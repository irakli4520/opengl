#include <GL/glut.h>
#include <GL/FreeImage.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>
#include <iostream>

// Для вращения камеры
float camX = 0;
float camY = 5;
float camZ = 0;
float viewX = 0;
float viewY = 0;
float viewZ = 0;
float theta = 90;
float phi = 270;
float r = 50;
float camSpeed = 2;
// id текстуры
GLuint side;
GLuint top;
GLuint sky;
GLuint grass;
GLuint wood;

void normalVector(float* normal, float x1, float y1, float z1, float x2, float y2, float z2)
{
	normal[0] = y1 * z2 - z1 * y2;
	normal[1] = x1 * z2 - z1 * x2;
	normal[1] = -normal[1];
	normal[2] = x1 * y2 - y1 * x2;
}

void milk(double r, double height)
{
	// Цилиндр
	float step = 1;
	float normal[3];
	float sideTex = 1;
	float x1, x2, z1, z2, xTex1, yTex1, xTex2, yTex2;
	glColor3d(1.0f, 1.0f, 1.0f);
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
		// Нижнее основание
		glBindTexture(GL_TEXTURE_2D, top);
		normalVector(normal, -x1, 0, -z1, -x2, 0, -z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, 0, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, 0, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, 0, z2);
		glEnd();
		// Верхнее основание
		normalVector(normal, x1, 0, z1, x2, 0, z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, height, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, height, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, height, z2);
		glEnd();
		// Стенки
		glBindTexture(GL_TEXTURE_2D, side);
		normalVector(normal, x1 - x2, 0, z1 - z2, x2 - x1, -6, z2 - z1);
		glNormal3fv(normal);
		glBegin(GL_QUADS);
		glTexCoord2f(sideTex, 1.0f);
		glVertex3d(x1, height, z1);
		glTexCoord2f(sideTex, 0.0f);
		glVertex3d(x1, 0, z1);
		sideTex = sideTex - step / 360;
		glTexCoord2f(sideTex, 0.0f);
		glVertex3d(x2, 0, z2);
		glTexCoord2f(sideTex, 1.0f);
		glVertex3d(x2, height, z2);
		glEnd();
	}
}

void world(float r)
{
	GLfloat sky_emission[] ={1.0, 1.0, 1.0, 1.0};
	GLfloat standart_emission[] ={0.0, 0.0, 0.0, 1.0};
	float step = 10;
	float normal[3];
	float sideTex = 1;
	float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, xTex1, yTex1, xTex2, yTex2;
	// Земля
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
		// Земля
		glBindTexture(GL_TEXTURE_2D, grass);
		normalVector(normal, -x1, 0, -z1, -x2, 0, -z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, 0, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, 0, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, 0, z2);
		glEnd();
	}
	// Небо
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sky_emission);
	glBindTexture(GL_TEXTURE_2D, sky);
	step = 10;
	for(float a = 0; a < 360; a = a + step) {
		for(float b = 0; b < 90; b = b + step) {
			y1 = r * cos(b * M_PI / 180);
			y2 = r * cos((b + step) * M_PI / 180);
			x1 = r * sin(b * M_PI / 180) * cos(a * M_PI / 180);
			z1 = r * sin(b * M_PI / 180) * sin(a * M_PI / 180);
			x2 = r * sin(b * M_PI / 180) * cos((a + step) * M_PI / 180);
			z2 = r * sin(b * M_PI / 180) * sin((a + step) * M_PI / 180);
			x3 = r * sin((b + step) * M_PI / 180) * cos(a * M_PI / 180);
			z3 = r * sin((b + step) * M_PI / 180) * sin(a * M_PI / 180);
			x4 = r * sin((b + step) * M_PI / 180) * cos((a + step) * M_PI / 180);
			z4 = r * sin((b + step) * M_PI / 180) * sin((a + step) * M_PI / 180);
			normalVector(normal, x1 - x2, y1 - y2, z1 - z2, x2 - x1, y2 - y1, z2 - z1);
			glNormal3fv(normal);
			xTex1 = (1 - a) / 360;
			yTex1 = (1 - b) / 90;
			xTex2 = (1 - (a + step)) / 360;
			yTex2 = (1 - (b + step)) / 90;
			glBegin(GL_QUADS);
			glTexCoord2f(xTex2, yTex1);
			glVertex3d(x2, y1, z2);
			glTexCoord2f(xTex1, yTex1);
			glVertex3d(x1, y1, z1);
			glTexCoord2f(xTex1, yTex2);
			glVertex3d(x3, y2, z3);
			glTexCoord2f(xTex2, yTex2);
			glVertex3d(x4, y2, z4);
			glEnd();
		}
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, standart_emission);
}

