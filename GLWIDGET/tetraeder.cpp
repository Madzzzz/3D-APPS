#include <QDebug>
#include "tetraeder.h"
#include "vertex.h"

Tetraeder::Tetraeder() : DisplayObject()
{
}

Tetraeder::~Tetraeder()
{
    //
}

void Tetraeder::initVertexBufferObjects()
{
    // Trenger ikke disse lenger
/*    GLfloat vertices[] = {
        0.0, 		0.0, 		1.0,
        0.0, 		0.942809,  	-0.333333,
       -0.816497, 	-0.471405,  	-0.333333,
       0.816497, 	-0.471405,  	-0.333333,
    };

    GLfloat colors[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        1.0, 1.0, 0.0, 1.0
    };
*/
    GLubyte indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 3, 1,
    3, 2, 1
    };

    // Lager en array av strukturer (men uten normal og tekstur foreløpig
    Vertex v[4];
    v[0].set_xyz(0.0, 0.0, 1.0);
    v[0].set_rgb(1.0, 0.0, 0.0);
    v[1].set_xyz(0.0, 0.942809, -0.333333);
    v[1].set_rgb(0.0, 1.0, 0.0);
    v[2].set_xyz(-0.816497, -0.471405, -0.333333);
    v[2].set_rgb(0.0, 0.0, 1.0);
    v[3].set_xyz(0.816497, -0.471405, -0.333333);
    v[3].set_rgb(1.0, 1.0, 0.0);
    v[0].set_st(0.0, 0.0);
    v[1].set_st(1.0, 0.0);
    v[2].set_st(0.0, 1.0);
    v[3].set_st(1.0, 1.0);

    // Gjør om til å kunne bruke drawArrays med duplisering
    Vertex w[12];
    int k=0;
    for (int i= indices[0]; i<12; i++)
        w[k++]=v[i];

    initializeOpenGLFunctions();

    // Skal nå sende all vertex og color data til ett buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vertex), v, GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12*sizeof(GLubyte), indices, GL_STATIC_DRAW);
}

// Se også Programming Guide Example 6-6
void Tetraeder::draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute)
{
    initializeOpenGLFunctions();
    // Har en array av strukturer (4 Vertex objekter) som skal splittes på to
    // attributter i vertex shader. stride blir her størrelsen av hver struktur
    // Må bruke offset for start
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); /// stride 3*sizeof(GL_FLOAT) går også bra!?

/// Hva med index i glVertexAttribPointer
    //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    /// Peker til color
    int offset = 3*sizeof(GLfloat);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 4*sizeof(GL_FLOAT) går også bra!?

    if (textureAttribute != -1)
    {
        offset = 6*sizeof(GLfloat);
        glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<const void*>(offset));
    }
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, 0); // Nytt

}
