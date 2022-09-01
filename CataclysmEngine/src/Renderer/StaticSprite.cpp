#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include <Renderer/StaticSprite.h>
#include <cstddef>
#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

StaticSprite::StaticSprite(std::shared_ptr<Texture> tex, std::shared_ptr<Shader> shader)
    :m_Texture(tex), m_Shader(shader) {

    auto width = tex->Width();
    auto height = tex->Height();

    VertexData vertices[] = {
        { { 0.0f , height }, { 0.0f, 1.0f } },
        { { 0.0f , 0.0f   }, { 0.0f, 0.0f } },
        { { width, 0.0f   }, { 1.0f, 0.0f } },
        { { width, height }, { 1.0f, 1.0f } },
    };

    uint16_t indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    const uint32_t VERTEX_BIND_POINT = 0;
    const uint32_t POS_ATTRIB_SLOT = 0;
    const uint32_t UV_ATTRIB_SLOT = 1;

    glCreateVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glCreateBuffers(1, &m_VBO);
    glNamedBufferData(m_VBO, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexArrayVertexBuffer(m_VAO, VERTEX_BIND_POINT, m_VBO, 0, sizeof(VertexData));

    glVertexArrayAttribFormat(m_VAO, POS_ATTRIB_SLOT, 2, GL_FLOAT, false, offsetof(VertexData, pos));
    glVertexArrayAttribBinding(m_VAO, POS_ATTRIB_SLOT, VERTEX_BIND_POINT);
    glEnableVertexArrayAttrib(m_VAO, POS_ATTRIB_SLOT);

    glVertexArrayAttribFormat(m_VAO, UV_ATTRIB_SLOT, 2, GL_FLOAT, false, offsetof(VertexData, uv));
    glVertexArrayAttribBinding(m_VAO, UV_ATTRIB_SLOT, VERTEX_BIND_POINT);
    glEnableVertexArrayAttrib(m_VAO, UV_ATTRIB_SLOT);

    glCreateBuffers(1, &m_IBO);
    glNamedBufferData(m_IBO, sizeof(indicies), indicies, GL_STATIC_DRAW);
    glVertexArrayElementBuffer(m_VAO, m_IBO);

    glBindVertexArray(0);
}

StaticSprite::~StaticSprite() {
    glDeleteBuffers(1, &m_IBO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void StaticSprite::DrawInstance(const glm::vec2 pos, const glm::vec2 scale, float rotate) {
    if (m_Texture == nullptr) {
        spdlog::warn("No textire provided");
        return;
    }

    if (m_Shader == nullptr) {
        spdlog::warn("No shader provided");
        return;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_Shader->Bind();

    glm::vec2 size(m_Texture->Width(), m_Texture->Height());

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));

    m_Shader->SetUniformMat4f("u_Model", model);

    glActiveTexture(GL_TEXTURE0);
    m_Texture->Bind();

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}