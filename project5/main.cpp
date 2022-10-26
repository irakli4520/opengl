#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

float gravity = 10;
float first_coord[] = {15, 0, 7};
float first_vector[] = {0, 0.2, 0.1};

float second_coord[] = {0, 0, 20};
float second_vector[] = {0.2, 0, 0};

float third_coord[] = {-15, 0, 15};
float third_vector[] = {0.18, 0, 0};

void customSphere(float radius, float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(radius, 100, 100);
	glPopMatrix();
}

void additionOfVectors(float* planet_vector, float* acceleration)
{
	planet_vector[0] = planet_vector[0] + acceleration[0];
	planet_vector[1] = planet_vector[1] + acceleration[1];
	planet_vector[2] = planet_vector[2] + acceleration[2];
}

void calculationOfAccelerationVector(float* planet_coord, float* acceleration)
{
	// �����������
	float distance = sqrt(planet_coord[0] * planet_coord[0] + planet_coord[1] * planet_coord[1] + planet_coord[2] * planet_coord[2]);
	acceleration[0] = -planet_coord[0] / distance;
	acceleration[1] = -planet_coord[1] / distance;
	acceleration[2] = -planet_coord[2] / distance;

	// ���������
	acceleration[0] = acceleration[0] / (distance * distance);
	acceleration[1] = acceleration[1] / (distance * distance);
	acceleration[2] = acceleration[2] / (distance * distance);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(50.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// �������� ���������
	GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat sun_emission[] ={1.0000, 0.7765, 0.0941, 1.0};
	GLfloat planets_emission[] ={0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

	// �������� �����
	GLfloat light1_diffuse[] = {1.0, 1.0, 1.0};
	GLfloat light1_position[] = {0.0, 0.0, 0.0, 1.0};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	// ������
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emission);
	glColor3f(1.0000, 0.7765, 0.0941);
	glutSolidSphere(3, 100, 100);

	// �������
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, planets_emission);

	glColor3f(0.7, 0.5, 0.5);
	customSphere(1.2, third_coord[0], third_coord[1], third_coord[2]);

	glColor3f(0.7, 0.02, 0.5);
	customSphere(1.0, second_coord[0], second_coord[1], second_coord[2]);

	glColor3f(0.3, 0.8, 0.2);
	customSphere(0.7, first_coord[0], first_coord[1], first_coord[2]);
	
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
	float acceleration[] = {0, 0, 0};

	// ���������� ������� ��������� � ������
	calculationOfAccelerationVector(first_coord, acceleration);
	// �������� ������� �������� ������� � ������� ��������� � ������
	additionOfVectors(first_vector, acceleration);
	// ���������� ������� � ����������� �������
	additionOfVectors(first_coord, first_vector);

	calculationOfAccelerationVector(second_coord, acceleration);
	additionOfVectors(second_vector, acceleration);
	additionOfVectors(second_coord, second_vector);

	calculationOfAccelerationVector(third_coord, acceleration);
	additionOfVectors(third_vector, acceleration);
	additionOfVectors(third_coord, third_vector);

	glutPostRedisplay();
    glutTimerFunc(33, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);//��������� ������������� ����
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//��������� ������ �����������
	glutInitWindowSize(600,600);//������ ����
	glutInitWindowPosition(200, 200);//��������� ������� �� ������
	glutCreateWindow("Lab5 physics");//��������� ����
	glClearColor(0.0f, 0.0f, 0.0f, 0.f);//���� ����

	// ��������� ��������
	glMatrixMode(GL_PROJECTION);//����� �������
	glLoadIdentity();//�������� �������

	glutDisplayFunc(display);//������� ������� �� �������� ��� ������� ��� ��������� ����. 
	glutReshapeFunc(changeSize);//���������� �������� �����������
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);

	// ������� ���������
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	// ������������� ������ ���������
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// ��������� �������� ���������
	GLfloat ambient[] = {0.15, 0.15, 0.15, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	// �������������� ���������� �������� � ��������� �����
	glEnable(GL_NORMALIZE);

	glutTimerFunc(1, timer, 0);  //������ �������
	glutMainLoop();//��������� �� ���������������������
}