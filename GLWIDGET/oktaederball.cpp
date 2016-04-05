// OktaederBall
// Approksimasjon av kule med rekursiv oktaeder subdivisjon
#include <iostream>
#include <sstream>
#include "oktaederball.h"
#include "vertex.h"

//!
//! \brief OktaederBall::OktaederBall()
//! \param n - the recursion level (default is 0 which makes the original Octahedron)
//!
//! The number of (duplicated) vertices are calculated based on the parameter n - the recursion level.
//! Initially we have 8 triangles, each with 3 vertices.
//! A subdivision consists of
//! - compute the midpoint of each edge in a triangel
//! - add these midpoint as vertices
//! - make three new edges by connecting new vertices
//! - preserve orientation
//! - move the three new points on the unit ball's surface by normalizing. Remember the vertex vector
//! is also a normal to the ball's surface.
//! The formula for the number of vertices is
//! m_antallVertices = 3 * 8 * 4^n
//! where
//! - 3 comes from the number of vertices in a triangle,
//! - 8 comes from the original number of triangles in a regular Octahedron
//! - n is the recursion level (number of repeated subdivisions)
//!
OktaederBall::OktaederBall(int n) : m_rekursjoner(n), m_indeks(0), DisplayObject()
{
    m_antallVertices = 3 * 8 * pow(4, m_rekursjoner);
    m_vertices = new Vertex[m_antallVertices];
    //qDebug() << "OktaederBall::OktaederBall()";
    oktaederUnitBall();
}

//!
//! \brief OktaederBall::~OktaederBall() virtual destructor
//!
OktaederBall::~OktaederBall()
{
    std::cout << "OktaederBall::~OktaederBall()" << std::endl;
    //delete [] m_vertices;
    std::cout << "OktaederBall::~OktaederBall() - vertices deleted" << std::endl;
}

// Parametre inn: xyz koordinatene til et triangle v1, v2, v3 ccw
// Bevarer orienteringen av hjørnene
//!
//! \brief OktaederBall::lagTriangel()
//! \param v1 - position on the unit ball for vertex 1
//! \param v2 - position on the unit ball for vertex 2
//! \param v3 - position on the unit ball for vertex 3
//!
//! lagTriangel() creates vertex data for a triangle's 3 vertices. This is done in the
//! final step of recursion.
//!
void OktaederBall::lagTriangel(const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
    m_vertices[m_indeks].set_xyz(v1.x, v1.y, v1.z);
    m_vertices[m_indeks].set_normal(v1.x, v1.y, v1.z);
    m_vertices[m_indeks++].set_st(0.0f, 0.0f);
    m_vertices[m_indeks].set_xyz(v2.x, v2.y, v2.z);
    m_vertices[m_indeks].set_normal(v2.x, v2.y, v2.z);
    m_vertices[m_indeks++].set_st(1.0f, 0.0f);
    m_vertices[m_indeks].set_xyz(v3.x, v3.y, v3.z);
    m_vertices[m_indeks].set_normal(v3.x, v3.y, v3.z);
    m_vertices[m_indeks++].set_st(0.5f, 1.0f);
    /*
    m_ballVertices[m_indeks++] = v1.x;
    m_ballVertices[m_indeks++] = v1.y;
    m_ballVertices[m_indeks++] = v1.z;
    m_ballVertices[m_indeks++] = v2.x;
    m_ballVertices[m_indeks++] = v2.y;
    m_ballVertices[m_indeks++] = v2.z;
    m_ballVertices[m_indeks++] = v3.x;
    m_ballVertices[m_indeks++] = v3.y;
    m_ballVertices[m_indeks++] = v3.z;

    std::ostringstream oss;
    if(m_indeks > 8)
        for(int i=m_indeks-9; i<m_indeks; i++)
            oss << m_ballVertices[i] << ", ";
    qDebug() << oss.str().c_str();

    Vec3 w = v2 - v1; // gir v1v2
    Vec3 x = v3 - v1; // gir v1v3
    Vec3 y = w ^ x;   // vektorprodukt
    float l = y*y;
    l = sqrt(l);

    qDebug() << l << "antall vertices " << m_antallVertices << "indeks " << m_indeks;
    */
}

