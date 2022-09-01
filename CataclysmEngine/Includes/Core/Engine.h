#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/SpriteRenderer.h"
#include <memory>

class Engine {
public:
    // Get engine reference
    static std::shared_ptr<Engine> GetRef();

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
    inline int32_t WindowWidth() const { return m_WindowWidth; }

    // Get window height
    inline int32_t WindowHeight() const { return m_WindowHeight; }

    // Set current window width
    inline void SetWindowWidth(int32_t width);
    
    // Set current window height
    inline void SetWindowHeight(int32_t height);

    // Get Engine running status
    inline bool IsRunning() const { return m_IsRunning; }

    // Return const reference to projection matrix
    inline const glm::mat4& Projection() const { return m_Projection; }

    // Set projection matrix
    inline void SetProjection(const glm::mat4& proj) { m_Projection = proj; }

    ~Engine();
private:
    GLFWwindow* m_Window = nullptr;                             // Pointer to glfw window
    int32_t m_WindowWidth = 1920, m_WindowHeight = 1080;        // Window current width and height

    bool m_IsRunning = false;                                   // Engine running state

    glm::mat4 m_Projection;

    std::shared_ptr<SpriteRenderer> m_SpriteRenderer = nullptr;

    Engine();
    inline static std::shared_ptr<Engine> s_Ref = nullptr;

    // Window close callback
    static void OnWindowClose(GLFWwindow* window);
};