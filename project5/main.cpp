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
	// направление
	float distance = sqrt(planet_coord[0] * planet_coord[0] + planet_coord[1] * planet_coord[1] + planet_coord[2] * planet_coord[2]);
	acceleration[0] = -planet_coord[0] / distance;
	acceleration[1] = -planet_coord[1] / distance;
	acceleration[2] = -planet_coord[2] / distance;

	// ускорение
	acceleration[0] = acceleration[0] / (distance * distance);
	acceleration[1] = acceleration[1] / (distance * distance);
	acceleration[2] = acceleration[2] / (distance * distance);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(50.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// свойства материала
	GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat sun_emission[] ={1.0000, 0.7765, 0.0941, 1.0};
	GLfloat planets_emission[] ={0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

	// источник света
	GLfloat light1_diffuse[] = {1.0, 1.0, 1.0};
	GLfloat light1_position[] = {0.0, 0.0, 0.0, 1.0};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	// солнце
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emission);
	glColor3f(1.0000, 0.7765, 0.0941);
	glutSolidSphere(3, 100, 100);

	// планеты
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, planets_emission);

	glColor3f(0.7, 0.5, 0.5);
	customSphere(1.2, third_coord[0], third_coord[1], third_coord[2]);

	glColor3f(0.7, 0.02, 0.5);
	customSphere(1.0, second_coord[0], second_coord[1], second_coord[2]);

	glColor3f(0.3, 0.8, 0.2);
	customSphere(0.7, first_coord[0], first_coord[1], first_coord[2]);
	
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

void timer(int value)
{
	float acceleration[] = {0, 0, 0};

	// вычисление вектора ускорения к звезде
	calculationOfAccelerationVector(first_coord, acceleration);
	// сложение вектора скорости планеты и вектора ускорения к звезде
	additionOfVectors(first_vector, acceleration);
	// приложение вектора к координатам планеты
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
	glutInit(&argc, argv);//начальная инициализация окна
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//установка режима отображения
	glutInitWindowSize(600,600);//размер окна
	glutInitWindowPosition(200, 200);//начальная позиция на экране
	glutCreateWindow("Lab5 physics");//заголовок окна
	glClearColor(0.0f, 0.0f, 0.0f, 0.f);//цвет фона

	// настройка проекции
	glMatrixMode(GL_PROJECTION);//режим матрицы
	glLoadIdentity();//отчищает матрицу

	glutDisplayFunc(display);//функция которой мы передаем имя функции для отрисовки окна. 
	glutReshapeFunc(changeSize);//подстройка размеров изображения
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);

	// рассчет освещения
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	// двухсторонний расчет освещения
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// изменение фонового овуещения
	GLfloat ambient[] = {0.15, 0.15, 0.15, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	// автоматическое приведение нормалей к единичной длине
	glEnable(GL_NORMALIZE);

	glutTimerFunc(1, timer, 0);  //запуск таймера
	glutMainLoop();//запускаем всё проинициализированное
}