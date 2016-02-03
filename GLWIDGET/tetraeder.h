#ifndef TETRAEDER_H
#define TETRAEDER_H

#include "displayobject.h"

class Tetraeder : public DisplayObject
{
private:

public:
    Tetraeder();
    ~Tetraeder();
    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute=-1);
};

#endif // TETRAEDER_H
