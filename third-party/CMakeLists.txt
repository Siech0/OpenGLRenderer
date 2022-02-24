

##### GLAD #####
add_subdirectory(glad)
add_library(glad::glad ALIAS glad)

##### GLFW #####
add_subdirectory(glfw)
add_library(glfw::glfw ALIAS glfw)

##### GLM #####
add_subdirectory(glm)

##### IMGUI #####
set(IMGUI_DIR imgui)
add_library(imgui STATIC)
add_library(imgui::imgui ALIAS imgui)
target_sources(imgui
	PRIVATE
		${IMGUI_DIR}/imgui.cpp
		${IMGUI_DIR}/imgui_demo.cpp
		${IMGUI_DIR}/imgui_draw.cpp
		${IMGUI_DIR}/imgui_tables.cpp
		${IMGUI_DIR}/imgui_widgets.cpp

		${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
		${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)