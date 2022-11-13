// 후면제거(Backface Removal)
#include <glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, -0.3, -0.3, -1.0, 0.0, 1.0, 0.0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);		// default	반시계방향이 전면
    //glCullFace(GL_BACK);		// default	후면제거
    //glCullFace(GL_FRONT);
    //glCullFace(GL_FRONT_AND_BACK);
    glDisable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT, GL_FILL);	// default  GL_FILL
    //glPolygonMode(GL_BACK, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // 뒷면 그리기 ---------------------
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.3, -0.6);
    glVertex3f(-0.5, 0.3, -0.6);
    glVertex3f(0.5, 0.3, -0.6);
    glVertex3f(0.5, -0.3, -0.6);
    glEnd();

    // 좌측면 그리기 -------------------
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.3, 0.6);
    glVertex3f(-0.5, 0.3, 0.6);
    glVertex3f(-0.5, 0.3, -0.6);
    glVertex3f(-0.5, -0.3, -0.6);
    glEnd();

    // 아랫면 그리기 -------------------
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.3, -0.6);
    glVertex3f(0.5, -0.3, -0.6);
    glVertex3f(0.5, -0.3, 0.6);
    glVertex3f(-0.5, -0.3, 0.6);
    glEnd();

    // 앞면 그리기 ---------------------
    /*glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.3, 0.6);
    glVertex3f(0.5, -0.3, 0.6);
    glVertex3f(0.5, 0.3, 0.6);
    glVertex3f(-0.5, 0.3, 0.6);
    glEnd();*/

    // 우측면 그리기 -------------------
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -0.3, 0.6);
    glVertex3f(0.5, -0.3, -0.6);
    glVertex3f(0.5, 0.3, -0.6);
    glVertex3f(0.5, 0.3, 0.6);
    glEnd();

    // 윗면 그리기 -------------------
    glColor3f(0.0, 0.0, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.3, 0.6);
    glVertex3f(0.5, 0.3, 0.6);
    glVertex3f(0.5, 0.3, -0.6);
    glVertex3f(-0.5, 0.3, -0.6);
    glEnd();
    
    glFlush();
}

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Back-Facing Removal");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
// --- <실습 및 과제> -----------------------------------------
// Display the images (a)~(c) in fig. 8-17 (Text p.383) 
// -----------------------------------------------------------