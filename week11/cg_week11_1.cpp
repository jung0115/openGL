// 후면제거(Backface Removal)
#include <glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>


void MyDisplay() {
    GLdouble eqn1[4] = { 0.0, 1.0, 0.0, 0.0 }; // - 위
    GLdouble eqn2[4] = { 1.0, 0.0, 0.0, 0.0 }; // | 오른쪽
    GLdouble eqn3[4] = { 1.0, 1.0, 0.0, 0.0 }; // \ 우상단
    GLdouble eqn4[4] = { 1.0, 0.0, 0.0, 0.5 }; // | 절단선?이 왼쪽으로 0.5만큼 더 치우침

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);

    glTranslatef(0.0, 0.0, -5.0);
    //glRotated(90.0, 1.0, 0.0, 0.0);

    glClipPlane(GL_CLIP_PLANE0, eqn1);
    glEnable(GL_CLIP_PLANE0);

    glClipPlane(GL_CLIP_PLANE1, eqn4);
    glEnable(GL_CLIP_PLANE1);

    glutWireSphere(1.0, 20, 16);
    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 10.0);
}

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 400);
    glutCreateWindow("Clip Plane");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
}