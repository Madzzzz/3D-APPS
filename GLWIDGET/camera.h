#ifndef CAMERA_H
#define CAMERA_H

#include <QtGui/QMatrix4x4>
#include "vec3.h"

class Camera
{
private:
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
    Vec3 m_position;
    static const int DX=1.0f;
    static const int DY=1.0f;
    static const int DZ=1.0f;

public:
    // Vi trenger "view-delen" av modelviewmatrisen
    // og lar navnet reflektere dette


    Camera();
    ~Camera();

    QMatrix4x4 getViewMatrix();
    QMatrix4x4 getProjectionMatrix();

    // Forslag til aktuelle funksjoner:
    //void pitch();
    //void yaw();
    //void roll();
    void setToIdentity();
    void perspective(float verticalAngle, float aspectRatio, float nearPlane, float farPlane);
    void zoomin();
    void zoomout();
    void left();
    void right();
    void up();
    void down();
    void home();
    void setPosition(float x, float y, float z);
    void view();
};

#endif // CAMERA_H
