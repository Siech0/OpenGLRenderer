

##### GLAD #####
set(GLAD_DIR glad)
add_library(glad STATIC)
add_library(glad::glad ALIAS glad)
target_sources(glad
	PRIVATE 
		${GLAD_DIR}/src/glad.c
)
target_include_directories(glad
	PUBLIC
		${GLAD_DIR}/include
)

##### GLFW #####
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_INSTALL OFF)
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
		##### Main Files #####
		${IMGUI_DIR}/imgui.cpp
		${IMGUI_DIR}/imgui_demo.cpp
		${IMGUI_DIR}/imgui_draw.cpp
		${IMGUI_DIR}/imgui_tables.cpp
		${IMGUI_DIR}/imgui_widgets.cpp

		##### BACKENDS #####
		${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
		${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui
	PUBLIC
		${IMGUI_DIR}
)
target_link_libraries(imgui
	PUBLIC
		OpenGL::GL
		OpenGL::GLU
		glfw::glfw
)

###### Tiny OBJ Loader ######
add_subdirectory(tinyobjloader)
add_library(tinyobjloader::tinyobjloader ALIAS tinyobjloader)

##### STB #####
set(STB_DIR stb)
add_library(stb STATIC)
add_library(stb::stb ALIAS stb)
target_sources(stb PRIVATE "stb.cpp")
target_include_directories(stb
	PUBLIC
		${STB_DIR}
)

##### ZLIB #####
add_subdirectory(zlib)
add_library(zlib::zlib ALIAS zlib)

##### Robin Map #####
add_subdirectory(robin-map)

#### CXXOpts #####
add_subdirectory(cxxopts)