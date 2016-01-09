#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>

const int BMP_Header_Length = 54;
#pragma pack(2)
struct BMPFileHeader {
	unsigned short	bfType;			// �ļ�����
	unsigned long   bfSize;			// �ļ���С
	unsigned short	bfReserved1;	// ����λ
	unsigned short	bfReserved2;	// ����λ
	unsigned long	bfOffBits;		// ����ƫ��λ��
};

#pragma pack()
// BMP��Ϣͷ
struct BMPInfoHeader {
	unsigned long	biSize;			// �˽ṹ��С
	long			biWidth;		// ͼ����
	long			biHeight;		// ͼ��߶�
	unsigned short	biPlanes;		// ��ɫ������
	unsigned short	biBitCount;		// ÿ�����ض�Ӧ��λ����24��24λͼ��32����alphaͨ����24λͼ
	unsigned long	biCompression;	// ѹ��
	unsigned long	biSizeImage;	// ͼ���С
	long			biXPelsPerMeter;// ����ֱ���
	long			biYPelsPerMeter;// ����ֱ���
	unsigned long	biClrUsed;		// ��ɫʹ����
	unsigned long	biClrImportant;	// ��Ҫ��ɫ��
};

GLuint loadTexture(const char *fileName);  //����ֵΪ0��Ϊ�����˴���
#endif