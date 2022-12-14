#include "Renderer/Texture.h"
#include <Core/ResourceManager.h>
#include <memory>
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Vendors/stb/stb_image.h>

std::shared_ptr<Shader> ResourceManager::LoadShader(const char* name, const char* vertPath, const char* fragPath) {
    std::shared_ptr<Shader> shader = std::make_unique<Shader>(vertPath, fragPath);
    s_Shaders.insert(std::make_pair(name, shader));
    return shader;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const char* name, const char* path, bool alpha) {
    stbi_set_flip_vertically_on_load(true);  

    std::shared_ptr<Texture>tex = std::make_unique<Texture>();
    if (alpha) {
        tex->SetImageFormat(GL_RGBA);
        tex->SetInteralFormat(GL_RGBA);
    }

    int width = 0, height = 0, channels = 0;
    uint8_t* data = stbi_load(path, &width, &height, &channels, 0);

    tex->Generate(width, height, data);
    s_Textures.insert(std::make_pair(name, tex));

    stbi_image_free(data);

    return tex;
}

std::shared_ptr<Shader> ResourceManager::GetShader(const char* name) {
    auto it = s_Shaders.find(name);
    if (it == s_Shaders.end())
        return nullptr;
    else
        return it->second;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const char* name) {
    auto it = s_Textures.find(name);
    if (it == s_Textures.end())
        return nullptr;
    else
        return it->second;
}

void ResourceManager::UnloadShader(const char* name) {
    auto it = s_Shaders.find(name);

    if (it == s_Shaders.end()) {
        spdlog::warn("Shader {} does not exists", name);
    } else {
        // delete it->second;
        s_Shaders.erase(it);
    }
}

void ResourceManager::UnloadTexture(const char* name) {
    auto it = s_Textures.find(name);

    if (it == s_Textures.end()) {
        spdlog::warn("Texture {} does not exists", name);
    } else {
        // delete it->second;
        s_Textures.erase(it);
    }
}

void ResourceManager::Clear() {
    // for (auto& [_, shader]: s_Shaders)
    //     delete shader;

    // for (auto& [_, texture]: s_Textures)
    //     delete texture;

    s_Shaders.clear();
    s_Textures.clear();
}