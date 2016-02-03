attribute vec3 aVertexColor;
attribute vec3 aVertexPosition;
uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;

attribute vec2 aTextureCoordinates;
varying vec2 vTextureCoordinates;

varying vec3 vColor;

void main(void)
{
    gl_Position = uPMatrix*uMVMatrix * vec4(aVertexPosition, 1.0);
    vColor = aVertexColor;
}