void stand(double r, double height)
{
	// Цилиндр
	float step = 1;
	float normal[3];
	float sideTex = 1;
	float x1, x2, z1, z2, xTex1, yTex1, xTex2, yTex2;
	glColor3d(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, wood);
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
		// Нижнее основание
		normalVector(normal, -x1, 0, -z1, -x2, 0, -z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, 0, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, 0, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, 0, z2);
		glEnd();
		// Верхнее основание
		normalVector(normal, x1, 0, z1, x2, 0, z2);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3d(0, height, 0);
		glTexCoord2f(xTex1, yTex1);
		glVertex3d(x1, height, z1);
		glTexCoord2f(xTex2, yTex2);
		glVertex3d(x2, height, z2);
		glEnd();
		// Стенки
		normalVector(normal, x1 - x2, 0, z1 - z2, x2 - x1, -6, z2 - z1);
		glNormal3fv(normal);
		glBegin(GL_QUADS);
		glTexCoord2f(sideTex, 1.0f);
		glVertex3d(x1, height, z1);
		glTexCoord2f(sideTex, 0.0f);
		glVertex3d(x1, 0, z1);
		sideTex = sideTex - step / 360;
		glTexCoord2f(sideTex, 0.0f);
		glVertex3d(x2, 0, z2);
		glTexCoord2f(sideTex, 1.0f);
		glVertex3d(x2, height, z2);
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, viewX, viewY, viewZ, 0.0f, 1.0f, 0.0f);

	// источник света
	GLfloat light1_diffuse[] = {1.0, 1.0, 1.0};
	GLfloat light1_position[] = {0.0, 25.0, -50.0, 1.0};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	// Банка на подставке
	glPushMatrix();
	glTranslatef(0, 1, -20);
	glRotatef(60, 0, 1, 0);
	milk(2, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -20);
	glRotatef(0, 0, 1, 0);
	stand(3, 1);
	glPopMatrix();

	// три подставки
	glPushMatrix();
	glTranslatef(20, 0, 3);
	glRotatef(0, 0, 1, 0);
	stand(2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0, -2);
	glRotatef(50, 0, 1, 0);
	stand(3, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, 1, 0);
	glRotatef(90, 0, 1, 0);
	stand(4, 3);
	glPopMatrix();

	// банка и подставки вокруг
	glPushMatrix();
	glTranslatef(-20, 0, 0);
	glRotatef(230, 0, 1, 0);
	milk(2, 4);
	glPopMatrix();

	float x, z;
	float r = 5;
	for(double i = 0; i <= 360; i = i + 60)
	{
		x = r * cos(i * M_PI / 180);
		z = r * sin(i * M_PI / 180);
		glPushMatrix();
		glTranslatef(x - 20, 0, z);
		glRotatef(180, 0, 1, 0);
		stand(0.5, 1);
		glPopMatrix();
	}

	// Под камерой
	stand(5, 0.5);

	world(100);

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
	gluPerspective(60.0f, ratio, 0.1f, 110.0f);
	glMatrixMode(GL_MODELVIEW);
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			if(theta > 0 + camSpeed) {
				theta = theta - camSpeed;
				viewX = r * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
				viewZ = r * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
				viewY = r * cos(theta * M_PI / 180);
			}
			break;
		case GLUT_KEY_DOWN:
			if(theta < 180 - camSpeed) {
				theta = theta + camSpeed;
				viewX = r * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
				viewZ = r * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
				viewY = r * cos(theta * M_PI / 180);
			}
			break;
		case GLUT_KEY_LEFT:
			phi = phi - camSpeed;
			if(phi < 0)
				phi = 360 + phi;
			viewX = r * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
			viewZ = r * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
			viewY = r * cos(theta * M_PI / 180);
			break;
		case GLUT_KEY_RIGHT:
			phi = phi + camSpeed;
			if(phi > 360)
				phi = phi - 360;
			viewX = r * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
			viewZ = r * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
			viewY = r * cos(theta * M_PI / 180);
			break;
	}
}

void timer(int value)
{
	glutPostRedisplay();
    glutTimerFunc(1, timer, 0);
}

int LoadFreeImage(char *filename, GLuint &id)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib;
	BYTE *bits;
	unsigned int widht, height;
	fif = FreeImage_GetFileType(filename);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	if (fif == FIF_UNKNOWN)
		return 1;
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	if (!dib)
		return 1;
	bits = FreeImage_GetBits(dib);
	widht = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	return 0;
}

int main(int argc, char **argv)
{
	// Инициализация положения камеры
	
	// Инициализация положения камеры
	viewX = r * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
	viewZ = r * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
	viewY = r * cos(theta * M_PI / 180);

	glutInit(&argc, argv);//начальная инициализация окна
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//установка режима отображения
	glutInitWindowSize(800,600);//размер окна
	glutInitWindowPosition(250, 100);//начальная позиция на экране
	glutCreateWindow("Lab7");//заголовок окна
	glClearColor(0.0f, 0.0f, 0.0f, 0.f);//цвет фона

	glutDisplayFunc(display);//функция которой мы передаем имя функции для отрисовки окна. 
	glutReshapeFunc(changeSize);//подстройка размеров изображения
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);
	// Текстуры
	glEnable(GL_TEXTURE_2D);

	// рассчет освещения
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	// двухсторонний расчет освещения
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// изменение фонового овуещения
	GLfloat ambient[] = {0.3, 0.3, 0.3, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	// автоматическое приведение нормалей к единичной длине
	glEnable(GL_NORMALIZE);
	// Обработка нажатия клавиш
	glutSpecialFunc(processSpecialKeys);
	// Запуск таймера
	//glutTimerFunc(1, timer, 0);

	// Текстуры
	LoadFreeImage("side.bmp", side);
	LoadFreeImage("top.bmp", top);
	LoadFreeImage("sky.bmp", sky);
	LoadFreeImage("grass.bmp", grass);
	LoadFreeImage("wood.bmp", wood);
	
	// Запускаем всё проинициализированное
	glutMainLoop();
}