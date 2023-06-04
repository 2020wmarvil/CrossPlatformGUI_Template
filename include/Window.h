#pragma once

#include "GLFW/glfw3.h" // Will drag system OpenGL headers

static void FramebufferSizeCallback([[maybe_unused]] GLFWwindow* pWindow, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

static void MouseCallback(GLFWwindow* pWindow, double xposIn, double yposIn);

class Window
{
public:
    static void Init()
    {
        glfwSetErrorCallback([](int Error, const char* Description)
        {
            std::cerr << "GLFW Error " << Error << ": " << Description << "\n";
        });

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            return;
        }

        s_bInitialized = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    static void Terminate()
    {
        glfwTerminate();
        s_bInitialized = false;
    }

    Window(const uint32_t Width, const uint32_t Height, const char* Name)
    {
        if (!s_bInitialized)
        {
            std::cerr << "Cannot create GLFW window. GLFW is not initialized.\n";
            return;
        }

        m_Window = glfwCreateWindow(Width, Height, Name, nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create window\n";
            return;
        }
        
        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1); // Enable vsync
        glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
        glfwSetCursorPosCallback(m_Window, MouseCallback);
        glfwSetWindowUserPointer(m_Window, this);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    ~Window()
    {
        glfwDestroyWindow(m_Window);
    }

    [[nodiscard]] GLFWwindow* GetHandle() const { return m_Window; }

    bool ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void PollEvents()
    {
        glfwPollEvents();
    }

    void ProcessInput(const float DeltaTime)
    {
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_Window, true);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_Camera.ProcessKeyboard(CameraMovement::FORWARD, DeltaTime);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_Camera.ProcessKeyboard(CameraMovement::BACKWARD, DeltaTime);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_Camera.ProcessKeyboard(CameraMovement::RIGHT, DeltaTime);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_Camera.ProcessKeyboard(CameraMovement::LEFT, DeltaTime);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS)
        {
            m_Camera.ProcessKeyboard(CameraMovement::UP, DeltaTime);
        }

        if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            m_Camera.ProcessKeyboard(CameraMovement::DOWN, DeltaTime);
        }
    }

    void SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    const Camera& GetCamera() const { return m_Camera; }
    Camera& GetCamera() { return m_Camera; }

private:
    GLFWwindow* m_Window{nullptr};
    inline static bool s_bInitialized{false};
    Camera m_Camera;
};

static void MouseCallback(GLFWwindow* pWindow, double xposIn, double yposIn)
{
    Window* window = (Window*)glfwGetWindowUserPointer(pWindow);
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    static bool bFirstMouse = true;
    static float LastX = 1920.0f / 2.0f;
    static float LastY = 1080.0f / 2.0f;

    if (bFirstMouse)
    {
        LastX = xpos;
        LastY = ypos;
        bFirstMouse = false;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos; // reversed since y-coordinates go from bottom to top
    LastX = xpos;
    LastY = ypos;

    window->GetCamera().ProcessMouseMovement(xoffset, yoffset);
}
