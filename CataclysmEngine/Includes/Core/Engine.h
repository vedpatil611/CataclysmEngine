#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine {
public:
    // Get engine reference
    static Engine* GetRef();

    //Initialize Engine
    void Init();

    // Update engine and components
    void Update(float delta);

    // Render engine components
    void Render();

    // Poll events
    void Events();

    // Terminate Engine Instance
    void Terminate();

    inline int GetWindowWidth() const { return m_WindowWidth; }
    inline int GetWindowHeight() const { return m_WindowHeight; }

    inline bool IsRunning() const { return m_IsRunning; }

    ~Engine();
private:
    GLFWwindow* m_Window = nullptr;                             // Pointer to glfw window
    int m_WindowWidth = 1920, m_WindowHeight = 1080;            // Window current width and height

    bool m_IsRunning = false;                                   // Engine running state

    Engine();
    inline static Engine* s_Ref = nullptr;

    // Window close callback
    static void OnWindowClose(GLFWwindow* window);
};