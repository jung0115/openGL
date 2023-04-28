#include <GL/glut.h>
#include <stdio.h>

GLboolean bLight0 = GL_TRUE, bLight1 = GL_FALSE;

GLfloat Ia = 0.5, Id = 0.5, Is = 0.5;
GLfloat Ka = 0.5, Kd = 0.5, Ks = 0.5, Sn = 25.0;

GLfloat spot_cutoff = 23.5;
GLfloat spot_expo = 2.0;

GLfloat Rx = 40.0, Ry = 30.0, Rz = 0.0;


void MyLightInit()
{
	// 전역주변광
	GLfloat MyGlobalAmbient[] = { 0.2, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, MyGlobalAmbient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);	// default
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);		// default

	// 0번 광원
	GLfloat light0_ambient[] = { Ia, 0.0, 0.0, 1.0 };
	GLfloat light0_diffuse[] = { Id, 0.0, 0.0, 1.0 };
	GLfloat light0_specular[] = { Is, Is, Is, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);		// Ia: 주변광
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);		// Id: 확산광
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);		// Is: 경면광

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);		// 상수항의 계수
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);		// 1차 항의 계수
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);		// 2차 항의 계수


	// 1번 광원
	GLfloat light1_ambient[] = { 0.0, Ia, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 0.0, Id, 0.0, 1.0 };
	GLfloat light1_specular[] = { Is, Is, Is, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);	// Ia: 주변광
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);	// Id: 확산광
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);	// Is: 경면광
}

void MyMaterialInit()
{
	GLfloat material_ambient[] = { Ka, Ka, Ka, 1.0 };
	GLfloat material_diffuse[] = { Kd, Kd, Kd, 1.0 };
	GLfloat material_specular[] = { Ks, Ks, Ks, 1.0 };
	GLfloat material_shiniess[] = { Sn };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);	// Ka: 주변광 계수
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);	// Kd: 확산광 계수
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);// Ks: 경면광 계수
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shiniess);// n: 광택 계수
}

void MyReshape(int w, int h) {
	if (w < h)
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	else
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);				//투상행렬
	glLoadIdentity();							//항등행렬 로드
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);	//평행투상
}

void DoKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
		// 주변광의 세기 및 계수 조절
	case 'q': { Ia += 0.1;	Ka += 0.1; }  break;
	case 'a': if (Ia > 0.1) { Ia -= 0.1;	Ka -= 0.1; }  break;

		// 확산광의 세기 및 계수 조절
	case 'e': { Id += 0.1;	Kd += 0.1; }  break;
	case 'd': if (Id > 0.1) { Id -= 0.1;	Kd -= 0.1; }  break;

		// 경면광의 세기 및 계수 조절
	case 'w': { Is += 0.1;	Ks += 0.1; }  break;
	case 's': if (Is > 0.1) { Is -= 0.1;	Ks -= 0.1; }  break;
	case 'n': Sn += 5; break;
	case 'm': Sn -= 5; break;

		// 스포트라인트 (조명각, 조명승수)
	case '1': spot_cutoff += 1.25;	break;
	case '2': spot_cutoff -= 1.25;	break;
	case '3': spot_expo += 1;	break;
	case '4': spot_expo -= 1;	break;

		// 회전
	case 'x': Rx += 10.0;	break;
	case 'y': Ry += 10.0;	break;
	case 'z': Rz += 10.0;	break;

	case 'i': // 초기화
		bLight0 = GL_TRUE; bLight1 = GL_FALSE;
		Ia = 0.5, Id = 0.5, Is = 0.5;				// 광원의 세기 
		Ka = 0.5, Kd = 0.5, Ks = 0.5, Sn = 25.0;	// 광원에 대한 반사 계수 (물체특성을 나타냄)
		spot_cutoff = 50.0;		// 스포트라이트 조명각 
		spot_expo = 2.0;		// 스포트라이트 조명승수
		Rx = 40.0, Ry = 30.0, Rz = 0.0;		// 회전각 
		break;
	}
	char info[128];
	sprintf_s(info, "a=(%.1f,%.1f), d=(%.1f,%.1f), s=(%.1f,%.1f,%.1f), spot_cutoff=(%.1f)", Ka, Ia, Kd, Id, Ks, Is, Sn, spot_cutoff);
	glutSetWindowTitle(info);
	MyLightInit();
	MyMaterialInit();
	glutPostRedisplay();
}

