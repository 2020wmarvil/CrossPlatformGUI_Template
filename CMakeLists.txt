cmake_minimum_required(VERSION 3.20)

project(CrossPlatformGUI)

# project properties
set(CMAKE_CXX_STANDARD 20) # use C++20
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) # 
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# create main build target/executable
add_executable(${PROJECT_NAME} 
    main.cpp
    include/Camera.h
    include/Mesh.h
    include/Shader.h
    include/Texture.h
    include/Window.h
    data/shaders/default.vert
    data/shaders/default.frag
)

# add thirdparty projects
find_package(OpenGL REQUIRED)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui)
add_subdirectory(thirdparty/stb)

# create source groups
get_target_property(ALL_SOURCES ${PROJECT_NAME} SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
         PREFIX "ProjectName"
         FILES ${ALL_SOURCES})

# link against thirdparty libraries
target_include_directories(${PROJECT_NAME} PRIVATE include thirdparty/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARY} glfw)

# copy data to build directory
file(COPY        "${CMAKE_CURRENT_SOURCE_DIR}/data"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
