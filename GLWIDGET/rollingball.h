#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "vec3.h"
#include "oktaederball.h"
#include "displayobject.h"
#include "TriangleSurface.h"

class RollingBall : public OktaederBall
{
private:
    Vec3 m_position;
    Vec3 m_velocity;
    TriangleSurface* m_triangleSurface;

public:
    RollingBall(TriangleSurface* triangleSurface);
    void update(float t = 0.017f);
};

#endif // ROLLINGBALL_H
