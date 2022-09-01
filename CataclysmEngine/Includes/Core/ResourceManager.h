#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>

class ResourceManager {
public:
    /**
     * @brief Load Shader into Resource Manager
     * 
     * @param name Name id of shader
     * @param vertPath Vertex shader source path for shader
     * @param fragPath Fragment shader source path for shader
     * 
     * @return Pointer to newly created Shader. Return nullptr if failed
     */
    static std::shared_ptr<Shader> LoadShader(const char* name, const char* vertPath, const char* fragPath);
    
    /**
     * @brief Load Texture into Resource Manager
     * 
     * @param name Name id of texture
     * @param path Path to texture file
     * @param alpha if the texture contain alpha value
     * 
     * @return Pointer to newly created Texture. Return nullptr if failed
     */
    static std::shared_ptr<Texture> LoadTexture(const char* name, const char* path, bool alpha = true);

    // Get shader from ResourceMananger
    static std::shared_ptr<Shader> GetShader(const char* name);

    // Get texture from ResourceManager
    static std::shared_ptr<Texture> GetTexture(const char* name);

    // Unload and delete shader
    static void UnloadShader(const char* name);

    // Unload and delete texture
    static void UnloadTexture(const char* name);

    // Clear all resources
    static void Clear();
private:
    inline static std::unordered_map<std::string, std::shared_ptr<Shader>> s_Shaders;
    inline static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
};