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
	new Cube(Point(10, 0, 0));  //������
	new Sphere(Point(10, -2, -4));  //��
	new Cone(Point(10, -2, -2));  //Բ׶
	new Circle(Point(10, -2, 2));  //Բ
	Cylinder *cc = new Cylinder(Point(10, -2, 0));  //Բ��
	cc->rotateTo(45, 0, 0, 1);
}
int main(int argc, char *argv[]) {
	World::init(&argc, argv);
	//����������ʹ��glutIdleFunc();��idle������д
	//��Ҫ�����ͼ��̺���������д��������World.cpp���޸�
	

	
	define();
	Rect rect(Point(10, 2, 0), loadTexture("images//win7.bmp"));
	rect.scale(3, 3, 4);



	{  //LIGHTING
		GLfloat lightPos0[] = {5,5,5,1};
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, Color(1, 1, 1));//COLOR::white);
		glEnable(GL_LIGHT0);  //light0ֻ������ʾ��
	}




	glutMainLoop();
	return 0;
}
