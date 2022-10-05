#include <GL/glut.h>
#include <stdio.h>

void MyDisplay() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity(); // 초기화

    glScalef(0.5, 1.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.5);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5, -0.5);
    glEnd();

    glLoadIdentity(); // 초기화

    glRotatef(90, 1, 0, 0);
    // x축으로 90도 rotate했으므로 화면상의 수직좌표가 z축이 됨
    glTranslatef(0.75, 0.0, -0.75);
    glScalef(0.25, 0.25, 0.25);

    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(0.5, 10, 20);

    glFlush();
}

int main()
{
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");
    glutDisplayFunc(MyDisplay);
    glutMainLoop();

    return 0;
}