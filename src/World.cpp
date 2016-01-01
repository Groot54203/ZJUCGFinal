#include <cmath>
#include <Windows.h>
#include <io.h>
#include "World.h"
#include "utility.h"
#include "texture.h"


unsigned int World::nextId = 0;
map<unsigned int, BasicElement *> World::objects = map<unsigned int, BasicElement *>();
deque<unsigned int> World::trash = deque<unsigned int>();

int World::windowHandle;
int World::windowHeight, World::windowWidth;
int World::windowPos[2];
int World::cursorPos[2];
int World::focusState;

Point World::eye = Point(0, 0, 0);
Point World::center = Point(1, 0, 0);
const Vec World::up = Vec(0, 1, 0);
double World::elevation[2] = { 0.0, 0.0 };
double World::moveSpeed = 0.4;
double World::rotateSpeed = 0.1;
double World::zoomFactor = 1, World::zoomSpeed = 0.005;

unsigned int World::chosenID = -1;
int World::gameMode = 0;
int World::gameModeNum = 2;

void (*World::_display)() = NULL;

int World::mouseState[3] = {GLUT_UP, GLUT_UP, GLUT_UP};




unsigned int World::getNextId() {
	if (trash.empty()) {
		return ++nextId;
	}
	else {
		int id = trash.front();
		trash.pop_front();
		return id;
	}
}
unsigned int World::getNextId(BasicElement *be) {
	int id = getNextId();
	objects[id] = be;
	return id;
}
int World::erase(unsigned int id) {
	if (objects.empty()) return -1;
	objects.erase(id);
	trash.push_back(id);
	return 0;
}
void World::init(int *argc, char *argv[], int windowHeight, int windowWidth, int xPos, int yPos) {
	{  //GLUT INIT
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
		glutInitWindowPosition(World::windowPos[0] = xPos, World::windowPos[1] = yPos);
		glutInitWindowSize(World::windowWidth = windowWidth, World::windowHeight = windowHeight);
		windowHandle = glutCreateWindow("Simple GLUT App");
		glutDisplayFunc(display);
		//glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(special);
		glutMotionFunc(motion);
		glutPassiveMotionFunc(passiveMotion);
		glutMouseFunc(mouseClick);
		glutEntryFunc(entry);
		glutIdleFunc(idle);

		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
	{  //GLEW INIT
		glewExperimental = TRUE;
		if (GLenum err = glewInit())
			fprintf(stderr, "Error is%s", glewGetErrorString(err));
	}
	{  //OPENGL INIT
		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
	}
	{  //WORLD INIT
		setCursorToCenter();
		POINT pos; GetCursorPos(&pos);
		cursorPos[0] = pos.x;  cursorPos[1] = pos.y;
	}
	{	//SHADOW INIT
		LightManager::shadow_init();
		glEnable(GL_BLEND);
	}
	//...
}
void World::setCursorToCenter() {
	SetCursorPos(windowWidth / 2 + windowPos[0], windowHeight / 2 + windowPos[1]);  //TODO  �����cursorPos����׼ȷ
}

void World::reCenter() {
	const double M_PI = 3.14159265358979323846;
	double theta = elevation[0] * M_PI / 180, fi = elevation[1] * M_PI / 180;
	Vec t = center - eye;
	center = eye + Vec(cos(fi)*cos(theta), sin(fi), cos(fi)*sin(theta))*t.abs();
}
void World::setCamera(Point _eye, Point _center) {
	eye = _eye;  center = _center;
	Vec t = center - eye;
	elevation[0] = atan2(t[2], t[0]) * 180 / M_PI;
	elevation[1] = atan2(t[1], hypot(t[0], t[2])) * 180 / M_PI;
}
void World::move(double dx, double dy, double dz) { move(Vec(dx, dy, dz)); }
void World::move(const Vec &ds) { eye += ds; center += ds; }
void World::move(int d, double step) {
	if (d < 0 || d > 2) return;
	if (d == 0) {
		Vec t = ((center - eye)*up).normalize();
		t = step * moveSpeed * t;
		eye += t; center += t;
	}
	else if (d == 1) {
		Vec t = (center - eye).normalize();
		t = step * moveSpeed *t;
		eye += t;  center += t;
	}
	else {
		eye += step * moveSpeed * up;
		center += step * moveSpeed * up;
	}
}
void World::_move(double dx, double dy) {
	Vec up = Vec(0,1,0);
	Vec t = -(up*(center-eye)).normalize()*dx*0.1;
	eye += moveSpeed*t; center += moveSpeed*t;
	t = -up*dy*0.1;
	eye += moveSpeed*t; center += moveSpeed*t;
}
void World::rotate(double angle, double x, double y, double z) {}
void World::rotate(int d, double step) {
	if (d < 0 || d > 1) return;
	if (d == 0) elevation[0] += rotateSpeed * step;
	else elevation[1] += rotateSpeed * step;
	if (elevation[1] > 75) elevation[1] = 75;
	if (elevation[1] < -75) elevation[1] = -75;

	reCenter();
}
void World::zoom(double d) {
	zoomFactor += zoomSpeed * d;
	if (zoomFactor > 3.5) zoomFactor = 3.5;
	if (zoomFactor < 0.1) zoomFactor = 0.1;
}

void World::drawAll() {
	for (auto o : objects) o.second->draw();
	if (_display != NULL) _display();
}

/*  GLU FUNC  */
void World::perspective() {
	gluPerspective(45*zoomFactor, (double)windowWidth / windowHeight, 0.1, 1000);
}
void World::lookAt() {
	gluLookAt(eye[0], eye[1], eye[2],  center[0], center[1], center[2],  up[0], up[1], up[2]);
}


/*  GLUT FUNC  */
void World::idle() {
	glutPostRedisplay();
}

void World::display() {
	if (focusState == GLUT_ENTERED)
		setCursorToCenter();

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//perspective();  //gluPerspective(45, (double)windowWidth / windowHeight, 0.1, 500);

	//glMatrixMode(GL_MODELVIEW);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	//gluLookAt(eye[0], eye[1], eye[2],
	//	center[0], center[1], center[2],
	//	up[0], up[1], up[2]);


	LightManager::displayWithShadow(drawAll);
	//drawAll();
	glutSwapBuffers();

	{
		int err = glGetError();
		//if (err != GL_NO_ERROR) printf("%d: %s\n", err, (char *)glewGetErrorString(err));
		//1281:  #define GL_INVALID_VALUE 0x0501
	}
}





//  ���溯���޸ĺ�����README.md��ע��
void World::keyboard(unsigned char key, int x, int y) {
	const double moveStep = 1;
	const double rotateStep = 8;

	switch (key) {
	case 27: exit(0);
	case 'a': case 'A':  //����ͼ�α���ԭ��������ҵ������ƶ�һ������תĳ���Ƕȵ��߼�������
		move(0, -moveStep);
		break;
	case 'd': case 'D':
		move(0, moveStep);
		break;
	case 'w': case 'W':
		move(1, moveStep);
		break;
	case 's': case 'S':
		move(1, -moveStep);
		break;
	case 'z': case 'Z':
		move(2, -moveStep);
		break;
	case 'c': case 'C':
		move(2, moveStep);
		break;
	case '-':  //�ٶȵĵ���
		moveSpeed -= 0.005;
		break;
	case '+':
		moveSpeed += 0.005;
		break;

	case 'j': case 'J':  //����ͼ�α���ԭ��������ҵ������ƶ�һ������תĳ���Ƕȵ��߼�������
		rotate(0, -rotateStep);
		break;
	case 'l': case 'L':
		rotate(0, rotateStep);
		break;
	case 'i': case 'I':
		rotate(1, rotateStep);
		break;
	case 'k': case 'K':
		rotate(1, -rotateStep);
		break;
		//case 'f': case 'F':
		//	autoForward = !autoForward;
		//	break;

		//case ',': case '<':
		//	REP (i, 0, 2) lightColor[1][i] -= 0.1;
		//	break;
		//case '.': case '>':
		//	REP (i, 0, 2) lightColor[1][i] += 0.1;
		//	break;
	default:
		break;
	}
	glutPostRedisplay();
}
void World::special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		grabScreen();
		break;
	case GLUT_KEY_F12:
		(++gameMode) %= gameModeNum;
		break;
	default:
		break;
	}
}

