#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WINDOW_SIZE 500.0

GLboolean IsSphere = false;
GLboolean IsTorus = false;
GLboolean IsTeapot = false;

GLboolean IsTranslate = false;
GLboolean IsRotate = false;
GLboolean IsScale = false;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);

    // 좌측 버튼 메뉴
    if (IsTranslate) { // x축을 기준으로 0.2만큼 이동
        glTranslatef(0.2, 0.0, 0.0);
        IsTranslate = false;
    }
    else if (IsRotate) { // y축을 30만큼 기준으로 회전
        glRotatef(30, 0.0, 1.0, 0.0);
        IsRotate = false;
    }
    else if (IsScale) { // 2배 확대
        glScalef(2.0, 2.0, 2.0);
        IsScale = false;
    }

    // 우측 버튼 메뉴
    if (IsSphere) // Draw Sphere
        glutWireSphere(0.2, 15, 15);
    else if (IsTorus) // Draw Torus
        glutWireTorus(0.1, 0.3, 40, 40);
    else if (IsTeapot) // Draw Teapot
        glutWireTeapot(0.4);

    glFlush();
}

void MyRightMenu(int entryID) {
    if (entryID == 1) { // Draw Sphere
        IsSphere = true;
        IsTorus = false;
        IsTeapot = false;
    }
    else if (entryID == 2) { // Draw Torus
        IsSphere = false;
        IsTorus = true;
        IsTeapot = false;
    }
    else if (entryID == 3) { // Draw Teapot
        IsSphere = false;
        IsTorus = false;
        IsTeapot = true;
    }
    glutPostRedisplay();
}

void MyLeftMenu(int entryID) {
    if (entryID == 1) { // Translate: 0.2만큼 이동
        IsTranslate = true;
    }
    else if (entryID == 2) { // Rotate: 30만큼 회전
        IsRotate = true;
    }
    else if (entryID == 3) { // Scale: 크기 2배 확대
        IsScale = true;
    }
    glutPostRedisplay();
}

int main()
{
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("조정미");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    // 우측 버튼 메뉴
    GLint MyRightMenuID = glutCreateMenu(MyRightMenu);
    glutAddMenuEntry("Draw Sphere", 1);
    glutAddMenuEntry("Draw Torus", 2);
    glutAddMenuEntry("Draw Teapot", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // 좌측 버튼 메뉴
    GLint MyLeftMenuID = glutCreateMenu(MyLeftMenu);
    glutAddMenuEntry("Translate", 1);
    glutAddMenuEntry("Rotate", 2);
    glutAddMenuEntry("Scale", 3);
    glutAttachMenu(GLUT_LEFT_BUTTON);

    glutDisplayFunc(MyDisplay);
    glutMainLoop();

    return 0;
}