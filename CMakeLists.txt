cmake_minimum_required(VERSION 3.20)

###### Setup Project #####
include(cmake/utils.cmake)

renderer_extract_version()

project(renderer VERSION ${RENDERER_VERSION} LANGUAGES C CXX)
message(STATUS "Build renderer: ${RENDERER_VERSION}")
include(GNUInstallDirs)

# Set Default Build to Release
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# Set master project variable.
if(NOT DEFINED RENDERER_MASTER_PROJECT)
	if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
		set(RENDERER_MASTER_PROJECT ON)
	else()
		set(RENDERER_MASTER_PROJECT OFF)
	endif()
endif()

##### Options #####

# Build all
option(RENDERER_BUILD_ALL "Build all artifacts" OFF)

# Use Sanitizer
option(RENDERER_SANITIZE_ADDRESS "Enable address sanitizer in tests" OFF)

# Enable warnings
option(RENDERER_BUILD_WARNINGS "Enable build warnings" OFF)

# Build install
option(RENDERER_INSTALL "Generate install target" ${RENDERER_MASTER_PROEJCT})

# Use resource files
option(RENDERER_USE_RESOURCES "Use resource files" ON)

# Use clang-tidy
option(RENDERER_TIDY "Run clang-tidy" OFF)

if(RENDERER_TIDY)
	set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	message(STATUS "Enabled clang tidy")
endif()

##### Dependency Management

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
add_subdirectory(third-party)

##### Resource Preprocessor #####

add_library(renderer-shader-preprocessor-if INTERFACE)
add_library(renderer::shader-preprocessor-if ALIAS renderer-shader-preprocessor-if)
target_include_directories(renderer-shader-preprocessor-if
	INTERFACE
		"shader_preprocessor/include"
)

add_executable(renderer-shader-preprocessor)
add_executable(renderer::shader-preprocessor ALIAS renderer-shader-preprocessor)
target_sources(renderer-shader-preprocessor
	PRIVATE
		"shader_preprocessor/main.cpp"
 "renderer/gl/shader_pipeline.cpp")

target_link_libraries(renderer-shader-preprocessor
	PRIVATE
		zlib::zlib
		cxxopts::cxxopts
		OpenGL::GL
		OpenGL::GLU
		glfw::glfw
		glad::glad
		Threads::Threads
		tsl::robin_map
		renderer::shader-preprocessor-if
)


##### Resources #####
if(RENDERER_USE_RESOURCES)
include(cmake/cmrc/CMakeRC.cmake)
	file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/resources/*")
	message(STATUS "Resource build enabled")
	cmrc_add_resource_library(renderer-resources 
		ALIAS renderer::resources 
		NAMESPACE rc
		WHENCE "${CMAKE_CURRENT_SOURCE_DIR}/resources"
		${RESOURCE_FILES}
	)

	target_compile_definitions( renderer-resources
		PUBLIC
			RENDERER_RC_ENABLED
	)
endif()

##### Main Library #####
add_library(renderer-backend STATIC)
add_library(renderer::backend ALIAS renderer-backend)
target_sources(renderer-backend
	PRIVATE
		"renderer/renderer.cpp"
		"renderer/gl/buffer.cpp"
		"renderer/gl/framebuffer.cpp"
		"renderer/gl/renderbuffer.cpp"
		"renderer/gl/shader.cpp"
		"renderer/gl/shader_program.cpp"
		"renderer/gl/texture.cpp"
		"renderer/gl/vertex_array.cpp"
		"renderer/core/camera.cpp"
		"renderer/core/vertex.cpp"
		"renderer/core/obj_loader.cpp"
		"renderer/core/tex_loader.cpp"
		"renderer/core/shader_loader.cpp"
 "renderer/gl/shader_pipeline.cpp")
target_include_directories(renderer-backend
	PUBLIC
		include/
)
target_compile_features(renderer-backend
	PUBLIC
		cxx_std_20
)
target_link_libraries(renderer-backend
	PUBLIC
		OpenGL::GL
		OpenGL::GLU
		glad::glad
		glfw::glfw
		glm::glm
		Threads::Threads
		tinyobjloader::tinyobjloader
		stb::stb
		cxxopts::cxxopts
		zlib::zlib
		tsl::robin_map

		renderer::resources
)
set_target_properties(renderer-backend 
	PROPERTIES
		CXX_EXTENSIONS OFF
		CXX_STANDARD_REQUIRED ON
)
renderer_enable_warnings(renderer-backend)
renderer_enable_sanitizer(renderer-backend)

##### Main Executable #####
add_executable(renderer-executable)
add_executable(renderer::renderer ALIAS renderer-executable)
target_sources(renderer-executable
	PRIVATE
		"renderer/main.cpp"
  "renderer/gl/shader_pipeline.cpp")
target_include_directories(renderer-executable
	PRIVATE
		include/
)
target_compile_features(renderer-executable
	PRIVATE
		cxx_std_20
)
target_link_libraries(renderer-executable
	PRIVATE
		renderer::backend
		imgui::imgui
		glfw::glfw
		Threads::Threads
)
set_target_properties(renderer-executable
	PROPERTIES
		CXX_EXTENSIONS OFF
		CXX_STANDARD_REQUIRED ON
)
renderer_enable_warnings(renderer-executable)
renderer_enable_sanitizer(renderer-executable)

##### Additional Binaries #####
if(RENDERER_BUILD_TESTS OR RENDERER_BUILD_ALL)
	message(STATUS "Generating tests")
	enable_testing()
	add_subdirectory(tests)
endif()

if(RENDERER_BUILD_BENCHMARKS OR RENDERER_BUILD_ALL)
	message(STATUS "Generating benchmarks")
	add_subdirectory(benchmarks)
endif()

##### Install #####
if(RENDERER_INSTALL)
	install(TARGETS renderer-executable)
endif()