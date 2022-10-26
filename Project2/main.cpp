#include <GL/glut.h>
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(6.0f, -15.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// ���
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

	// ��������
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