#include "camera.h"

Camera::Camera()
{
    m_projectionMatrix.setToIdentity();
    m_viewMatrix.setToIdentity();
}

Camera::~Camera()
{

}

QMatrix4x4 Camera::getViewMatrix()              { return m_viewMatrix; }
QMatrix4x4 Camera::getProjectionMatrix()        { return m_projectionMatrix; }
/*
 *
void Camera::translate(float dx, float dy, float dz)
{
   m_position.x = dx;
   m_position.y = dy;
   m_position.z = dz;

   m_viewMatrix.translate(m_position.x, m_position.y, m_position.z);
}
*/
void Camera::setPosition(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}

void Camera::view()
{
    m_viewMatrix.translate(m_position.x, m_position.y, m_position.z);
}

void Camera::setToIdentity()
{
   m_viewMatrix.setToIdentity();
   m_projectionMatrix.setToIdentity();
}

void Camera::perspective(float verticalAngle, float aspectRatio, float nearPlane, float farPlane)
{
    m_projectionMatrix.perspective(verticalAngle, aspectRatio, nearPlane, farPlane);
}

void Camera::zoomin()
{
    m_position.z += DZ;
}


void Camera::zoomout()
{
    m_position.z -= DZ;
}

void Camera::left()
{
    m_position.x -= DX;
    //qDebug() << "Venstre";
}

void Camera::right()
{
    m_position.x += DX;
}

void Camera::up()
{
     m_position.y += DY;
}

void Camera::down()
{
     m_position.y -= DY;
}
void Camera::home()
{

}
