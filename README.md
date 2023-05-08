# CrossPlatformGUI_Template

This is a convenient template for quickly getting a cross-platform GUI project up and running in C++ with GLFW, OpenGL, and DearImGUI.

### Setup

Create a build directory

```mkdir build && cd build```

Run CMake from the build directory

```cmake ..```

To build and execute the project, use the generated makefile (Unix default) or MSBuild solution (Windows default). 

### Modifying the project

To add header and source files, append the filepaths to ```add_executable(${PROJECT_NAME} main.cpp <your_files_here>)```

To modify the user interface, see the [ImGUI GLFW/OpenGL example](https://github.com/ocornut/imgui/blob/docking/examples/example_glfw_opengl3/main.cpp), or uncomment the ImGui::ShowDemoWindow() function in main.cpp.

For convenience, [ImPlot](https://github.com/epezent/implot), [ImSpinner](https://github.com/dalerank/imspinner), and [LegitProfiler](https://github.com/Raikiri/LegitProfiler) are also included in the ImGui source files.

### Usage

If your application does not require rendering outside of the UI itself, you can set ```bUIShouldFillWindow = true``` to in ```main.cpp```. This will force the ImGUI context to fill the GLFW window. 

Otherwise, you can use the GLFW window to render arbitrary geometry, with floating ImGUI windows that can be dragged or docked for convenience. ImGUI will generate an ```imgui.ini``` file in the ```build``` directory, which stores layout preferences, and automatically sets ImGUI window positions and sizes on startup. Delete this file to reset preferences to default.