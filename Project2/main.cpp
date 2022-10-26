#include <GL/freeglut.h>
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(6.0f, -15.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Куб
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-2, 2, 2);
	glVertex3f(-6, 2, 2);
	glVertex3f(-6, -2, 2);
	glVertex3f(-2, -2, 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-2, 2, -2);
	glVertex3f(-6, 2, -2);
	glVertex3f(-6, -2, -2);
	glVertex3f(-2, -2, -2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-6, -2, -2);
	glVertex3f(-6, -2, 2);
	glVertex3f(-2, -2, 2);
	glVertex3f(-2, -2, -2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-6, 2, -2);
	glVertex3f(-6, 2, 2);
	glVertex3f(-2, 2, 2);
	glVertex3f(-2, 2, -2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-6, 2, -2);
	glVertex3f(-6, 2, 2);
	glVertex3f(-6, -2, 2);
	glVertex3f(-6, -2, -2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-2, 2, -2);
	glVertex3f(-2, 2, 2);
	glVertex3f(-2, -2, 2);
	glVertex3f(-2, -2, -2);
	glEnd();

	// Пирамида
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(6, -2, -2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2, -2, -2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(4, -2, 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2, -2, -2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(4, -2, 2);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(4, 2, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2, -2, -2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(6, -2, -2);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(4, 2, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(4, 2, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(6, -2, -2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(4, -2, 2);
	glEnd();

	glutSwapBuffers();//прорисовываем буфер на экран
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);//начальная инициализация окна
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//установка режима отображения
	glutInitWindowSize(600,600);//размер окна
	glutInitWindowPosition(200, 200);//начальная позиция на экране
	glutCreateWindow("Lab2");//заголовок окна
	glClearColor(0, 0, 0, 0);//цвет фона

	// настройка проекции
	glMatrixMode(GL_PROJECTION);//режим матрицы
	glLoadIdentity();//отчищает матрицу

	glutDisplayFunc(display);//функция которой мы передаем имя функции для отрисовки окна. 
	glutReshapeFunc(changeSize);//подстройка размеров изображения
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();//запускаем всё проинициализированное
}