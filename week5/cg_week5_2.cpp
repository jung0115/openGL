#include <GL/glut.h>
#include <stdio.h>

void MyDisplay() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity(); // 초기화

    // a
    glColor3f(0.0, 0.0, 0.0);
    glutSolidTeapot(0.1);

    glPushMatrix();
        // b
        glTranslatef(0.15, 0.15, 0.15);
        glutSolidTeapot(0.1);

        glPushMatrix();
            // c
            glTranslatef(0.5, -0.1, 0.0);
            glRotatef(45, 0, 0, 1);
            glScaled(0.5, 0.5, 0.5);
            glutSolidTeapot(0.1);
        glPopMatrix();

        glPushMatrix();
            // d
            glColor3f(1.0, 0.0, 0.0);
            glTranslatef(-0.8, 0.3, 0.0);
            glScaled(2.0, 2.0, 2.0);
            glRotatef(90, 0, 1, 0);
            glutSolidTeapot(0.1);
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();
        // e
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(0.0, -0.5, 0.0);
        glutSolidTeapot(0.1);
    glPopMatrix();

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