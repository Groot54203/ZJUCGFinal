# Computer Graphics
##### 2015 ZJU Computer Graphics Final Project
<br/>
# Ŀǰ���ȣ�
1. ���Է���ػ��������ˡ�(����Ļ��Ʋ����"APIʹ�÷���"�͡�main.cpp��)
2. �ü��̿��Բ������ǰ�����������ƶ��ˡ�(�ֱ��Ӧ���̵�wsadcz) <br/>
   ���ڿ��������ٿ��ˡ�
3. �ü��̿�����ת����ĽǶ��ˣ����ҿ��Գ�������ĳ���ǰ����(�����ϵ�jlik�ֱ��Ӧ�������ҡ����ϡ�������ת)
4. ��������ѡ������ʵ�֣��������������û����ȥ������ֻ�ܿ�cmd�����

<br/>

## �������綨�壺
����y��������Ϊ��ֱ���ϵķ���<br/>
��ʼʱ����x�����򣬴�ʱ�Ҳ�Ϊz��������
<br/>

## APIʹ�÷�����
#### ���������������
1. ��BasicElement.h��BasicElement.cpp����̳���BasicElement���࣬������drawNaive������
2. ��main�����У�
	1. ����initWorld������������г�ʼ��
	2. �����Լ�������(������BasicElement������)�Ķ��󣬲��������ꡢ����(��ת��)��
	3. Ȼ���ٵ���glutMainLoop�Ϳ��Կ�ʼ��ʾ�����������
(ע�����տ�����Ҫ�Լ����塣���⣬���Ҫ�õ����ʻ��������꣬������Ҫ���ж���һ���µ�BasicElement��)


## �����ඨ��
#### ���ڴ����͹�����ά������ࣺWorld
```
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

	static Point eye, center;
	static const Vec up;  //up�������ܱ��޸�
	static double moveSpeed;

	static unsigned int chosenID;


	/*  ��ʼ������  */
	static void init(int *argc, char *argv[], int windowHeight=800, int windowWidth=800);

	/*  �ƶ����  */
	static void move(double dx, double dy, double dz);

	/*  ��ת����Ƕ�(�Ƕ���)  */
	static void rotate(double angle, double x, double y, double z);

	/*  һ���Ի�����������  */
	static void drawAll();

	friend class BasicElement;
};
```

#### ���ڱ�ʾ������ά����Ľṹ��BasicElement
```
class BasicElement {
private:
	unsigned int id;

public:
	Point centroid;  //����
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
};
```

#### ���ڱ�ʾ��obj�ȸ�ʽ�������ά����Ľṹ��Model
```
class Model
{
protected:
      struct v{
            double x;
            double y;
            double z;
      };
      struct f{
            unsigned int v1,v2,v3;
      };
	  struct vt{
		double x,y;
	  };
	  GLuint DrawListID;
	  std::vector<v> vertices;
	  std::vector<v> vert_nor;
      std::vector<f> faces,face_tex;
	  std::vector<vt> texture_ord;
	  std::vector<f> normals;
public:
	//�ڻ���obj֮ǰ�ǵö�ȡһ��obj�ļ�����opengl��ʼ��֮���ٶ�ȡ
	  virtual void Readobj(const char * filename);
	  //���ƺ���
      virtual void draw();
	  Model();
	  //��������
	  Model(const Model &);
      ~Model(void);
};
```





## ����Ҫ���Ƶĵط���
1. ���д��뻹δ�����������ԣ�������bug������Ⱥ��˵һ�¡�
2. ��Դ������Ҫ���ⶨ��һ���࣬������ʹ��BasicElement��



## ���Ͷ�ʫ�����ۺ��иĶ��ĵط���
1.	id�����ʹ�long long��Ϊ��unsigned int����ΪglLoadName��������ֻ�ܽ���Unsigned int���͵Ĳ�����
2.	drawBody�����ĳ���drawNaive
