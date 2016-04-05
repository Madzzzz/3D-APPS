#ifndef PLANE_H
#define PLANE_H

#include "displayobject.h"
#include "vec3.h"

class Vertex;

class Plane : public DisplayObject
{
public:
    Plane();
    ~Plane();
    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute=-1);
};

#endif // PLANE_H


//plan som tinga står på, bare 4 vertexer rett fram
