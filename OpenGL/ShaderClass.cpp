#include "ShaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);

    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());

        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());

        in.close();
        return(contents);
    }

    throw(errno);
}

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
    std::string vertex_code = get_file_contents(vertex_file);
    std::string fragment_code = get_file_contents(fragment_file);

    const char* vertex_source = vertex_code.c_str();
    const char* fragment_source = fragment_code.c_str();

    // Create Vertex Shader Object and get reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertex_source, NULL);
    // Compile Vertex Shader into machine code
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragment_source, NULL);
    // Compile Fragment Shader into machine code
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");


    // Create Shader Program Object and get reference
    ID = glCreateProgram();
    // Attach Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Programd
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader Objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
    GLint has_compiled;
    char info_log[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);

        if (has_compiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);

            std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << info_log << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &has_compiled);

        if (has_compiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);

            std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << info_log << std::endl;
        }
    }
}
