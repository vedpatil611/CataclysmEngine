#include <Renderer/Shader.h>

#include <cstdio>
#include <glad/glad.h>
#include <Utils/File.h>
#include <spdlog/spdlog.h>

Shader::Shader(const char* vertPath, const char* fragPath) {
    m_Id = glCreateProgram();

    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertPath);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragPath);

    glAttachShader(m_Id, vs);
    glAttachShader(m_Id, fs);

    LinkProgram();
    ValidateProgram();

    PreCacheUniforms();

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    glDeleteProgram(m_Id);
}

void Shader::Bind() const {
    glUseProgram(m_Id);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniformMat4f(const char* name, const glm::mat4& mat) {
    auto it = m_UniformCache.find(name);
    
    int location;

    if (it == m_UniformCache.end())
        location = GetUniformLocation(name);
    else
        location = it->second;

    glUniformMatrix4fv(location, 1, false, &mat[0][0]);
}

uint32_t Shader::CompileShader(uint32_t type, const char* srcPath) {
    uint32_t id = glCreateShader(type);

    auto srcStr = Utils::ReadFile(srcPath);
    auto src = srcStr.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char* message = new char[len];
        glGetShaderInfoLog(id, len, &len, message);
        spdlog::error("Failed to complile {} shader: {}", type == GL_VERTEX_SHADER ? "vertex" : "fragment", message);
        // printf("Failed to compile %s shader: %s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", message);
        delete[] message;

        glDeleteShader(id);

        return 0;
    }

    return id;
}

void Shader::LinkProgram() {
    glLinkProgram(m_Id);

    int result;
    glGetProgramiv(m_Id, GL_LINK_STATUS, &result);

    if (!result) {
        char eLog[1024];
        glGetProgramInfoLog(m_Id, sizeof(eLog), nullptr, eLog);
        printf("Failed to link program: %s", eLog);
    }
}

void Shader::ValidateProgram() {
    glValidateProgram(m_Id);

    int result;
    glGetProgramiv(m_Id, GL_VALIDATE_STATUS, &result);

    if (!result) {
        char eLog[1024];
        glGetProgramInfoLog(m_Id, sizeof(eLog), nullptr, eLog);
        printf("Failed to validate program: %s", eLog);
    }
}

void Shader::PreCacheUniforms() {
    int numUniforms;
    glGetProgramiv(m_Id, GL_ACTIVE_UNIFORMS, &numUniforms);

    int maxUniformLength;
    glGetProgramiv(m_Id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLength);

    if (numUniforms > 0 && maxUniformLength > 0) {
        char* uniformName = new char[maxUniformLength];

        for (int i = 0; i < numUniforms; ++i) {
            int len, size;
            GLenum dataType;

            glGetActiveUniform(m_Id, i, maxUniformLength, &len, &size, &dataType, uniformName);
            GetUniformLocation(uniformName);
        }

        delete[] uniformName;
    }
}

int32_t Shader::GetUniformLocation(const char* name) {
    int location = glGetUniformLocation(m_Id, name);
    if (location == -1) {
        printf("Uniform %s not found\n", name);
    }

    m_UniformCache[name] = location;

    return location;
}