//  TODO
void World::motion(int x, int y) {
	POINT pos;
	Point pcenter;
	if (focusState == GLUT_ENTERED) {
		switch (mouseState[0]*4+mouseState[1]*2+mouseState[2]) {
		/*  orbit  */
		case 3:  //���
			GetCursorPos(&pos);
			x = pos.x;  y = pos.y;
			elevation[0] += rotateSpeed * (x - cursorPos[0]);
			elevation[1] += -rotateSpeed * (y - cursorPos[1]);
			if (elevation[1] > 75) elevation[1] = 75;
			if (elevation[1] < -75) elevation[1] = -75;

			pcenter = center;
			reCenter();
			eye = eye + (pcenter - center);
			center = pcenter;
			break;

		/*  zoom  */
		case 5:  //�м�
			GetCursorPos(&pos);
			zoom(pos.y - cursorPos[1]);
			break;

		/*  zoom to fit  */
		case 1:  //���+�м�
			zoomFactor = 1;
			break;

		/*  pan  */
		case 6:
			GetCursorPos(&pos);
			x = pos.x;  y = pos.y;
			_move(x - cursorPos[0], y - cursorPos[1]);
			break;
		default:
			break;
		}

		glutPostRedisplay();
	}
}
void World::passiveMotion(int x, int y) {
	POINT pos;
	if (focusState == GLUT_ENTERED) {
		GetCursorPos(&pos);
		x = pos.x;  y = pos.y;
		elevation[0] += rotateSpeed * (x - cursorPos[0]);
		elevation[1] += -rotateSpeed * (y - cursorPos[1]);
		if (elevation[1] > 75) elevation[1] = 75;
		if (elevation[1] < -75) elevation[1] = -75;
		reCenter();

		glutPostRedisplay();
	}
}
void World::entry(int state) {
	focusState = state;
	if (state == GLUT_ENTERED)
		setCursorToCenter();
}
void World::mouseClick(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		mousedw(x, y, button);
	}
	mouseState[button] = state;
	
}


