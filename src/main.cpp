#include "World.h"
#include "BasicElement.h"
#include "texture.h"
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
	new Cube(Point(10, 0, 0));
}
int main(int argc, char *argv[]) {
	World::init(&argc, argv);
	//����������ʹ��glutIdleFunc();��idle������д
	//��Ҫ�����ͼ��̺���������д��������World.cpp���޸�


	
	define();
	Rect rect(Point(10, 2, 0), loadTexture("images//win7.bmp"));
	rect.scale(3, 3, 4);





	glutMainLoop();
	return 0;
}
