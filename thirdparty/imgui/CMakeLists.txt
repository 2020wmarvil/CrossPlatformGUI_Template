set(IMGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imstb_rectpack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imstb_textedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imstb_truetype.h

    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot.h
    ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot_items.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/imspinner/imspinner.h

    ${CMAKE_CURRENT_SOURCE_DIR}/LegitProfiler/ImGuiProfilerRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LegitProfiler/ProfilerTask.h
)

set(THIRDPARTY_SOURCE_FILES ${THIRDPARTY_SOURCE_FILES} ${IMGUI_SOURCES} PARENT_SCOPE)

find_package(OpenGL REQUIRED)
find_package(GLFW3)

if (${GLFW3_FOUND})
    message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
else()
    message(STATUS "GLFW3 not found on system. Falling back to pre-packaged lib.")
    set(${GLFW3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
    set(${GLFW3_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/glfw/lib/lib-vc2019/glfw3.lib)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLFW3_INCLUDE_DIR}
    backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARY} ${GLFW3_LIBRARY})