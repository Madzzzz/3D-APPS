#include <QDebug>
#include <QImage>
#include <cstdio>
#include <iostream>
#include "trianglesurface.h"
#include "vertex.h"
#include "fil.h"

TriangleSurface::TriangleSurface() : DisplayObject()
{
    lesfil("C:/sUsers/mads/Documents/GitHub/3D-APPS/GLWIDGETDATA/Plandata.txt");
}

TriangleSurface::~TriangleSurface()
{
    qDebug() << "TriangleSurface::~TriangleSurface()";
    delete [] m_vertices;
    qDebug() << "TriangleSurface::~TriangleSurface()";
}

void TriangleSurface::lesfil(std::string filnavn)
{
    std::cout << "TriangleSurface::lesfil()" << std::endl;
    Fil::les(filnavn, m_vertices, m_antallVertices);
    std::cout << "antall " << m_antallVertices << std::endl;
    for (int i=0; i<m_antallVertices; i++)
        std::cout << m_vertices[i] << " fra TriangleSurface::lesfil()" <<
                     std::endl;
}

void TriangleSurface::initVertexBufferObjects()
{
    initializeOpenGLFunctions();
    // Unødvendig å gjøre dette, siden m_vertices kan sendes inn uten cast med glBufferData
    //float* bufferData = new float[m_antallVertices*sizeof(Vertex)];
    //data(bufferData);
    // Skal nå sende all vertex og color data til ett buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_antallVertices*sizeof(Vertex), m_vertices,
                 GL_STATIC_DRAW);
    qDebug() << "TriangleSurface::initVertexBufferObjects()";
}

void TriangleSurface::draw(GLint positionAttribute, GLint normalAttribute, GLint
                           textureAttribute)
{
    // Har en array av strukturer (noen Vertex objekter) som skal splittes på to
    // attributter i vertex shader. stride blir her størrelsen av hver struktur
    // Må bruke offset for start
    initializeOpenGLFunctions();//makeCurrent();
    int offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), reinterpret_cast<const void*> (offset));
    offset = 3*sizeof(GLfloat);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), reinterpret_cast<const void*> (offset));
    // Tekstur
    if (textureAttribute != -1)
    {
        //glUniform1i(colorAttribute, 0);
        offset = 6*sizeof(GLfloat);
        //glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
        glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), reinterpret_cast<const void*> (offset));
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
    //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glDrawArrays(GL_TRIANGLES, 0, m_antallVertices);
    //qDebug() << "TriangleSurface::draw() " << ++i;
}

