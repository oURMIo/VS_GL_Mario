// ������ ����������� ��������� � ����������� GLUT
#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include "GL/glut.h"   // ���� ����������� ����������

const int nGround = 41;
static float yGround[nGround] = {
	50, 50, 50, 50, 70, 70, 55, 58, 60, 77, 80, 75, 82, 84, 87, 90, 92, 93, 93, 95,
	90, 90, 91, 93, 90, 100, 99, 95, 90, 85, 81, 84, 93, 95, 99, 101, 110, 105, 90, 95, 95 };	
//static float yGround[nGround];

float me_step = 400.0 / (nGround - 1);
int me_nx = 1;
int me_ny = 1;
float me_x = me_nx * me_step;
float me_y = me_ny * me_step;

static int start_ground = 0;

void circle(float x, float y, float r)
{
	glBegin(GL_POLYGON);
	for (float a = 0.0; a < 6.29; a += 0.01)
	{
		glVertex2f(x + r*cos(a), y + r*sin(a));
	}
	glEnd();
}

void ellipse(float x, float y, float r, float r1)
{
	glBegin(GL_POLYGON);
	for (float a = 0.0; a < 6.29; a += 0.01)
	{
		glVertex2f(x + r*cos(a), y + r1*sin(a));
	}
	glEnd();
}

void draw_sky()
{
	// BACKGRAUND
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0, 0);
	glVertex2f(400, 0);
	glColor3f(0.5, 0.0, 0.1);
	glVertex2f(400, 300);
	glVertex2f(0, 400);
	glEnd();
}


void draw_me()
{
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(me_x - 10, me_y - 10, 0.0);
	glVertex3f(me_x - 10, me_y + 10, 0.0);
	glVertex3f(me_x + 10, me_y + 10, 0.0);
	glVertex3f(me_x + 10, me_y - 10, 0.0);
	glEnd();
}

void draw_ground()
{
	glColor3f(0.1, 1.0, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(400, 0);
	glVertex2f(0, 0);
	for (int i = start_ground; i < nGround - 1; i++)
	{
		glBegin(GL_POLYGON);
		glVertex2f(i * me_step, yGround[i]);
		glVertex2f((i + 1) * me_step, yGround[i + 1]);
		glVertex2f((i + 1) * me_step, 0);
		glVertex2f(i * me_step, 0);
		glEnd();
		if (i == nGround - 1) i = 0;
		if (i == start_ground - 1) break;
	}

}

void display()  /// ��������� �����
{
	glClear(GL_COLOR_BUFFER_BIT); // ������� ������ ������ (��������� �������)
	glClearColor(0.0, 0.5, 1.0, 0.0);   // ��������� ����� ������
	glLineWidth(2);
	glColor3f(0.0, 0.5, 0.0);     // ��������� ����� ��������� (� �������, � �������)
	//glBegin(GL_POLYGON); // ������ ��������� ��������������
	//glVertex2f(10, 10);  // ������� �������������� �� �������
	//glVertex2f(30, 10);
	//glVertex2f(30, 20);
	//glVertex2f(10, 20);
	//glEnd();             // ����� ��������� ��������������

	// ����
	draw_sky();
	draw_ground();
	draw_me();

	glFlush();   // ��������� ������ � ������������� �������
	glFinish();  // ���������� ����� (��������� �������)
}

void reshape(int x, int y)    // ��������� ��������� �������� ����
{
	glViewport(0, 0, x, y);   // ��������� ������� ��������� "�� �� ����"  (��������� �������)
	glMatrixMode(GL_PROJECTION); glLoadIdentity();  // "�����" ������ ��������� ��������� (��������� �������)
	glMatrixMode(GL_MODELVIEW);  glLoadIdentity();  // "�����" ������ ��������� ��������� (��������� �������)
	glOrtho(0.0, 400.0, 0.0, 300.0, -1.0, 1.0); 	// !!!!! ��������� ����� ������� ��������� (�����, ������, ������)
}

/*
void mouseClick(int button, int state, int x, int y)  // ��������� ������� ������ ����
{
	if (GLUT_LEFT_BUTTON == button)
	{
		start_ground++;
		if (start_ground > nGround) start_ground = 0;
	}
}
*/

void keyboard2(int key, int x, int y)    // ��������� ������� ������������ �������
{
	if (GLUT_KEY_LEFT == key) if (me_nx > 0) { me_nx = me_nx - 1; me_x = me_nx*me_step; } // GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_UP
	if (GLUT_KEY_RIGHT == key) if (me_nx < nGround){ me_nx = me_nx + 1; me_x = me_nx*me_step; }
	if (GLUT_KEY_DOWN == key) { me_ny = me_ny - 1; me_y = me_ny*me_step; }
	if (GLUT_KEY_UP == key) { me_ny = me_ny + 1; me_y = me_ny*me_step; }
}

void keyboard(unsigned char key, int x, int y)  // ��������� ������� ������������ �������
{
	if (key == 27)   // ���� ����� ESC...
		exit(0);     // �� ��������� ����������
}

void step_ground()
{
	float temp = yGround[0];
	for (int i = 0; i < nGround - 1; i++)
		yGround[i] = yGround[i + 1];
	yGround[nGround - 1] = temp;
}

void timer1(int param)
{
	step_ground();
	display();
	glutTimerFunc(100, timer1, 0);   // ������������ ���������� ������ �������
}

int _tmain(int argc, _TCHAR* argv[])   // !!! ������ �������� ���������
{
	glutInit(&argc, (char**)argv);    // ������������� ������� (��������� �������)

	glutInitWindowSize(1024, 768);     // ��������� �������� ���� 
	glutInitWindowPosition(100, 100); // ��������� ������� ���� ������������ ������

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH); // ����� ����������� (��. �������)
	glutCreateWindow("���������� ������");  // �������� ���� � ��������� ������ � ���������

	glutDisplayFunc(display);    // ������� �������-����������� ������� "���������" (WM_PAINT � WinAPI)
	glutIdleFunc(display);       // ������� �������-����������� ������� "���������" (WM_PAINT � WinAPI)
	glutReshapeFunc(reshape);    // ������� �������-����������� ������� "���������" (WM_SIZE � WinAPI)
//	glutMouseFunc(mouseClick);   // ������� �������-����������� ������� "���������" (WM_LBUTTONPRESSED)
	glutKeyboardFunc(keyboard);  // ������� �������-����������� ������� "���������" (WM_KEYDOWN � WinAPI)
	glutSpecialFunc(keyboard2);  // ������� �������-����������� ������� "���������" (WM_KEYDOWN � WinAPI)
	glutTimerFunc(1000, timer1, 0);

	glutMainLoop();				 // ������ ��������� ����� ���������
	return 0;                    // ���������� �������� ���������
}

/*
void spiralQuad(float x, float y)
{
float d_left = 0, d_right = 0, d_up = 0, d_down = 0, D = 5.0;

glBegin(GL_LINE_STRIP); // ������ ��������� ��������������
for (int i = 0; i < 8; i++)
{
glVertex2f(x - d_left, y + d_up);
d_right += D;
d_left += D;
glVertex2f(x + d_right, y + d_up);
d_up += D;
d_down += D;
glVertex2f(x + d_right , y - d_up);
glVertex2f(x - d_left, y - d_down);
}
glEnd();
}
*/