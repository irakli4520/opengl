#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(10.0f, 10.0f, 10.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	int r = 2;
	double x1, x2, z1, z2;
	for(double i = 0; i <= 359; i++)
	{
		x1 = r * cos(i * M_PI / 180);
		x2 = r * cos((i + 1) * M_PI / 180);
		z1 = r * sin(i * M_PI / 180);
		z2 = r * sin((i + 1) * M_PI / 180);
		// ������ ���������
		glBegin(GL_TRIANGLES);
		glColor3d(1.0f, 0.0f, 0.0f);
		glVertex3d(0, 0, 0);
		glColor3d(0.0f, 0.0f, 1.0f);
		glVertex3d(x1, 0, z1);
		glVertex3d(x2, 0, z2);
		glEnd();
		// ������� ���������
		glBegin(GL_TRIANGLES);
		glColor3d(0.0f, 0.0f, 1.0f);
		glVertex3d(0, 6, 0);
		glColor3d(1.0f, 0.0f, 0.0f);
		glVertex3d(x1, 6, z1);
		glVertex3d(x2, 6, z2);
		glEnd();
		// ������
		glBegin(GL_QUADS);
		glColor3d(0.0f, 0.0f, 1.0f);
		glVertex3d(x2, 6, z2);
		glVertex3d(x1, 6, z1);
		glColor3d(1.0f, 0.0f, 0.0f);
		glVertex3d(x1, 0, z1);
		glVertex3d(x2, 0, z2);
		glEnd();
	}
	glutSwapBuffers();//������������� ����� �� �����
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
	glutInit(&argc, argv);//��������� ������������� ����
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//��������� ������ �����������
	glutInitWindowSize(600,600);//������ ����
	glutInitWindowPosition(200, 200);//��������� ������� �� ������
	glutCreateWindow("Lab2");//��������� ����
	glClearColor(0, 0, 0, 0);//���� ����

	// ��������� ��������
	glMatrixMode(GL_PROJECTION);//����� �������
	glLoadIdentity();//�������� �������

	glutDisplayFunc(display);//������� ������� �� �������� ��� ������� ��� ��������� ����. 
	glutReshapeFunc(changeSize);//���������� �������� �����������
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();//��������� �� ���������������������
}