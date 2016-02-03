#ifndef XYZ_H
#define XYZ_H

#include "displayobject.h"
#include "vertex.h"

class XYZ : public DisplayObject
{
private:
    //GLuint m_vertexBuffer;
    GLuint m_colorBuffer;

public:
    XYZ();
    ~XYZ();
    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute=-1);
};

#endif // XYZ_H
