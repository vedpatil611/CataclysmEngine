#include <Renderer/SpriteRenderer.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader* shader)
    :m_Shader(shader) {

    VertexData vertices[] = {
        { { 0.0f, 1.0f }, { 0.0f, 1.0f } },
        { { 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 1.0f, 1.0f }, { 1.0f, 1.0f } },
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

SpriteRenderer::~SpriteRenderer() {
    glDeleteBuffers(1, &m_IBO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void SpriteRenderer::DrawSprite(Texture* tex, const glm::vec2 pos, const glm::vec2 size, float rotate) {
    if (tex == nullptr) {
        printf("No texture provided\n");
        return;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_Shader->Bind();

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_Shader->SetUniformMat4f("u_Model", model);

    glActiveTexture(GL_TEXTURE0);
    tex->Bind();

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}