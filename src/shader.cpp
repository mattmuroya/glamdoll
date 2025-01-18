#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    GLuint id; // Shader program handle

    // Read, compile, and link source code
    void create(const char* vertSourceFilePath, const char* fragSourceFilePath)
    {
        // ---------------------------------------------------------------------
        // Get shader source code from file
        // ---------------------------------------------------------------------

        std::string vertSourceCode;
        std::string fragSourceCode;

        std::ifstream vertSourceFile;
        std::ifstream fragSourceFile;

        // Enable filestream exceptions
        vertSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            std::stringstream vertStream, fragStream;

            // Open source file
            vertSourceFile.open(vertSourceFilePath);
            fragSourceFile.open(fragSourceFilePath);

            // Read buffer contents into stream
            vertStream << vertSourceFile.rdbuf();
            fragStream << fragSourceFile.rdbuf();

            // Close source file
            vertSourceFile.close();
            fragSourceFile.close();

            // Convert stream to string
            vertSourceCode = vertStream.str();
            fragSourceCode = fragStream.str();
        }
        catch (const std::exception& e)
        {
            std::cout << "ERROR::SHADER::FILESTREAM_EXCEPTION\n" << e.what() << std::endl;
        }

        // Convert string to C-style
        const char* vertShaderCode = vertSourceCode.c_str();
        const char* fragShaderCode = fragSourceCode.c_str();

        // ---------------------------------------------------------------------
        // Compile and link
        // ---------------------------------------------------------------------

        GLuint vertexShader, fragmentShader;

        // Create shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Set source and compile
        glShaderSource(vertexShader, 1, &vertShaderCode, NULL);
        glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        // Verify compilation successful
        verifyShaderCompile(vertexShader, "VERTEX");
        verifyShaderCompile(fragmentShader, "FRAGMENT");

        // Create shader program
        id = glCreateProgram();

        // Attach and link compiled shaders to program
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);

        glLinkProgram(id);

        // Verify shader program link
        verifyProgramLink(id);

        // Delete shader objects (no longer needed after linking)
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // Shader activation
    void use()
    {
        glUseProgram(id);
    };

    // Uniform setters (const member functions do not modify this object)
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void setMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void setMat3(const std::string& name, glm::mat3 value) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    void verifyShaderCompile(GLuint handle, const char* type)
    {
        int  success;
        char infoLog[512];

        glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(handle, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        else
        {
            std::cout << type << " shader compiled successfully." << std::endl;
        }
    }

    void verifyProgramLink(GLuint handle)
    {
        int  success;
        char infoLog[512];

        glGetProgramiv(handle, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(handle, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        }
        else
        {
            std::cout << "Shader program linked successfully." << std::endl;
        }
    };
};

#endif
