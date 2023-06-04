#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    /**
     * \brief Creates a shader object from vertex and fragment shader files on disk
     * \param VertexPath Vertex shader filepath
     * \param FragmentPath Fragment shader filepath
     */
    Shader(const char* VertexPath, const char* FragmentPath)
    {
        // Read shaders from disk
        std::string vertexCode, fragmentCode;
        std::ifstream vShaderFile, fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vShaderFile.open(VertexPath);
            std::stringstream vShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            vShaderFile.close();
            vertexCode = vShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "Failed to open or read vertex shader: " << e.what() << std::endl;
        }

        try
        {
            fShaderFile.open(FragmentPath);
            std::stringstream fShaderStream;
            fShaderStream << fShaderFile.rdbuf();
            fShaderFile.close();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "Failed to open or read fragment shader: " << e.what() << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Compile shaders
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        // Create shader program
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        glLinkProgram(m_ID);
        CheckCompileErrors(m_ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    /**
     * \brief Bind this shader object as the active shader
     */
    void Bind() const
    {
        glUseProgram(m_ID);
    }

    void SetBool(const std::string& Name, const bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, Name.c_str()), (int)value);
    }

    void SetInt(const std::string& Name, const int Value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, Name.c_str()), Value);
    }

    void SetFloat(const std::string& Name, const float Value) const
    {
        glUniform1f(glGetUniformLocation(m_ID, Name.c_str()), Value);
    }

    void SetVec2(const std::string& Name, const glm::vec2& Value) const
    {
        glUniform2fv(glGetUniformLocation(m_ID, Name.c_str()), 1, &Value[0]);
    }

    void SetVec2(const std::string& Name, const float X, const float Y) const
    {
        glUniform2f(glGetUniformLocation(m_ID, Name.c_str()), X, Y);
    }

    // ------------------------------------------------------------------------
    void SetVec3(const std::string& Name, const glm::vec3& Value) const
    {
        glUniform3fv(glGetUniformLocation(m_ID, Name.c_str()), 1, &Value[0]);
    }

    void SetVec3(const std::string& Name, const float X, const float Y, const float Z) const
    {
        glUniform3f(glGetUniformLocation(m_ID, Name.c_str()), X, Y, Z);
    }

    // ------------------------------------------------------------------------
    void SetVec4(const std::string& Name, const glm::vec4& Value) const
    {
        glUniform4fv(glGetUniformLocation(m_ID, Name.c_str()), 1, &Value[0]);
    }

    void SetVec4(const std::string& Name, const float X, const float Y, const float Z, const float W) const
    {
        glUniform4f(glGetUniformLocation(m_ID, Name.c_str()), X, Y, Z, W);
    }

    void SetMat2(const std::string& Name, const glm::mat2& Mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ID, Name.c_str()), 1, GL_FALSE, &Mat[0][0]);
    }

    void SetMat3(const std::string& Name, const glm::mat3& Mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ID, Name.c_str()), 1, GL_FALSE, &Mat[0][0]);
    }

    void SetMat4(const std::string& Name, const glm::mat4& Mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, Name.c_str()), 1, GL_FALSE, &Mat[0][0]);
    }

private:
    void CheckCompileErrors(const GLuint Shader, const std::string& Type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (Type != "PROGRAM")
        {
            glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(Shader, 1024, NULL, infoLog);
                std::cout << Type << " shader failed to compile.\n" << infoLog <<
                        "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(Shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(Shader, 1024, NULL, infoLog);
                std::cout << Type << " shader failed to link.\n" << infoLog <<
                        "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

private:
    uint32_t m_ID;
};
