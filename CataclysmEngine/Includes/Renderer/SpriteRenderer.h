#pragma once

#include "Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class SpriteRenderer: public Renderer {
public:
    /**
     * @brief Construct a new Sprite Renderer object
     * 
     * @param shader Shader to be used for rendering
     */
    SpriteRenderer(std::shared_ptr<Shader> shader);
    ~SpriteRenderer();

    /**
     * @brief Draw sprite from texture
     * 
     * @param tex Texture to be draw
     * @param pos Texture position
     * @param size Size to be draw
     * @param rotate Anti-clock wise rotation in degree
     */
    void DrawSprite(std::shared_ptr<Texture> tex, const glm::vec2 pos, const glm::vec2 size, float rotate = 0.0f);
private:
    uint32_t m_VBO, m_VAO, m_IBO;
    std::shared_ptr<Shader> m_Shader;

    struct VertexData
    {
        glm::vec2 pos;
        glm::vec2 uv;
    };
};