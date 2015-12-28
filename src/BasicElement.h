#ifndef __BasicElement_H__
#define __BasicElement_H__

#include "utility.h"

/*  ������ά����  */
class BasicElement {
private:
	unsigned int id;

public:
	Point centroid;  //����
	Vec scaleValue;
	BasicElement();
	~BasicElement();
	unsigned int getId();


	/*  draw�����������������壬��������������Ӧ��ƽ�ƺ���ת����  */
	void draw();

	/*  drawNaive��������glutSolidTeapot��������������ԭ��Ϊ���Ľ��л���  */
	virtual void drawNaive();


	/*  �˺�����ʹ������glRotate������ʹ�ã�ֻ���������Զ�ε���ʹ�á�
		(����rotate(90, 1, 1, 1)��rotate(100, 1, 0, 1)��������ת�������Ե���)
		���⣬�˺�����angle����Ϊ�Ƕ���                                        */
	void rotate(double angle, double x, double y, double z);

	/*  ���λ�ƺ���  */
	void move(double dx, double dy, double dz); 

	/*  ������������ƶ���ĳ��λ��  */
	void moveTo(Point p);

	/*  ���ź���  */
	void scale(double tx, double ty, double tz);
	void scale(Vec t);
};

class Cube : public BasicElement {
public:
	Cube(Point p);
	void drawNaive();
};

class Rect : public BasicElement {
public:
	unsigned int tex;
	Rect(Point p, unsigned int texture=0);
	Rect(unsigned int texture=0);
	void drawNaive();
};


#endif
