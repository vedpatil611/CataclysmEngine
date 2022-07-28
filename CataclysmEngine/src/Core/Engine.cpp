#include <Core/Engine.h>

#include <stdexcept>

Engine* Engine::GetRef() {
    return s_Ref = (s_Ref == nullptr) ? new Engine() : s_Ref;
}

void Engine::Init() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init glfw");
    }

    m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "CatalysmEngine", nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwSetWindowUserPointer(m_Window, this);

    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("Failed to init glad");

    glfwSetWindowCloseCallback(m_Window, &Engine::OnWindowClose);

    m_IsRunning = true;
}

void Engine::Update(float delta) {

}

void Engine::Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_Window);
}

void Engine::Events() {
    glfwPollEvents();
}

void Engine::Terminate() {
    m_IsRunning = false;
    auto* e = s_Ref;
    s_Ref = nullptr;
    delete e;
}

Engine::Engine() {

}

Engine::~Engine() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Engine::OnWindowClose(GLFWwindow* window) {
    auto* e = Engine::GetRef();

    e->m_IsRunning = false;
}