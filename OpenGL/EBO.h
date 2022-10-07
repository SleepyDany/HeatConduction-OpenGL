#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
    GLuint ID;

    EBO();
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void uploadBufferData(GLuint* indices, GLsizeiptr size);
    void Unbind();
    void Delete();
};

#endif
