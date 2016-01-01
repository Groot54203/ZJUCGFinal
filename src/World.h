#ifndef __World_H__
#define __World_H__

#include <map>
#include <deque>
#include "LightSource.h"
#include "BasicElement.h"
using namespace std;


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
	static double zoomFactor;

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

	/*  �ⲿ�ɴ�����ƺ���  */
	static void (*_display)();

	friend class BasicElement;


	/*  GLUT FUNC  */
	static void idle();  //����static��Ϳ��Դ���glutIdleFunc()����
	static void display();
	static void keyboard(unsigned char key, int x, int y);
	static void special(int key, int x, int y);
	static void motion(int x, int y);
	static void passiveMotion(int x, int y);
	static void entry(int state);
	static void mouseClick(int button, int state, int x, int y);

		/*  ��ѡ��������  */
		static void gl_select(int x, int y);
		static void mousedw(int x, int y, int but);

	//TODO  ��ꡢ��ײ��⡢���մ���Ⱥ�����Ҫ���


	/*  ����  */
	static string scrennshotsDir;
	static void grabScreen();


};



#endif
