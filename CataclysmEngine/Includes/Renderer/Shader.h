#pragma once

#include <string>
#include <unordered_map>

class Shader {
public:
    /**
     * @param vertPath Vertex shader source code path
     * @param fragPath Fragment shader source code path
     */
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();

    // Bind this shader for current usage
    void Bind() const;

    // Unbind this shader from current usage
    void Unbind() const;
private:
    // Shader id
    uint32_t m_Id;

    // Uniform location cache for faster access
    std::unordered_map<std::string, int> m_UniformCache;

    /**
     * Compile shader of given type from source
     * 
     * @param type Shader type enum
     * @param srcPath Shader source code path
     * 
     * @return id of compiled shader
     */
    uint32_t CompileShader(unsigned int type, const char* srcPath);

    // Link attached shaders in programs
    void LinkProgram();

    // Validate attached shaders in program
    void ValidateProgram();

    // Precache all uniform locations of shader for faster access later
    void PreCacheUniforms();

    /**
     * Get location of uniform
     * 
     * @param name Name of uniform
     * 
     * @return uniform location
     */
    int32_t GetUniformLocation(const char* name);
};