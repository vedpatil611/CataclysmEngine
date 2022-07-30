#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/SpriteRenderer.h"

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

    // Get window width
    inline int32_t GetWindowWidth() const { return m_WindowWidth; }

    // Get window height
    inline int32_t GetWindowHeight() const { return m_WindowHeight; }

    // Set current window width
    inline void SetWindowWidth(int32_t width);
    
    // Set current window height
    inline void SetWindowHeight(int32_t height);

    // Get Engine running status
    inline bool IsRunning() const { return m_IsRunning; }

    ~Engine();
private:
    GLFWwindow* m_Window = nullptr;                             // Pointer to glfw window
    int32_t m_WindowWidth = 1920, m_WindowHeight = 1080;            // Window current width and height

    bool m_IsRunning = false;                                   // Engine running state

    SpriteRenderer* m_SpriteRenderer = nullptr;

    Engine();
    inline static Engine* s_Ref = nullptr;

    // Window close callback
    static void OnWindowClose(GLFWwindow* window);
};