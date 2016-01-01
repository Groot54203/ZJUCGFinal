#include "World.h"
#include "BasicElement.h"
#include "texture.h"
#include "test.h"
using namespace std;


/*
	���ֶ�������ķ�����
	1. ��World::init()��glutMainLoop()֮�䶨�塣
	   (���԰Ѷ���д��World::int()֮ǰ���������������Ҫ�õ�OpenGL�����Ķ���������Ҫд��World::int()֮��)
	2. ��һ��������Ȼ����new�����塣��Ȼ������������λ��ҲҪ��World::init()��glutMainLoop()֮�䡣
	   (��new������ָ����Զ�������в���)


	ע���ں������������new���壬�Ͳ�����ʾ��������Ϊ��������ʱ������Ǹ����������������Ȼ���Ǹ������û��...
*/


void define() {
	//Cube *c = new Cube(Point(2, 2, 0));
	//c->rotateTo(45, 1, 0, 0);  //������
	//new Sphere(Point(2, 1, 2));  //��
	//new Cone(Point(2, 2, -3));  //Բ׶
	//new Circle(Point(-2, 2, 2));  //Բ
	//Cylinder *cc = new Cylinder(Point(2, -2, 4));  //Բ��
	//cc->rotateTo(45, 0, 0, 1);
}
void draw_world()
{
	//glStaff::xyz_frame(2,2,2,false);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glTranslatef(-10, -10, 0);
	LightManager::xoy_foor(20, 3, 100);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, 0, 0);
	glutSolidCube(2);

	glTranslatef(2, 0, 2);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1, 2, 50, 50);
	glRotatef(90, 1, 0, 0);

	glTranslatef(0, 0, -4);
	glutSolidSphere(1, 50, 50);

	glTranslatef(-4, 1, 0);
	glRotatef(45, 1, 0, 0);
	glutSolidTorus(0.5f, 1, 50, 50);
	glRotatef(-45, 1, 0, 0);
	glPopMatrix();
}
int main(int argc, char *argv[]) {
	World::init(&argc, argv);
	World::setCamera(Point(-10, 10, 10), Point(0, 0, 0));
	//����������ʹ��glutIdleFunc();��idle������д
	//��Ҫ�����ͼ��̺���������д��������World.cpp���޸�
	

	
	define();
	//Rect rect(Point(0, -3, 0));// , loadTexture("images//win7.bmp"));
	//rect.rotateTo(90, 0, 0, 1);
	//rect.scale(3, 3, 4);

	//
	//Rect rect2(Point(5, 1, 0));// , loadTexture("images//win7.bmp"));
	//rect2.scale(3, 3, 4);
	////rect2.rotateTo(90, 1, 0, 0);
	//rect2.rotate(90, 0, 1, 0);

	World::_display = draw_world;
	{  //LIGHTING
		LightSource ls(Point(5, 6, -2, 1));
		LightManager::addLight(ls);
		LightSource ls2(Point(-2, 6, 5, 1));
		LightManager::addLight(ls2);
		LightSource ls3(Point(-3, 6, -3, 1));
		LightManager::addLight(ls3);
		//LightManager::lights.push_back(ls);
		//float lightPos0[] = {1, 0, 0, 1};
		//glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, Color(1, 0, 0, 0.5));//COLOR::white);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Color(1, 0, 0, 0.5));//COLOR::white);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Color(1, 0, 0, 0.5));//COLOR::white);

		glLightfv(GL_LIGHT1, GL_AMBIENT, Color(0, 0, 0, 0.5));//COLOR::white);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Color(0, 0, 1, 0.5));//COLOR::white);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Color(0, 0, 1, 0.5));//COLOR::white);

		glLightfv(GL_LIGHT2, GL_AMBIENT, Color(0, 0, 0, 0.5));//COLOR::white);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Color(0, 1, 0, 0.5));//COLOR::white);
		glLightfv(GL_LIGHT2, GL_SPECULAR, Color(0, 1, 0, 0.5));//COLOR::white);

		/*GLfloat dir[] = { 0, 0,-1};
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);*/
		glEnable(GL_LIGHT0);  //light0ֻ������ʾ��
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}

	glutMainLoop();
	return 0;
}
