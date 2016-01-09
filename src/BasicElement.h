#ifndef __BasicElement_H__
#define __BasicElement_H__
#include "Model.h"
#include "utility.h"

/*  ������ά����  */
class BasicElement {
private:

public:
	unsigned int id;
	Point centroid;  //����
	Quat rotateQuat;  //GLMat rotateMat;
	Vec scaleValue;
	int classType;  //1Ϊ�ӵ���2Ϊ���Լ�Ѫ�����壬һ��Ϊ0
	BasicElement();
	virtual ~BasicElement();
	unsigned int getId();
	virtual bool shouldBeRemoved();


	/*  draw�����������������壬��������������Ӧ��ƽ�ƺ���ת����  */
	virtual void draw();

	/*  drawNaive��������glutSolidTeapot��������������ԭ��Ϊ���Ľ��л���  */
	virtual void drawNaive();


	/*  �˺�����ʹ������glRotate������ʹ�ã�ֻ���������Զ�ε���ʹ�á�
		(����rotate(90, 1, 1, 1)��rotate(100, 1, 0, 1)��������ת�������Ե���)
		���⣬�˺�����angle����Ϊ�Ƕ���                                        */
	void rotate(double angle, double x, double y, double z);  //�������ò�ƻ����������������⣬���Ǿ����������Ǹ�������

	/*  �˺���ÿ���Գ�ʼ״̬Ϊ��׼��ʹ��������ĳ��������תangle�Ƕ�  */
	void rotateTo(double angle, double x, double y, double z);

	/*  ���λ�ƺ���  */
	void move(double dx, double dy, double dz); 

	/*  ������������ƶ���ĳ��λ��  */
	void moveTo(Point p);

	/*  ���ź���  */
	void scale(double tx, double ty, double tz);
	void scale(Vec t);
	void scale(double t);
};

class Cube : public BasicElement {
private:
	GLuint tex=0;
public:
	Cube(Point p);
	Cube(Point p, GLuint t);
	void drawNaive();
};

class Sphere : public BasicElement {
public:
	double radius;
	int slices, stacks;
	Sphere(Point p, double radius=0.5, int slices=50, int stacks=50);
	void drawNaive();
};

class Cone : public BasicElement {
public:
	double radius, height;
	int slices, stacks;
	Cone(Point p, double radius=0.5, double height=1.0, int slices=50, int stacks=50);
	void drawNaive();
};

class Circle : public BasicElement {
public:
	double radius;
	int slices;
	Circle(Point p, double radius=0.5, int slices=100);
	void circle();
	virtual void drawNaive();
};
class Cylinder : public Circle {
public:
	double height;
	int stacks;
	Cylinder(Point p, double radius=0.5, double height=0.5, int slices=100, int stacks=100);
	void drawNaive();
};

//TODO  ���������Ͷ�����̨

class Rect : public BasicElement {
public:
	Model M;
	unsigned int tex;
	Rect(Point p, unsigned int texture=0);
	Rect(unsigned int texture=0);
	void drawNaive();
};

class AviBoard : public BasicElement {
private:
	int nowtime;//��ʱ
	int timebase;//��ʱ��nowtime-timebase�Ƿ����һ֡��ʱ��
	int pixel_w;//��
	int pixel_h;//��
	int framenum;//��֡��
	int count;
	double height;
	double weight;
	unsigned char *buffer;//avi
	unsigned char *tmpbuff;
public:
	AviBoard(Point p,double height,double weight,string videoname);
	~AviBoard(void);
	void drawNaive();
};


/*Life Bar*/
class LifeBar {
private:
	double barlen = 4, barw = 0.5;
	double max_life;
public:
	LifeBar();
	LifeBar(double _max_life);
	LifeBar(double _max_life, double len, double w);
	~LifeBar();
	void DrawBar(Point pos, double life);
};
class objectmodel : public BasicElement {
protected:
	Model* mymo;
public:
	//objectmodel(objectmodel&other)
	//{
	//	mymo = new Model(*other.mymo);
	//}
	objectmodel(Point p, string name);
	virtual ~objectmodel(void);
	//virtual void draw();
	virtual void drawNaive();
	void objectmodel::addToPhysicsWorld(double coliisionscale = 30, double weight = 100000);
};

class Monster : public objectmodel {
protected:
	int blood;
	int fullblood;
	LifeBar lifeBar;
public:
	Monster(Point p, string name);
	void subblood();
	bool shouldBeRemoved();
	void draw();
	void drawNaive();
};

class CameraModel : public BasicElement {
public:
	CameraModel(Point p);
	CameraModel();
	void drawNaive();
};


class Bullet : public BasicElement {
public:
	double radius;
	int slices, stacks;
	Bullet(Point p, double radius=0.5, int slices=50, int stacks=50);
	void drawNaive();
	bool shouldBeRemoved();
};

#endif
