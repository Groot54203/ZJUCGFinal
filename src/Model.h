#ifndef _Model_H_
#define _Model_H_
#include "GL/GLUT.H"
#include <vector>
#include <iostream>
#include<string>
#define Model_ERROR1 "List ID Initialization failure"
#define Model_ERROR2 "OBJ file open failure"
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
#endif