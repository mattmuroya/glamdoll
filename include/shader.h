#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
    GLuint id;

public:
    void create(const char*, const char*);
    void use();
    void setBool(const std::string&, bool) const;
    void setInt(const std::string&, int) const;
    void setFloat(const std::string&, float) const;
    void setMat4(const std::string&, glm::mat4) const;
    void setMat3(const std::string&, glm::mat3) const;

private:
    void verifyShaderCompile(GLuint, const char*);
    void verifyProgramLink(GLuint);
};

#endif
