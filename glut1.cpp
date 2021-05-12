// Пример графической программы с библиотекой GLUT
#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include "GL/glut.h"   // Файл графической библиотеки

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

void display()  /// Отрисовка кадра
{
	glClear(GL_COLOR_BUFFER_BIT); // очистка буфера экрана (служебная команда)
	glClearColor(0.0, 0.5, 1.0, 0.0);   // установка цвета экрана
	glLineWidth(2);
	glColor3f(0.0, 0.5, 0.0);     // установка цвета рисования (и контура, и заливки)
	//glBegin(GL_POLYGON); // начало рисования многоугольника
	//glVertex2f(10, 10);  // вершины многоугольника по очереди
	//glVertex2f(30, 10);
	//glVertex2f(30, 20);
	//glVertex2f(10, 20);
	//glEnd();             // конец рисования многоугольника

	// небо
	draw_sky();
	draw_ground();
	draw_me();

	glFlush();   // окончание работы с промужеточным буфером
	glFinish();  // завершение кадра (служебная команда)
}

void reshape(int x, int y)    // Обработка изменения размеров окна
{
	glViewport(0, 0, x, y);   // установка области рисования "во всё окно"  (служебная команда)
	glMatrixMode(GL_PROJECTION); glLoadIdentity();  // "сброс" матриц пересчёта координат (служебная команда)
	glMatrixMode(GL_MODELVIEW);  glLoadIdentity();  // "сброс" матриц пересчёта координат (служебная команда)
	glOrtho(0.0, 400.0, 0.0, 300.0, -1.0, 1.0); 	// !!!!! Установка своей системы координат (левая, правая, нижняя)
}

/*
void mouseClick(int button, int state, int x, int y)  // Обработка нажатия кнопки мыши
{
	if (GLUT_LEFT_BUTTON == button)
	{
		start_ground++;
		if (start_ground > nGround) start_ground = 0;
	}
}
*/

void keyboard2(int key, int x, int y)    // Обработка нажатия двухбайтовой клавиши
{
	if (GLUT_KEY_LEFT == key) if (me_nx > 0) { me_nx = me_nx - 1; me_x = me_nx*me_step; } // GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_UP
	if (GLUT_KEY_RIGHT == key) if (me_nx < nGround){ me_nx = me_nx + 1; me_x = me_nx*me_step; }
	if (GLUT_KEY_DOWN == key) { me_ny = me_ny - 1; me_y = me_ny*me_step; }
	if (GLUT_KEY_UP == key) { me_ny = me_ny + 1; me_y = me_ny*me_step; }
}

void keyboard(unsigned char key, int x, int y)  // Обработка нажатия однобайтовой клавиши
{
	if (key == 27)   // если нажат ESC...
		exit(0);     // то завершаем приложение
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
	glutTimerFunc(100, timer1, 0);   // планирование следующего вызова функции
}

int _tmain(int argc, _TCHAR* argv[])   // !!! начало основной программы
{
	glutInit(&argc, (char**)argv);    // инициализация графики (служебная команда)

	glutInitWindowSize(1024, 768);     // установка размеров окна 
	glutInitWindowPosition(100, 100); // установка позиции окна относительно экрана

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH); // режим отображения (сл. команда)
	glutCreateWindow("Одномерный массив");  // Создание окна с указанием текста в заголовке

	glutDisplayFunc(display);    // задание функции-обработчика события "отрисовка" (WM_PAINT в WinAPI)
	glutIdleFunc(display);       // задание функции-обработчика события "отрисовка" (WM_PAINT в WinAPI)
	glutReshapeFunc(reshape);    // задание функции-обработчика события "отрисовка" (WM_SIZE в WinAPI)
//	glutMouseFunc(mouseClick);   // задание функции-обработчика события "отрисовка" (WM_LBUTTONPRESSED)
	glutKeyboardFunc(keyboard);  // задание функции-обработчика события "отрисовка" (WM_KEYDOWN в WinAPI)
	glutSpecialFunc(keyboard2);  // задание функции-обработчика события "отрисовка" (WM_KEYDOWN в WinAPI)
	glutTimerFunc(1000, timer1, 0);

	glutMainLoop();				 // запуск основного цикла программы
	return 0;                    // завершение основной программы
}

/*
void spiralQuad(float x, float y)
{
float d_left = 0, d_right = 0, d_up = 0, d_down = 0, D = 5.0;

glBegin(GL_LINE_STRIP); // начало рисования многоугольника
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