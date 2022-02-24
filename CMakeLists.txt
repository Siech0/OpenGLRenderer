cmake_minimum_required(VERSION 3.20)

###### Setup Project #####
include(cmake/utils.cmake)

renderer_extract_version()

project(renderer VERSION ${RENDERER_VERSION} LANGUAGES CXX)
message(STATUS "Build renderer: ${RENDERER_VERSION}")
include(GNUInstallDirs)

# Set Default Build to Release
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# Set master project variable.
if(NOT DEFINED RENDERER_MASTER_PROJECT)
	if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
		set(CMAKE_MASTER_PROJECT ON)
	else()
		set(CMAKE_MASTER_PROJECT OFF)
	endif()
endif()


##### Options #####

# Build all
option(RENDERER_BUILD_ALL "Build all artifacts" OFF)

# Build benchmarks
option(RENDERER_BUILD_BENCHMARKS "Build benchmarks" OFF)

# Build tests
option(RENDERER_BUILD_TEST "Build tests" OFF)

# Use Sanitizer
option(RENDERER_SANITIZE_ADDRESS "Enable address sanitizer in tests" OFF)

# Enable warnings
option(RENDERER_BUILD_WARNINGS "Enable build warnings" OFF)

# Build install
option(RENDERER_INSTALL "Generate install target" ${RENDERER_MASTER_PROEJCT})

# Use clang-tidy
option(RENDERER_TIDY "Run clang-tidy" OFF)

if(RENDERER_TIDY)
	set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	message(STATUS "Enabled clang tidy")
endif()

##### Dependency Management

find_package(Threads REQUIRED)
add_subdirectory(third-party)

##### Main Library #####
add_library(renderer-backend STATIC)
add_library(renderer::backend ALIAS renderer-backend)
target_sources(renderer-backend
	PRIVATE
		src/backend/test.cpp
)
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
		glad::glad
		glfw::glfw
		glm::glm
		Threads::Threads
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
		src/main.cpp
)
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
		glad::glad
		glm::glm
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