#ifndef __BasicElement_H__
#define __BasicElement_H__
#include "Model.h"
#include "utility.h"

/*  ������ά����  */
class BasicElement {
private:
	unsigned int id;

public:
	Point centroid;  //����
	Quat rotateQuat;  //GLMat rotateMat;
	Vec scaleValue;
	int classType;  //1Ϊ�ӵ���һ��Ϊ0
	BasicElement();
	virtual ~BasicElement();
	unsigned int getId();


	/*  draw�����������������壬��������������Ӧ��ƽ�ƺ���ת����  */
	void draw();

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
class objectmodel : public BasicElement {
private:
	int blood;
	int fullblood;
	Model* mymo;
public:
	objectmodel(objectmodel&other)
	{
		mymo = new Model(*other.mymo);
	}
	objectmodel(Point p, string name );
	~objectmodel(void);
	void drawNaive();
	void subblood();
	bool shoulddead();
	void objectmodel::addToPhysicsWorld(double coliisionscale = 30, double weight = 100000);
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
};

/*Life Bar*/
class LifeBar{
private:
	double barlen = 4, barw = 0.5;
	double max_life;
public:
	LifeBar(double _max_life) :max_life(_max_life) {}
	LifeBar(double _max_life, double len, double w) :barlen(len), barw(w), max_life(_max_life){}
	~LifeBar(){}
	void DrawBar(Point pos, double life)
	{
		glEnable(GL_COLOR_MATERIAL);
		glPushMatrix();
		glTranslatef(pos.getX(), pos.getY(), pos.getZ());
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(-barlen/2, 0, -barw/2);
		glVertex3f(-barlen / 2, 0, barw / 2);
		glVertex3f(barlen / 2, 0, barw / 2);
		glVertex3f(barlen / 2, 0, -barw / 2);
		glVertex3f(-barlen / 2, 0, -barw / 2);
		glEnd();
		if (life < max_life / 3) glColor3f(1, 0, 0);
		else glColor3f(0, 1, 0);
		glBegin(GL_QUADS);
		glVertex3f(-barlen / 2, 0, -barw / 2);
		glVertex3f(-barlen / 2, 0, barw/2);
		glVertex3f(-barlen / 2 + barlen * (life / max_life), 0, barw / 2);
		glVertex3f(-barlen / 2 + barlen*(life / max_life), 0, -barw / 2);		
		glEnd();
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
		float am[4] = { 0.3, 0.3, 0.3, 1 };
		float nor[4] = { 0.5, 0.5, 0.5, 1 };
		float zero[4] = { 0.3, 0.3, 0.3, 1 };

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, am);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zero);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, nor);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 70.0);
	}
};
#endif