void World::mousedw(int x, int y, int but) {
	//printf("Mouse button %d pressed at %d %d\n", but, x, y);
	gl_select(x, windowHeight - y); //Important: gl (0,0) ist bottom left but window coords (0,0) are top left so we have to change this!
}

void World::gl_select(int x, int y) {
	GLuint buff[4096] = { 0 };
	GLint hits, view[4];

	glSelectBuffer(4096, buff);

	//retrieve info about the viewport
	glGetIntegerv(GL_VIEWPORT, view);
	//switch select mode
	glRenderMode(GL_SELECT);


	glInitNames();
	glPushName(0);

	//modify the vieving volume, restricting selection area around the cursor
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	//restrict the draw to an area around the cursor
	gluPickMatrix(x, y, 0.1, 0.1, view);
	perspective();  //gluPerspective(45*zoomFactor, 1, 1, 500);

	//pretend to draw the objects onto the screen
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
	drawAll();

	//restore the view
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	//get number of objects drawed in that area and return to render mode
	hits = glRenderMode(GL_RENDER);

	if (hits >= 1) {
		int choose = buff[3];
		GLuint depth = buff[1];

		for (int i = 0; i < hits; i++) {
			if (buff[i * 4 + 1] < (GLuint)depth) {	//obtain selected object with minimum depth
				choose = buff[i * 4 + 3];
				depth = buff[i * 4 + 1];
			}
		}
		chosenID = choose;
	}
	else chosenID = -1;
	cout << "hits: " << hits << "   ID: " << chosenID << endl;

	glMatrixMode(GL_MODELVIEW);
}




/*  ��ͼ  */

string World::scrennshotsDir = "screenshots";


