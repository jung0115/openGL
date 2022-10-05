#include <GL/glut.h>
#include <stdio.h>

void MyDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(20.0);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);
        glVertex3f(0.0, 0.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.5, 0.5, 0.0);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 1.0, 0.0);
        // 수평 라인
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.8, 0.0, 0.0);

        // 대각선
        glVertex3f(-0.8, 0.8, 0.0);
        glVertex3f(0.8, -0.8, 0.0);
    glEnd();
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Default가 GL_FILL
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
        // 삼각형
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(-0.45, 0.0, 0.0);
        glVertex3f(-0.9, -0.9, 0.0);
        glVertex3f(0.0, -0.9, 0.0);
    glEnd();
    
    glFlush();
}

int main()
{
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("조정미");
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();

    return 0;
}