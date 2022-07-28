#include <Renderer/Texture.h>

Texture::Texture() {
    glGenTextures(1, &m_Id);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_Id);
}

void Texture::Generate(int32_t width, int32_t height, uint8_t* data) {
    m_Width = width;
    m_Height = height;

    glBindTexture(GL_TEXTURE_2D, m_Id);

    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_MinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_MaxFilter);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}