typedef unsigned char Byte;
typedef unsigned short int Word;
typedef unsigned long int DWord;
struct BitMapFileHeader {  //λͼ�ļ�ͷ
	Word bfType;  //���ܷ�������һ�������Ϊshort�������32λ??  //��Ҫ�Ƕ�������64λ��Ҫ��ô��??...(����Ӧ�û���������������...)
	DWord bfSize;  //˵����λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	Word bfReserved1;
	Word bfReserved2;
	DWord bfOffBits;  //˵���� "the beginning of the file" �� "the bitmap data" ��ƫ������  //����һ���bmp��˵��54
};
struct BitMapInfoHeader {
	DWord biSize;  //˵��BITMAPINFOHEADER�ṹ����Ҫ���ֽ���
	DWord biWidth;
	DWord biHeight;  //biHeightΪ������ͼ���Ǵ����������µ�˳������
	Word biPlanes;  //λƽ����
	Word biBitCount;  //ÿ����λ��
	DWord biCompression;  //ѹ�����ͣ�0Ϊ��ѹ��
	DWord biSizeImage;  //ѹ��ͼ���С���ֽ�����
	DWord biXPelsPerMeter;  //ˮƽ�ֱ���
	DWord biYPelsPerMeter;
	DWord biClrUsed;  //ʹ�õ�ɫ����
	DWord biClrImportant;  //��Ҫɫ����
};
#define BMP_Header_Length 54
//void getFiles(string path, vector<string>& files) {  
//    //�ļ����  
//    long   hFile   =   0;  
//    //�ļ���Ϣ  
//    struct _finddata_t fileinfo;
//    string p;  
//    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
//    {  
//        do  
//        {  
//            //�����Ŀ¼,����֮  
//            //�������,�����б�  
//            if((fileinfo.attrib &  _A_SUBDIR))  
//            {  
//                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
//                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
//            }  
//            else  
//            {  
//                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
//            }  
//        }while(_findnext(hFile, &fileinfo)  == 0);  
//        _findclose(hFile);  
//    }  
//}
//int getMax(string s) {
//	int i,j;
//	for (i=s.size()-1; i>=0; i--)
//		if (s[i] == '.') break;
//		else if (s[i] == '\\') return -1;
//	for (j=i-1; j>=0; j--)
//		if (s[j] == '\\') break;
//	if (i<0 || j<0 || i==j+1) return -1;
//	return stringToInt(s.substr(j+1, i-j-1));
//}
void World::grabScreen(void) {  //TODO  ��ͼʱ�������һ����ʾ��Ϣ
	//static int times = -1;
	//if (times == -1) {
	//	vector<string> files;
	//	getFiles(scrennshotsDir, files);
	//	for (int i=0; i<files.size(); i++) times = max(times, getMax(files[i]));
	//}
	//times++;
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	FILE*    pWritingFile;
	GLubyte* pPixelData;
	GLubyte  BMP_Header[BMP_Header_Length];
	GLint    i, j;
	GLint    PixelDataLength;

	// �����������ݵ�ʵ�ʳ���
	i = windowWidth * 3;   // �õ�ÿһ�е��������ݳ���
	while (i % 4 != 0) ++i;

	PixelDataLength = i * windowHeight;

	// �����ڴ�ʹ��ļ�
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0) exit(0);

	//fopen_s(&pWritingFile, (scrennshotsDir + "\\\\" + intToString(times) + ".bmp").c_str(), "wb");
	string s = intToString(sys.wYear) + "-" + intToString(sys.wMonth) + "-" + intToString(sys.wDay) + "-" + intToString(sys.wHour) + "-" + intToString(sys.wMinute) + "-" + intToString(sys.wSecond) + "-" + intToString(sys.wMilliseconds);
	fopen_s(&pWritingFile, (scrennshotsDir + "\\\\" + s + ".bmp").c_str(), "wb");
	if (pWritingFile == 0) exit(0);

	// ��ȡ����
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  //ʹ��ÿ�е�������4�ı�������
	glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);


	BitMapFileHeader fileHeader;
	fileHeader.bfType = 0x4D42;
	fwrite(&fileHeader.bfType, sizeof(Word), 1, pWritingFile);

	BitMapInfoHeader infoHeader;
	int rowBytes = (24 >> 3) * windowWidth, offset = rowBytes % 4;
	if (offset != 0) rowBytes += offset = 4 - offset;
	fileHeader.bfSize = windowHeight * windowWidth * 3 + 54;
	fileHeader.bfReserved1 = fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = 54;
	fwrite(&fileHeader.bfSize, sizeof(DWord) * 3, 1, pWritingFile);

	infoHeader.biSize = 40;
	infoHeader.biWidth = windowWidth;
	infoHeader.biHeight = windowHeight;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = 0;
	infoHeader.biSizeImage = windowHeight * rowBytes;
	infoHeader.biXPelsPerMeter = infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	fwrite(&infoHeader, sizeof(BitMapInfoHeader), 1, pWritingFile);

	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
	//fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);  //OpenGL��BMP_Header����...
	//fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = windowWidth;
	j = windowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// д����������
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// �ͷ��ڴ�͹ر��ļ�
	fclose(pWritingFile);
	free(pPixelData);
}
