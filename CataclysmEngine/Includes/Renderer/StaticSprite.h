#pragma once

#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>

/**
 * @brief Static sprite generate its own vertex data from texture and thus has its own renderer
 */
class StaticSprite {
public:
    /**
     * @brief Construct a new Static Sprite object
     * 
     * @param tex Texture from which sprite is to be constructed
     * @param shader Shader progam which should be used to draw sprite
     */
    StaticSprite(Texture* tex, Shader* shader);

    ~StaticSprite();

    /**
     * @brief Draw instance of sprite on buffer
     * 
     * @param pos Position at which sprite should be drawn
     * @param scale Sprite image scaling 
     * @param rotate Sprite image anti clockwise rotation 
     */
    void DrawInstance(const glm::vec2 pos, const glm::vec2 scale = glm::vec2(1.0f, 1.0f), float rotate = 0.0f);
private:
    uint32_t m_VBO, m_VAO, m_IBO;
    Shader* m_Shader;
    Texture* m_Texture;

    struct VertexData
    {
        glm::vec2 pos;
        glm::vec2 uv;
    };
};