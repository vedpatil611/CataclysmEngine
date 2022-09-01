#include <Core/Engine.h>

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <memory>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <Core/ResourceManager.h>
#include "Renderer/SpriteRenderer.h"
#include "Renderer/StaticSprite.h"

StaticSprite* woodySprite = nullptr;

std::shared_ptr<Engine> Engine::GetRef() {
    return s_Ref = (s_Ref == nullptr) ? std::shared_ptr<Engine>(new Engine()) : s_Ref;
}

void Engine::Init() {
    // spdlog::info("Failed to init glfw");
    // spdlog::warn("Failed to init glfw");
    // spdlog::error("Failed to init glfw");
    // spdlog::critical("Failed to init glfw");
    
    if (!glfwInit()) {
        spdlog::critical("Failed to init glfw");
        throw std::runtime_error("Failed to init glfw");
    }


    m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "CatalysmEngine", nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        spdlog::critical("Failed to create window");
        throw std::runtime_error("Failed to create window");
    }

    glfwSetWindowUserPointer(m_Window, this);

    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::critical("Failed to init glfw");
        throw std::runtime_error("Failed to init glad");
    }

    glfwSetWindowCloseCallback(m_Window, &Engine::OnWindowClose);

    m_Projection = glm::ortho(0.0f, 720.0f, 0.0f, 576.0f, -1.0f, 1.0f);

    m_IsRunning = true;

    // m_Window = std::shared_ptr<GLFWwindow>(window);

    #ifdef DEBUG
    auto shader = ResourceManager::LoadShader("basic", "shaders/vert.glsl", "shaders/frag.glsl");
    shader->SetUniformMat4f("u_Proj", m_Projection);
    
    auto woodyTex = ResourceManager::LoadTexture("woody", "assets/woody.png");

    // m_SpriteRenderer = new SpriteRenderer(shader);
    m_SpriteRenderer = std::make_shared<SpriteRenderer>(shader);

    woodySprite = new StaticSprite(woodyTex, shader);
    #endif
}

void Engine::Update(float delta) {

}

void Engine::Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    #ifdef DEBUG
    ResourceManager::GetShader("basic")->SetUniformMat4f("u_Proj", m_Projection);
    // m_SpriteRenderer->DrawSprite(ResourceManager::GetTexture("woody"), { 0.2, 0.2 }, { 0.2, 0.2 });
    woodySprite->DrawInstance({400.0f, 400.0f});
    woodySprite->DrawInstance({1.0f, 1.0f}, {5.0f, 5.0f});
    #endif

    glfwSwapBuffers(m_Window);
}

void Engine::Events() {
    glfwPollEvents();
}

void Engine::Terminate() {
    m_IsRunning = false;
    auto e = s_Ref;
    s_Ref = nullptr;
    e.reset();
}

void Engine::SetWindowWidth(int32_t width) {
    m_WindowWidth = width;
    glfwSetWindowSize(m_Window, m_WindowWidth, m_WindowHeight);
}

void Engine::SetWindowHeight(int32_t height) {
    m_WindowHeight = height;
    glfwSetWindowSize(m_Window, m_WindowWidth, m_WindowHeight);
}

Engine::Engine() {

}

Engine::~Engine() {
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
    glfwTerminate();
}

void Engine::OnWindowClose(GLFWwindow* window) {
    auto e = Engine::GetRef();

    e->m_IsRunning = false;
}