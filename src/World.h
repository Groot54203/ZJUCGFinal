#ifndef __World_H__
#define __World_H__
#define GLUT_DISABLE_ATEXIT_HACK
#include <map>
#include <deque>
#include "LightSource.h"
#include "BasicElement.h"
#include "Physics.h"
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

	static CameraModel *cameraModel;  static int changing;
	static btRigidBody *cameraModelRigidBody;
	static Point eye, center;
	static const Vec up;  //up�������ܱ��޸�
	static double elevation[2];
	static double moveSpeed;
	static double rotateSpeed;
	static double zoomFactor, zoomSpeed;

	static unsigned int chosenID;

	/*  ��Ϸģʽ��0���ϵ�ģʽ��1����Ϸģʽ  */
	static int gameMode;
	static int gameModeTotalNum;
	static const int GOD_MODE = 0;
	static const int GAME_MODE = 1;


	/*  ��ʼ������  */
	static void init(int *argc, char *argv[], int windowHeight=800, int windowWidth=800, int xPos=100, int yPos=100);
	static void setCursorToCenter();

	static void reCenter();
	static void setCamera(Point eye, Point center);


	/*  �ƶ����  */
	static void move(double dx, double dy, double dz);
	static void move(const Vec &ds);
	static void move(int d, double step);
	static void _move(double dx, double dy);

	/*  ��ת����Ƕ�(�Ƕ���)  */
	static void rotate(double angle, double x, double y, double z);

	/*  ��ת���(d=01�ֱ��ʾ��ˮƽ������ֱ����ת��d��������ֵ�����£�stepΪ��������ת������ת)
		���������[-45��,45��]֮��                                                            */
	static void rotate(int d, double step);

	/*  ��bullet�Ǳߵ����λ�ø���  */
	static void syncWithCameraModel();

	/*  zoom  */
	static void zoom(double d);


	/*  һ���Ի�����������  */
	static void drawAll();

	/*  �ⲿ�ɴ�����ƺ���  */
	static void (*_display)();
	static void(*_free)();

	/*  �ж��ӵ��Ƿ��ɾ��  */
	static double worldBound[3][2];
	static bool isInside(Point p);

	friend class BasicElement;


	/*  GLU FUNC  */
	static void perspective();
	static void lookAt();


	/*  GLUT FUNC  */
	static int mouseState[3];
	static int keyboardPressing[256];

	static void idle();  //����static��Ϳ��Դ���glutIdleFunc()����
	static void display();
	static void keyboard(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	static void special(int key, int x, int y);
	static void motion(int x, int y);
	static void passiveMotion(int x, int y);
	static void entry(int state);
	static void mouseClick(int button, int state, int x, int y);

		/*  ��ѡ��������  */
		static void gl_select(int x, int y);
		static void mousedw(int x, int y, int but);

		/*  ���̸�������  */
		static void keyboardResponse();

	//TODO  ��ײ��⡢���մ���Ⱥ�����Ҫ���


	/*  ����  */
	static string scrennshotsDir;
	static void grabScreen();


	/*  ��Ѫ����(ûʵ��)  */
	static void subtractBlood();

	static bool couldMoveTo(Point p);

	static bool jumping;
	static double jumpHeight, jumpA, jumpV, jumpDt;
	static double getCameraHeight();
	static void jump();
	static void solveJump();
};



#endif
