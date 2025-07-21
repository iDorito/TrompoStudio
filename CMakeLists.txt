# CMakeList.txt: proyecto de CMake para TrompoStudio, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.13)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# RUNTIME
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded<$<CONFIG:Release>:Release>")

project ("TrompoStudio" LANGUAGES CXX C)

# if (CMAKE_VERSION VERSION_GREATER 3.12)
#   set_property(TARGET TrompoStudio PROPERTY CXX_STANDARD 20)
# endif()

# C++ STANDARDS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Optional

# DEPENDENCIES
set(DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(DEPENDENCIES_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include")
set(DEPENDENCIES_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib")
set(DIR_IMGUI "${DEPENDENCIES_DIR}/imgui")

# Agregue un origen al ejecutable de este proyecto.
add_executable (
	TrompoStudio "src/main.cpp"
	"src/Application/App.cpp"
	"src/Application/WindowManager.cpp"
	"src/Application/MyWindow.cpp"
	"src/Engine/Engine.cpp"
	# GLAD
	"dependencies/glad.c"

	# Imgui
	"${DIR_IMGUI}/imgui.cpp"
    "${DIR_IMGUI}/imgui_draw.cpp"
    "${DIR_IMGUI}/imgui_tables.cpp"
    "${DIR_IMGUI}/imgui_widgets.cpp"
    # Backends de ImGui (asumiendo que están en una subcarpeta 'backends')
    "${DIR_IMGUI}/backends/imgui_impl_glfw.cpp"
    "${DIR_IMGUI}/backends/imgui_impl_opengl3.cpp"

 "src/Application/MyWindow.h" "src/Application/MyWindow.cpp")

# DIRECTORIES
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DIR_ASSETS="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# GLAD Loader for OpenGL Backend
target_compile_definitions(TrompoStudio PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# Main Include
target_include_directories(TrompoStudio PUBLIC
	"${DEPENDENCIES_INCLUDE_DIR}"
	
	# imgui
	"${DIR_IMGUI}"
    "${DIR_IMGUI}/backends"
)

# Main libs
target_link_libraries(TrompoStudio PUBLIC
	"${DEPENDENCIES_LIB_DIR}/glfw3.lib"
	"${DEPENDENCIES_LIB_DIR}/spdlogd.lib"

	opengl32
)

# Visual Studio config
if(MSVC)
	target_compile_definitions(TrompoStudio PRIVATE _CRT_SECURE_NO_WARNINGS)

	# Encoding
	target_compile_options(TrompoStudio PRIVATE /utf-8)
endif()

# Redundant
target_compile_features(TrompoStudio PUBLIC cxx_std_20)


# TODO: Agregue pruebas y destinos de instalación si es necesario.
