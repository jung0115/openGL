#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
int Width, Height;

void Init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    // 기본 투상 방법을 평행 투상으로 설정.
    // 물체 크기의 2배 정도의 가시 부피가 설정됨.
    // 윈도우 크기에 의한 왜곡 방지 - 평행 투상
    GLdouble WidthFactor = (GLdouble)Width / 500.0;
    GLdouble HeightFactor = (GLdouble)Height / 500.0;
    glOrtho(-2.0 * WidthFactor, 2.0 * WidthFactor, -2.0 * HeightFactor, 2.0 * HeightFactor, 0.5, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawScene() {
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        // 가로 세로 크기가 4인 회색 사각형을 그림
        glBegin(GL_QUADS);
            glVertex3f(2.0, 0.0, 2.0);
            glVertex3f(2.0, 0.0, -2.0);
            glVertex3f(-2.0, 0.0, -2.0);
            glVertex3f(-2.0, 0.0, 2.0);
        glEnd();
    glPopMatrix();

    glColor3f(0.3, 0.3, 0.7);
    glPushMatrix();
        // 3차원 좌표 0.0, 0.0, -0.5에 WireTeaPot 생성
        glTranslatef(0.0, 0.0, -0.5);
        glutWireTeapot(1.0);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // 좌하단 뷰 포트
    glViewport(0, 0, Width / 2, Height / 2);
    glPushMatrix();
        // 카메라 위치: 0.0, 0.0, 1.0
        // 카메라 방향(초점): 0.0, 0.0, 0.0
        // 상향 벡터: 0.0, 1.0, 0.0
        // => +z축에서 바라본 측면도가 그려짐
        gluLookAt(0.0, 0.0, 1.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
        DrawScene();
    glPopMatrix();

    // 우하단 뷰 포트
    glViewport(Width / 2, 0, Width / 2, Height / 2);
    glPushMatrix();
        // 카메라 위치: 1.0, 0.0, 0.0
        // 카메라 방향(초점): 0.0, 0.0, 0.0
        // 상향 벡터: 0.0, 1.0, 0.0
        // => +x축에서 바라본 측면도가 그려짐
        gluLookAt(1.0, 0.0, 0.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
        DrawScene();
    glPopMatrix();

    // 좌상단 뷰 포트
    glViewport(0, Height / 2, Width / 2, Height / 2);
    glPushMatrix();
        // 카메라 위치: 0.0, 1.0, 0.0
        // 카메라 방향(초점): 0.0, 0.0, 0.0
        // 상향 벡터: 0.0, 0.0, -1.0
        // => +y축에서 내려다본 측면도가 그려짐
        gluLookAt(0.0, 1.0, 0.0,  0.0, 0.0, 0.0,  0.0, 0.0, -1.0);
        DrawScene();
    glPopMatrix();

    // 우상단 뷰 포트
    glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
    // 행렬 모드를 투상 행렬로 => 원근 투상을 적용하기 위해
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        // 현 투상행렬을 항등행렬로 초기화
        glLoadIdentity();
        // 원근 투상의 가시 부피 설정
        // 시야각: 30도, 종횡비: (GLdouble)Width / (GLdouble)Height, 전방 절단면: 3.0, 후방 절단면: 50
        // 윈도우 크기에 의한 왜곡을 방지하기 위해 종횡비를 윈도우 크기에 따라 변화 - 원근 투상
        gluPerspective(30, (GLdouble)Width / (GLdouble)Height, 3.0, 50.0);
        // 행렬 모드를 모델 뷰 행렬로 => 시점 좌표계는 모델 뷰 행렬에 반영되므로
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            // 카메라 위치: 5.0, 5.0, 5.0
            // 카메라 방향(초점): 0.0, 0.0, 0.0
            // 상향 벡터: 0.0, 1.0, 0.0
            gluLookAt(5.0, 5.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
            DrawScene();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glFlush();
}

void MyReshape(int w, int h) {
    Width = w;   Height = h;
    Init();
    glutPostRedisplay();
}

int main() {
    Width = 500; Height = 500;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");
    Init();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
}