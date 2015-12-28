#ifndef __World_H__
#define __World_H__

#include <map>
#include <deque>
#include "GL/glut.h"
#include "BasicElement.h"
using namespace std;


namespace GLfunc {
	void idle();
	void display();
	void keyboard(unsigned char key, int x, int y);
	void motion(int x, int y);
	void passiveMotion(int x, int y);
	void entry(int state);
	void mouseClick(int button, int state, int x, int y);

	//TODO  ��ꡢ��ѡ����ײ��⡢���մ���Ⱥ�����Ҫ���

};


class World {
private:
	static unsigned int nextId;

	/*  ��map�ṹ���ڱ��������е���������  */
	static map<unsigned int, BasicElement *> objects;

	/*  ��˫�˶�������ά����ɾ������ά����id  */
	static deque<unsigned int> trash;

	static unsigned int getNextId();
	static unsigned int getNextId(BasicElement *be);
	static int erase(unsigned int id);

public:
	static int windowHandle;
	static int windowHeight, windowWidth;
	static int windowPos[2];
	static int cursorPos[2];
	static int focusState;

	static Point eye, center;
	static const Vec up;  //up�������ܱ��޸�
	static double elevation[2];
	static double moveSpeed;
	static double rotateSpeed;

	static unsigned int chosenID;


	/*  ��ʼ������  */
	static void init(int *argc, char *argv[], int windowHeight=800, int windowWidth=800, int xPos=100, int yPos=100);
	static void setCursorToCenter();


	static void World::reCenter();

	/*  �ƶ����  */
	static void move(double dx, double dy, double dz);
	static void move(const Vec &ds);
	static void move(int d, double step);

	/*  ��ת����Ƕ�(�Ƕ���)  */
	static void rotate(double angle, double x, double y, double z);

	/*  ��ת���(d=01�ֱ��ʾ��ˮƽ������ֱ����ת��d��������ֵ�����£�stepΪ��������ת������ת)
		���������[-75��,75��]֮��                                                            */
	static void rotate(int d, double step);

	/*  һ���Ի�����������  */
	static void drawAll();

	friend class BasicElement;
};



#endif
