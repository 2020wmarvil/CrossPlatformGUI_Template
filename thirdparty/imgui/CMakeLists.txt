set(SOURCES
    imgui.h
    imgui.cpp

    imconfig.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h

    backends/imgui_impl_glfw.h
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.h
    backends/imgui_impl_opengl3.cpp
    backends/imgui_impl_opengl3_loader.h

    implot/implot.h
    implot/implot.cpp
    implot/implot_demo.cpp
    implot/implot_internal.h
    implot/implot_items.cpp

    imspinner/imspinner.h

    LegitProfiler/ImGuiProfilerRenderer.h
    LegitProfiler/ProfilerTask.h
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} backends)