// Rekursiv subdivisjon av triangel
//!
//! \brief OktaederBall::subDivide() recursive subdivision of a triangel
//! \param a coordinates for vertex a
//! \param b coordinates for vertex b
//! \param c coordinates for vertex c
//! \param n level of recursion
//!
//! The function tests
//! (if n>0)
//! - three new edge midpoints are computed and normalized,
//! - four new calls to subDivide() is done - one for each new triangle, preserving orientation
//! and with decreased parameter n
//! else
//! - call lagTriangel(a, b, c)
//!
void OktaederBall::subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n)
{
    if (n>0) {
        Vec3 v1 = a+b; v1.normalize();
        Vec3 v2 = a+c; v2.normalize();
        Vec3 v3 = c+b; v3.normalize();
        subDivide(a, v1, v2, n-1);
        subDivide(c, v2, v3, n-1);
        subDivide(b, v3, v1, n-1);
        subDivide(v3, v2, v1, n-1);
    } else {
        lagTriangel(a, b, c);
    }
}

//!
//! \brief OktaederBall::oktaederUnitBall() creates 8 unit ball vertices and call subDivide()
//!
//! If the parameter n of the construktor OktaederBall() is zero, the result will be the
//! original octahedron consisting of 8 triangles with duplicated vertices.
//!
void OktaederBall::oktaederUnitBall()
{
    Vec3 v0(0, 0, 1);
    Vec3 v1(1, 0, 0);
    Vec3 v2(0, 1, 0);
    Vec3 v3(-1, 0, 0);
    Vec3 v4(0, -1, 0);
    Vec3 v5(0, 0, -1);

    subDivide(v0, v1, v2, m_rekursjoner);
    subDivide(v0, v2, v3, m_rekursjoner);
    subDivide(v0, v3, v4, m_rekursjoner);
    subDivide(v0, v4, v1, m_rekursjoner);
    subDivide(v5, v2, v1, m_rekursjoner);
    subDivide(v5, v3, v2, m_rekursjoner);
    subDivide(v5, v4, v3, m_rekursjoner);
    subDivide(v5, v1, v4, m_rekursjoner);
}

//!
//! \brief OktaederBall::initVertexBufferObjects() calls glGenBuffers(), glBindBuffer() and glBufferdata()
//! for using later use of glDrawArrays()
//!
void OktaederBall::initVertexBufferObjects()
{
    initializeOpenGLFunctions();

    // Skal nå sende all vertex og color data til ett buffer
    //int lengde = m_antallVertices * 8;//sizeof(Vertex)/sizeof(GLfloat);
    //float* bufferData = new float[lengde];
    //data(bufferData);
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_antallVertices*sizeof(Vertex),m_vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, lengde, bufferData, GL_STATIC_DRAW);
    //qDebug() << "OktaederBall::initVertexBufferObjects()";
}

//!
//! \brief OktaederBall::draw() draws a ball using glDrawArrays()
//! \param positionAttribute    vertex shader variable for position
//! \param normalAttribute      vertex shader variable for normal or color
//! \param textureAttribute     vertex shader variable for texture coordinates (optional)
//!
//! draw()
//! - glBindBuffer()
//! - glVertexAttribPointer()
//! - glBindTexture()
//! - glVertexAttribPointer()
//! - glDrawArrays() with GL_TRIANGLES
//!
void OktaederBall::draw(GLint positionAttribute, GLint normalAttribute, GLint textureAttribute)
{
    //qDebug() << "OktaederBall::draw" << positionAttribute << normalAttribute << textureAttribute;
    // Har en array av vertices som også er normaler
    //initializeOpenGLFunctions();
    int offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 3*sizeof(GL_FLOAT) går også bra!?
    offset = 3*sizeof(GLfloat); // samme for normalene
    //glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);

    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset)); /// stride 3*sizeof(GL_FLOAT) går også bra!?
//    offset = 6*sizeof(GLfloat);
//    glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
/// Tekstur
    glBindTexture(GL_TEXTURE_2D, m_texture); // denne må med
    if (textureAttribute != -1)
    {
        //glUniform1i(colorAttribute, 0);
        offset = 6*sizeof(GLfloat);
        //glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
        glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*> (offset));
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, m_tekstur);
    }
    //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    //qDebug() << "m_lengde 72? " << m_lengde;
    glDrawArrays(GL_TRIANGLES, 0, m_antallVertices);//m_antallVertices);
    //qDebug() << "Plan::draw() " << ++i;
}
// Funksjon til bruk dersom m_vertices arrayen ikke kan sendes uten casting til buffer
// - men det kan den jo
void OktaederBall::data(float v[]) const
{
    int k=0;
    for (int i=0; i<m_antallVertices; i++)
    {
        float vdata[8];
        m_vertices[i].data(vdata);
        for (int j=0; j<8; j++)
            v[k++] = vdata[j];
    }
}
