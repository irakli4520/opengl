#include <GL/glut.h>
#include <GL/FreeImage.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

// ��� �������� �����
float angle = 0;
float speed = -0.5;

// ��� �������� ������
float camX = 0;
float camY = 0;
float camZ = 0;
float viewX = 0;
float viewY = 0;
float viewZ = 0;
float theta = 45;
float phi = 180;
float r = 12;
float camSpeed = 0.05;
// id ��������
GLuint side;
GLuint top;

void normalVector(float* normal, float x1, float y1, float z1, float x2, float y2, float z2)
{
	normal[0] = y1 * z2 - z1 * y2;
	normal[1] = x1 * z2 - z1 * x2;
	normal[1] = -normal[1];
	normal[2] = x1 * y2 - y1 * x2;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, viewX, viewY, viewZ, 0.0f, 1.0f, 0.0f);

	// �������� �����
	GLfloat light1_diffuse[] = {1.0, 1.0, 1.0};
	GLfloat light1_position[] = {-10.0, 8.0, -2.0, 1.0};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	// �������
	double r = 2;
	double x1, x2, z1, z2;
	float step = 1;
	float normal[3];
	float sideTex = 1;
	float height = 4;
	float xTex1, yTex1, xTex2, yTex2;
	glColor3d(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	for(double i = 0; i <= 360 - step; i = i + step)
	{
		x1 = r * cos(i * M_PI / 180);
		x2 = r * cos((i + step) * M_PI / 180);
		z1 = r * sin(i * M_PI / 180);
		z2 = r * sin((i + step) * M_PI / 180);
		xTex1 = (cos(i * M_PI / 180) + 1) / 2;
		yTex1 = (sin(i * M_PI / 180) + 1) / 2;
		xTex2 = (cos((i + step) * M_PI / 180) + 1) / 2;
		yTex2 = (sin((i + step) * M_PI / 180) + 1) / 2;
		// ������ ���������
		glBindTexture(GL_TEXTURE_2D, top);
		normalVector(normal, -x1, 0, -z1, -x2, 0, -z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, -height / 2, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, -height / 2, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, -height / 2, z2);
		glEnd();
		// ������� ���������
		normalVector(normal, x1, 0, z1, x2, 0, z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, height / 2, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, height / 2, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, height / 2, z2);
		glEnd();
		// ������
		glBindTexture(GL_TEXTURE_2D, side);
		normalVector(normal, x1 - x2, 0, z1 - z2, x2 - x1, -6, z2 - z1);
		glNormal3fv(normal);
		glBegin(GL_QUADS);
		glTexCoord2f(sideTex, 1.0f);
		glVertex3d(x1, height / 2, z1);
		glTexCoord2f(sideTex, 0.0f);
		glVertex3d(x1, -height / 2, z1);
		sideTex = sideTex - step / 360;
		glTexCoord2f(sideTex, 0.0f);
		glVertex3d(x2, -height / 2, z2);
		glTexCoord2f(sideTex, 1.0f);
		glVertex3d(x2, height / 2, z2);
		glEnd();
	}
	glPopMatrix();

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

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			theta = theta - camSpeed;
			camX = r * sin(theta) * cos(phi);
			camZ = r * sin(theta) * sin(phi);
			camY = r * cos(theta);

			break;
		case GLUT_KEY_DOWN:
			theta = theta + camSpeed;
			camX = r * sin(theta) * cos(phi);
			camZ = r * sin(theta) * sin(phi);
			camY = r * cos(theta);
			break;
		case GLUT_KEY_LEFT:
			phi = phi + camSpeed;
			camX = r * sin(theta) * cos(phi);
			camZ = r * sin(theta) * sin(phi);
			camY = r * cos(theta);
			break;
		case GLUT_KEY_RIGHT:
			phi = phi - camSpeed;
			camX = r * sin(theta) * cos(phi);
			camZ = r * sin(theta) * sin(phi);
			camY = r * cos(theta);
			break;
	}
}

void timer(int value)
{
	angle = angle + 1 * speed;
	if(angle > 360)
		angle = angle - 360;

	glutPostRedisplay();
    glutTimerFunc(1, timer, 0);
}

void LoadFreeImage(char *filename, GLuint &id)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib;
	BYTE *bits;
	unsigned int widht, height;
	fif = FreeImage_GetFileType(filename);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	if (fif == FIF_UNKNOWN)
		return;
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	if (!dib)
		return;
	bits = FreeImage_GetBits(dib);
	widht = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int main(int argc, char **argv)
{
	// ������������� ��������� ������
	camX = r * sin(theta) * cos(phi);
	camZ = r * sin(theta) * sin(phi);
	camY = r * cos(theta);

	glutInit(&argc, argv);//��������� ������������� ����
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//��������� ������ �����������
	glutInitWindowSize(600,600);//������ ����
	glutInitWindowPosition(200, 200);//��������� ������� �� ������
	glutCreateWindow("Lab6");//��������� ����
	glClearColor(0.0f, 0.0f, 0.0f, 0.f);//���� ����

	glutDisplayFunc(display);//������� ������� �� �������� ��� ������� ��� ��������� ����. 
	glutReshapeFunc(changeSize);//���������� �������� �����������
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);
	// ��������
	glEnable(GL_TEXTURE_2D);

	// ������� ���������
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	// ������������� ������ ���������
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// ��������� �������� ���������
	GLfloat ambient[] = {0.08, 0.08, 0.08, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	// �������������� ���������� �������� � ��������� �����
	glEnable(GL_NORMALIZE);
	// ��������� ������� ������
	glutSpecialFunc(processSpecialKeys);
	// ������ �������
	glutTimerFunc(1, timer, 0);

	// ��������
	 LoadFreeImage("side.bmp", side);
	 LoadFreeImage("top.bmp", top);
	
	// ��������� �� ���������������������
	glutMainLoop();
}