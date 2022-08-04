#pragma once

#include <cstdint>
#include <stdint.h>
#include <glad/glad.h>

class Texture {
public:
    // Construct a new Texture object
    Texture();
    ~Texture();

    /**
     * @brief Generate and load texture on gpu
     * 
     * @param width Width of texture
     * @param height Height of texture
     * @param data Texture data read from file
     */
    void Generate(int32_t width, int32_t height, uint8_t* data);

    // Bind texture to current slot
    void Bind() const;

    // Unbind texture from current slot
    void Unbind() const;

    // Set internal format for image
    inline void SetInteralFormat(int32_t format) { m_InternalFormat = format; }

    // Set format of image
    inline void SetImageFormat(int32_t format) { m_ImageFormat = format; }

    // Get widht of texture image
    inline int32_t Width() const  { return m_Width; }

    // Get Height of texture image
    inline int32_t Height() const { return m_Height; }
private:
    uint32_t m_Id;
    int32_t m_Width = 0, m_Height = 0;
    // Texture format
    int32_t m_InternalFormat = GL_RGB;
    // Image format
    int32_t m_ImageFormat = GL_RGB;

    int32_t m_WrapS = GL_REPEAT, m_WrapT = GL_REPEAT;
    int32_t m_MinFilter = GL_NEAREST, m_MaxFilter = GL_NEAREST;
};