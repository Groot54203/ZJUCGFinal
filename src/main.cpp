#include "World.h"
#include "BasicElement.h"
#include "texture.h"
using namespace std;

int main(int argc, char *argv[]) {
	World::init(&argc, argv);
	Cube cube(Point(10, 0, 0));
	Rect rect(Point(10, 2, 0), loadTexture("images//win7.bmp"));
	rect.scale(3, 3, 4);
	//����������ʹ��glutIdleFunc();��idle������д
	//��Ҫ�����ͼ��̺���������д��������World.cpp���޸�
	glutMainLoop();
	return 0;
}