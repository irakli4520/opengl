#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

float modif = 0;
bool direct = true;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5.0f, 10.0f, 10.0f, 3.0f, 0.0f, 1.5f, 0.0f, 1.0f, 0.0f);

	float x1, x2, y1, y2, z1, z2;
	glBegin(GL_QUADS);
	float basicRColour = 1.000;
	float basicGColour = 0.722;
	float basicBColour = 0.255;
	for(x1 = 0; x1 <= 6; x1 = x1 + 0.1)
	{
		x2 = x1 + 0.1;
		y1 = sin(x1 * 2 + modif) / 4;
		y2 = sin(x2 * 2 + modif) / 4;
		glBegin(GL_QUADS);
		//�������� ����
		glColor3f(basicRColour - (0 - y1) / 3, basicGColour - (0 - y1) / 3, basicBColour - (0 - y1) / 3);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x1, y1, 3.0f);
		glColor3f(basicRColour - (0 - y2) / 3, basicGColour - (0 - y2) / 3, basicBColour - (0 - y2) / 3);
		glVertex3f(x2, y2, 3.0f);
		glVertex3f(x2, y2, 0.0f);
		//"����"
		glColor3f(0.917f, 0.917f, 0.818f);
		glVertex3f(x1, y1 - 0.5, 0.0f);
		glVertex3f(x1, y1 - 0.5, 3.0f);
		glVertex3f(x2, y2 - 0.5, 3.0f);
		glVertex3f(x2, y2 - 0.5, 0.0f);
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

void timer(int value)
{
	if(modif == 1)
		direct = false;
	if(modif == -1)
		direct = true;
	if(direct)
		modif = modif + 0.1;
	if(!direct)
		modif = modif - 0.1;
	glutPostRedisplay();
    glutTimerFunc(33, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);//��������� ������������� ����
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//��������� ������ �����������
	glutInitWindowSize(600,600);//������ ����
	glutInitWindowPosition(200, 200);//��������� ������� �� ������
	glutCreateWindow("Lab4");//��������� ����
	glClearColor(0.961f, 0.961f, 0.863f, 0.f);//���� ����

	// ��������� ��������
	glMatrixMode(GL_PROJECTION);//����� �������
	glLoadIdentity();//�������� �������

	glutDisplayFunc(display);//������� ������� �� �������� ��� ������� ��� ��������� ����. 
	glutReshapeFunc(changeSize);//���������� �������� �����������
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(1, timer, 0);  //������ �������
	glutMainLoop();//��������� �� ���������������������
}