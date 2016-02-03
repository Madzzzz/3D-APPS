#include "xyz.h"

XYZ::XYZ() : DisplayObject()
{
}

XYZ::~XYZ()
{
    //
}

void XYZ::initVertexBufferObjects()
{
    initializeOpenGLFunctions();

    m_vertices = new Vertex[6];

    //Possisjon
    m_vertices[0].set_xyz(0.0, 0.0, 0.0);
    m_vertices[1].set_xyz(1.0, 0.0, 0.0);
    m_vertices[2].set_xyz(0.0, 0.0, 0.0);
    m_vertices[3].set_xyz(0.0, 1.0, 0.0);
    m_vertices[4].set_xyz(0.0, 0.0, 0.0);
    m_vertices[5].set_xyz(0.0, 0.0, 1.0);

    //Farge
    m_vertices[0].set_rgb(1.0, 0.0, 0.0);
    m_vertices[1].set_rgb(1.0, 0.0, 0.0);
    m_vertices[2].set_rgb(0.0, 1.0, 0.0);
    m_vertices[3].set_rgb(0.0, 1.0, 0.0);
    m_vertices[4].set_rgb(0.0, 0.0, 1.0);
    m_vertices[5].set_rgb(0.0, 0.0, 1.0);

    //Sender vertex possisjon og fargedata til et buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(Vertex), m_vertices, GL_STATIC_DRAW);


}

void XYZ::draw(GLint positionAttribute, GLint colorAttribute, GLint /*textureAttribute*/)
{
    int offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), reinterpret_cast<const void*> (offset));

    offset = 3*sizeof(GLfloat);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), reinterpret_cast<const void*> (offset));

    glDrawArrays(GL_LINES, 0, 6);

}
