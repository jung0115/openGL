#include <GL/glut.h>

#define WIDTH 3
#define HEIGHT 3

GLubyte MyTexture[WIDTH][HEIGHT][3]; // 2차원 텍스처 영상을 위한 배열

GLfloat mat_diffuse[] = { 0.25, 0.25, 1., 0. };   // 확산 반사
GLfloat mat_specular[] = { 1., 1., 1., 0. };      // 경면 반사
GLfloat light_position[] = { 10., 10., 20., 1. }; // 광원의 위치

GLfloat MyPlane111[] = { 1.5, 1.5, 1.5, 0.0 };  // 기준 평면
GLfloat MyPlane100[] = { 1.5, 0.0, 0.0, 0.0 };  // 기준 평면
GLfloat Rx = 0.0, Ry = 0.0, Rz = 0.0;           // 회전축

// 코드 11-2 체크무늬 텍스처
void FillMyTextureCheck() {
	int s, t;
	for (s = 0; s < WIDTH; s++) {
		for (t = 0; t < HEIGHT; t++) {
			GLubyte intensity = ((s + t) % 2) * 255;
			MyTexture[s][t][0] = intensity;
			MyTexture[s][t][1] = intensity;
			MyTexture[s][t][2] = intensity;
		}
	}
}

void MyInit() {
	// 조명과 음영 설정
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);    // 조명 (물체의 특성)
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  // 조명의 위치

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);  // 은면 제거
	glShadeModel(GL_SMOOTH);  // 구로 쉐이딩

	FillMyTextureCheck(); // 텍스처로 사용할 영상 만들기(텍스처 영상)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB,
		GL_UNSIGNED_BYTE, &MyTexture[0][0][0]);

	// 텍스처 파라미터 설정(p.606)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D); // 텍스처 활성화

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, MyPlane111); // 기준평면
	//glTexGenfv(GL_S, GL_OBJECT_PLANE, MyPlane100);

	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	//glTexGenfv(GL_T, GL_OBJECT_PLANE, MyPlane111);
	//glTexGenfv(GL_T, GL_OBJECT_PLANE, MyPlane100);

	glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40., (GLfloat)w / (GLfloat)h, 1., 10.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glTranslatef(0., 0., -1);  // 원구를 뒤쪽으로 이동
}

void DoKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		case '1': Rx += 1; break;
		case '2': Ry += 1; break;
		case '3': Rz += 1; break;
		case 'i': Rx = Ry = Rz = 0;; break;   // 초기 위치
	}

	glutPostRedisplay();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotatef(Rx, 1.0, 0.0, 0.0);
		glRotatef(Ry, 0.0, 1.0, 0.0);
		glRotatef(Rz, 0.0, 0.0, 1.0);
		glutSolidSphere(1.5, 50, 50);
	glPopMatrix();

	glutSwapBuffers();
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("2D Texture to Shpere");
	glutKeyboardFunc(DoKeyboard);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);
	MyInit();
	glutMainLoop();
	return 0;
}

