#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GLUT_KEY_LEFT 100
#define GLUT_KEY_UP 101
#define GLUT_KEY_RIGHT 102
#define GLUT_KEY_DOWN 103

#define WINDOW_SIZE 500.0

float red = 1.0, green = 1.0, blue = 1.0;
float leftX = -0.5, rightX = 0.5, topY = 0.5, bottomY = -0.5;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(red, green, blue);
    
    glBegin(GL_POLYGON);
        glVertex3f(leftX, bottomY, 0.0);
        glVertex3f(rightX, bottomY, 0.0);
        glVertex3f(rightX, topY, 0.0);
        glVertex3f(leftX, topY, 0.0);
    glEnd();

    glFlush();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
    switch (KeyPressed){
        case 'r': // 빨간색으로 변경
            red = 1.0; green = 0.0; blue = 0.0; break;
        case 'g': // 초록색으로 변경
            red = 0.0; green = 1.0; blue = 0.0; break;
        case 'b': // 파란색으로 변경
            red = 0.0; green = 0.0; blue = 1.0; break;
        default:
            break;
    }

    glutPostRedisplay();
}

void MySpecialKeyboard(int KeyPressed, int X, int Y) {
    switch (KeyPressed) {
    case GLUT_KEY_LEFT: // 좌측으로 20px 이동
        leftX -= 20.0 / WINDOW_SIZE; rightX -= 20.0 / WINDOW_SIZE; break;
    case GLUT_KEY_RIGHT: // 우측으로 20px 이동
        leftX += 20.0 / WINDOW_SIZE; rightX += 20.0 / WINDOW_SIZE; break;
    case GLUT_KEY_UP: // 상단으로 20px 이동
        topY += 20.0 / WINDOW_SIZE; bottomY += 20.0 / WINDOW_SIZE; break;
    case GLUT_KEY_DOWN: // 하단으로 20px 이동
        topY -= 20.0 / WINDOW_SIZE; bottomY -= 20.0 / WINDOW_SIZE; break;
    default:
        break;
    }

    glFlush();
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
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecialKeyboard);
    glutMainLoop();

    return 0;
}