void MyOpenBox()
{
	// 앞
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, -0.3, 0.6);
	glVertex3f(0.5, -0.3, 0.6);
	glVertex3f(0.5, 0.3, 0.6);
	glVertex3f(-0.5, 0.3, 0.6);
	glEnd();

	// 뒤
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-0.5, -0.3, -0.6);
	glVertex3f(-0.5, 0.3, -0.6);
	glVertex3f(0.5, 0.3, -0.6);
	glVertex3f(0.5, -0.3, -0.6);
	glEnd();

	// 좌측
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-0.5, -0.3, 0.6);
	glVertex3f(-0.5, 0.3, 0.6);
	glVertex3f(-0.5, 0.3, -0.6);
	glVertex3f(-0.5, -0.3, -0.6);
	glEnd();

	// 우측
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.3, 0.6);
	glVertex3f(0.5, -0.3, -0.6);
	glVertex3f(0.5, 0.3, -0.6);
	glVertex3f(0.5, 0.3, 0.6);
	glEnd();

	// 하단
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-0.5, -0.3, 0.6);
	glVertex3f(-0.5, -0.3, -0.6);
	glVertex3f(0.5, -0.3, -0.6);
	glVertex3f(0.5, -0.3, 0.6);
	glEnd();

	/*
	// 상단
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-0.5, 0.3, 0.6);
		glVertex3f(0.5, 0.3, 0.6);
		glVertex3f(0.5, 0.3, -0.6);
		glVertex3f(-0.5, 0.3, -0.6);
	glEnd();
	*/
}

void DoMenu(int value)
{
	switch (value) {
	case 1:
		bLight0 = GL_TRUE;
		break;
	case 2:
		bLight0 = GL_FALSE;
		break;
	case 3:
		bLight1 = GL_TRUE;
		break;
	case 4:
		bLight1 = GL_FALSE;
		break;
	}
	glutPostRedisplay();
}

void DoDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	// 조명기능 활성화
	glEnable(GL_LIGHTING);

	// 0번 광원 배치
	if (bLight0)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	GLfloat light0_position[] = { -5.0, 5.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// 1번 광원 배치
	if (bLight1)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	GLfloat light1_position[] = { 5.0, 5.0, 5.0, 1.0 };	// 광원의 위치
	//GLfloat light1_position[] = {Px, Py, Pz, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	// 1번 광원 Spotlight
	GLfloat spot_direction[] = { -5.0, -5.0, -5.0 };	// 원점으로부터의 광원벡터 방향(원점-->좌표)
	//GLfloat spot_direction[] = {-Px, -Py, -Pz};	// 원점으로부터의 광원벡터 방향(원점-->좌표)
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);	// 조명각 0~90도(p.545)
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_expo);	// 조명승수 (광택계수와 유사)

	glPushMatrix();
	glRotatef(Rx, 1.0, 0.0, 0.0);
	glRotatef(Ry, 0.0, 1.0, 0.0);
	glRotatef(Rz, 0.0, 0.0, 1.0);
	MyOpenBox();
	glPopMatrix();

	glutSolidSphere(0.5, 50, 50);
	glFlush();
}

int main()
{
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 500);
	glutCreateWindow("OpenGL Lighting and Shading");
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	// 메뉴
	glutCreateMenu(DoMenu);
	glutAddMenuEntry("Light 0 ON", 1);
	glutAddMenuEntry("Light 0 OFF", 2);
	glutAddMenuEntry("Light 1 ON", 3);
	glutAddMenuEntry("Light 1 OFF", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	MyLightInit();		// 광원 설정
	MyMaterialInit();	// 광원의 계수 설정
	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(DoKeyboard);
	glutMainLoop();
	return 0;
}