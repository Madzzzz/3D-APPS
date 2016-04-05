#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include "displayobject.h"

class TriangleSurface : public DisplayObject
{

private:
    void lesfil(std::string filnavn);

public:
    TriangleSurface();
    ~TriangleSurface();

    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint normalAttribute, GLint
              textureAttribute=-1);
};
#endif // TRIANGLESURFACE_H

