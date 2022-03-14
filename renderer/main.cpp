
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include <renderer/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


using namespace gfx::gl;
using namespace gfx::core;

void glfwErrorCallback(int error, const char* description)
{
	std::cout << "GLFW Error " << error << " : " << description << '\n';
}

class Application
{
public:

	Application(int width, int height, const std::string& title) 
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (m_window == nullptr)
			throw std::runtime_error("Unable to create window.");

		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Unable to load OpenGL.");

		glfwSwapInterval(1); // Enable vsync.

		// Set user pointer so we can access this window in callbacks
		glfwSetWindowUserPointer(m_window, (void*)this);
		glfwSetFramebufferSizeCallback(m_window, &Application::onFramebufferResizeCallback);

		// Setup IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); 
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Darkmode is the best style
		ImGui::StyleColorsDark();

		// Setup platform / render imgui backends
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		// Prepare renderer
		glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);
		m_renderer.reset(new gfx::Renderer(m_bufferWidth, m_bufferHeight));
	}

	~Application()
	{
		// Destroy ImGui
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Destroy glfw window
		glfwDestroyWindow(m_window);
	}

	void run()
	{
		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();

			// ImGui Frame Init
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			update();
			draw();
			render();

			// ImGui Rendering
			ImGui::Render(); 
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2((float)m_bufferWidth, (float)m_bufferHeight);
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}

			// Swap out buffer
			glfwSwapBuffers(m_window);
		}
	}

private:

	// Update state
	void update()
	{
		
		// Don't update scene when ImGui is focused
		if (ImGui::IsWindowFocused())
			return;

		bool update_camera = false;
		glm::vec3 position_update(0.0f, 0.0f, 0.0f);
		auto& camera = m_renderer->camera();

		// Handle any mouse drags
		ImVec2 mouse_pos = ImGui::GetMousePos();
		const float xpos = mouse_pos.x;
		const float ypos = mouse_pos.y;

		if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
		{
			// Initial Read
			if (m_mouseLastX < 0.0 || m_mouseLastY < 0.0f)
			{
				m_mouseLastX = xpos;
				m_mouseLastY = ypos;
			}

			const float xoffset = xpos - m_mouseLastX;
			const float yoffset = ypos - m_mouseLastY;
			m_mouseLastX = xpos;
			m_mouseLastY = ypos;

			const float yaw = xoffset * m_sensitivity;
			const float pitch = yoffset * m_sensitivity;

			auto& camera = m_renderer->camera();
			camera.rotateYaw(yaw);
			camera.rotatePitch(yaw);
		}
		else
		{
			m_mouseLastX = xpos;
			m_mouseLastY = ypos;
		}

		// Handle key presses
		if (ImGui::IsKeyDown('A'))
		{
			position_update -= camera.right();
			update_camera = true;
		}

		if (ImGui::IsKeyDown('S'))
		{
			position_update -= camera.forward();
			update_camera = true;
		}

		if (ImGui::IsKeyDown('D'))
		{
			position_update += camera.right();
			update_camera = true;
		}

		if (ImGui::IsKeyDown('W'))
		{
			position_update += camera.forward();
			update_camera = true;
		}

		if (ImGui::IsKeyDown('Q'))
		{
			position_update -= camera.up();
			update_camera = true;
		}

		if (ImGui::IsKeyDown('E'))
		{
			position_update += camera.up();
			update_camera = true;
		}

		// Process camera update
		if(update_camera)
		{
			float move_speed = m_moveSpeed;
			if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
				move_speed *= 10.0f;

			if (glm::length(position_update) > 0.0f)
			{
				// Normalize movement vector + scale by move speed
				position_update = move_speed * glm::normalize(position_update);
				camera.offsetPosition(position_update);
			}
		}
	}

	// Rendering 
	void render()
	{
		m_renderer->render((float)m_bufferWidth, (float)m_bufferHeight);
	}

	// GUI Drawing
	void draw()
	{
		
		ImGui::Begin("Renderer");
		if (ImGui::CollapsingHeader("Camera Control"))
		{
			auto& camera = m_renderer->camera();
			ImGui::InputFloat("Camera Sensitivity", &m_sensitivity);
			ImGui::InputFloat("Camera Speed", &m_moveSpeed);
			ImGui::Separator();

			auto pos = camera.position();
			if (ImGui::InputFloat3("Camera Position", (float*)&pos))
			{
				camera.setPosition(pos);
			}

			auto angles = camera.orientationAngles();
			angles.x = glm::degrees(angles.x); angles.y = glm::degrees(angles.y); angles.z = glm::degrees(angles.z);
			if (ImGui::InputFloat("Yaw", &angles.y) | ImGui::InputFloat("Pitch", &angles.x) | ImGui::InputFloat("Roll", &angles.z))
			{
				angles.x = glm::radians(angles.x); angles.y = glm::radians(angles.y); angles.z = glm::radians(angles.z);
				camera.setOrientation(angles);
			}
			ImGui::Separator();

			static glm::vec3 lookat_pos;
			ImGui::InputFloat3("LookAt Position", (float*)&lookat_pos);
			if (ImGui::Button("Look"))
			{
				camera.lookAt(lookat_pos);
			}
		}

		if (ImGui::CollapsingHeader("Scene"))
		{
			ImGui::InputFloat3("Light Position", (float*)&m_renderer->lightPosition());
			ImGui::ColorEdit3("Light Color", (float*)&m_renderer->lightColor());
			ImGui::InputFloat("Light Power", &m_renderer->lightPower());
			ImGui::InputFloat("Model Alpha", &m_renderer->modelAlpha());
		}
		ImGui::End();

	}

	// callback bindings
	void onFramebufferResize(int width, int height)
	{
		m_bufferWidth = width;
		m_bufferHeight = height;
		m_renderer->setViewport(width, height);
	}

	// static callback bindings
	static void onFramebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		Application* self = (Application *)glfwGetWindowUserPointer(window);
		self->onFramebufferResize(width, height);
	}

	// Window State
	int m_bufferWidth, m_bufferHeight;
	GLFWwindow* m_window;
	std::unique_ptr<gfx::Renderer> m_renderer;

	// IO State
	double m_mouseLastX = -1.0, m_mouseLastY = -1.0;
	float m_sensitivity = 0.1f, m_moveSpeed = 0.1f;
};


int main()
{
	try
	{
		if (!glfwInit())
			throw std::runtime_error("Unable to initialize GLFW3.");

		glfwSetErrorCallback(glfwErrorCallback);

		Application app(720, 600, "Renderer");
		app.run();


	}
	catch (std::exception& e)
	{
		std::cout << "Fatal Error: " << e.what() << '\n';
	}

	glfwTerminate();
}