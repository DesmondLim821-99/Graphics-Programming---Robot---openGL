
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

BITMAP BMP;
HBITMAP hBMP = NULL;

float tx1 = 0.0;
int qno = 0;
float rx = 0.0, rspeed = 1.0;
float tx = 0.0, ty = 0.0;
float tz = 0.0, tspeed = 0.1;
float oNear = -10.0, oFar = 75.0;
float pNear = 1.0, pFar = 21.0;
float ptx = 0.0, pty = 0.0, ptspeed = 0.5;
float pr = 0.0, prspeed = 1.0;
float rs1 = 1.0;

float rShoulder = 0.0;

float rLowerLimb = 0.0;

boolean isOrtho = false;

float left = -2.0;
float right = 2.0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_UP) {
			//if (tz > oNear + rs1) {
				tz -= tspeed;
			//}
			//else {
			//	if (tz > pNear + rs1) {
			//		tz -= tspeed;
			//	}
			//}
		}
		else if (wParam == VK_DOWN) {
			//if (isOrtho) {
				//if (tz < oFar - rs1) {
					tz += tspeed;
				//}
				//else {
				//	if ((tz < pFar - rs1)) {
				//		tz += tspeed;
				//	}
				//}
			//}
		}

		else if (wParam == VK_LEFT) {
			tx1 -= tspeed;
		}
		else if (wParam == VK_RIGHT) {
			tx1 += tspeed;
		}
		else if (wParam == 0x70) {
			pr += prspeed;
			/*left -= 0.01;
			right += 0.01;*/
		}
		else if (wParam == 0x71) {
			pr -= prspeed;
		}
		else if (wParam == 0x72) {
			ty += tspeed;
		}
		else if (wParam == 0x73) {
			ty -= tspeed;
		}
		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = 0;
			/*tz = pNear + rs1;*/
		}

		else if (wParam == 'W') {
			rShoulder += rspeed;
		}
		else if (wParam == 'S') {
			rShoulder -= rspeed;
		}
		else if (wParam == 'I') {
			rLowerLimb += rspeed;
		}
		else if (wParam == 'K') {
			rLowerLimb -= rspeed;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//void drawCube(float sc) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//
//	glRotatef(0.01, 1.0, 1.0, 1.0);
//	/*glScalef(0.5, 0.5, 0.5);*/
//	glBegin(GL_LINE_LOOP);
//	glColor3f(1.0, 0.0, 0.0);
//	glVertex3f(0.0f, 0.0f, sc); // face 1 (bottom)
//	glVertex3f(sc, 0.0f, sc);
//	glVertex3f(sc, 0.0f, sc);
//	glVertex3f(0.0f, 0.0f, 0.0f); //origin
//
//	glColor3f(0.0, 1.0, 0.0);
//	glVertex3f(0.0f, 0.0f, 0.0f); // face 2 (Left)
//	glVertex3f(0.0f, sc, 0.0f);
//	glVertex3f(0.0f, sc, sc);
//	glVertex3f(0.0f, 0.0f, sc); //origin
//
//	glColor3f(0.0, 0.0, 1.0);
//	glVertex3f(0.0f, 0.0f, sc); // face 3 (front)
//	glVertex3f(0.0f, sc, sc);
//	glVertex3f(sc, sc, sc);
//	glVertex3f(sc, 0.0f, sc); //origin
//
//	glColor3f(1.0, 0.0, 0.0);
//	glVertex3f(sc, 0.0f, sc); // face 4 (right)
//	glVertex3f(sc, sc, sc);
//	glVertex3f(sc, sc, 0.0f);
//	glVertex3f(sc, 0.0f, 0.0f); //origin
//
//	glColor3f(0.0, 1.0, 0.0);
//	glVertex3f(sc, 0.0f, 0.0f); // face 5 (back)
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(0.0f, sc, 0.0f);
//	glVertex3f(sc, sc, 0.0f); //origin
//
//	glColor3f(0.0, 0.0, 1.0);
//	glVertex3f(sc, sc, 0.0f); // face 6 (top)
//	glVertex3f(0.0f, sc, 0.0f);
//	glVertex3f(0.0f, sc, sc);
//	glVertex3f(sc, sc, sc); //origin
//	glEnd();
//}

void pyramid(float sc) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glRotatef(0.01, 1.0, 1.0, 1.0);


	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sc); // face 1 (bottom base)
	glVertex3f(sc, 0.0f, sc);
	glVertex3f(sc, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); //origin
	glVertex3f(sc / 2, sc, sc / 2);
	glVertex3f(0.0f, 0.0f, sc);
	glVertex3f(sc / 2, sc, sc / 2);
	glVertex3f(sc, 0.0f, sc);
	glVertex3f(sc / 2, sc, sc / 2);
	glVertex3f(sc, 0.0f, 0.0f);
	glVertex3f(sc / 2, sc, sc / 2);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

void drawSphere(float r, int sl, int h) {
	GLUquadricObj* sphere = NULL; //create quadric obj pointer
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, r, sl, h);
	gluDeleteQuadric(sphere);
}

void drawCylinder(float tr, float br, float h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, tr, br, h, 10, 10);
	gluDeleteQuadric(cylinder);
}

void drawCone(float r, float h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.0, r, h, 10, 10);
	gluDeleteQuadric(cylinder);
}

void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;
	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < 2 * PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void projection() {
	glMatrixMode(GL_PROJECTION); // refer to the projection
	glLoadIdentity();
	glTranslatef(tx1, ty, tz);
	/*glTranslatef(0.0, 0.0, 0.1);*/
	//glTranslatef(ptx, pty, 0.0); //translate x and y for projection
	glRotatef(pr, 0.0, 1.0, 0.0);
	if (isOrtho) {
		glOrtho(-2.0, 2.0, -2.0, 2.0, oNear, oFar);
	}
	else {
		gluPerspective(30.0, 1.0, -1.0, 1.0);
		glFrustum(-2.0, 2.0, -2.0, 2.0, pNear, pFar);
	}
}


GLuint loadTexture(LPCSTR filename) {

	GLuint texture = 0;

	// Step 3 initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return texture;
}


void drawShoulderRec() {   // Shoulder rectangle

	glBegin(GL_QUADS); 
	/*glColor3f(1.0, 0.0, 0.0);*/
	glVertex3f(0.0f, 0.0f, 0.0f); // face 1 (bottom)
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.25f);
	glVertex3f(0.0f, 0.0f, 0.25f); //origin

	glVertex3f(0.0f, 0.0f, 0.25f); // face 2 (front)
	glVertex3f(0.0f, 0.3f, 0.25f);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glVertex3f(0.1f, 0.0f, 0.25f); //origin

	glVertex3f(0.1f, 0.0f, 0.25f); // face 3 (right)
	glVertex3f(0.1f, 0.3f, 0.25f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f); //origin

	glVertex3f(0.1f, 0.0f, 0.0f); // face 4 (back)
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); //origin

	glVertex3f(0.0f, 0.0f, 0.0f); // face 5 (left)
	glVertex3f(0.0f, 0.0f, 0.25f);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glVertex3f(0.0f, 0.3f, 0.0f); //origin

	glVertex3f(0.0f, 0.3f, 0.0f); // face 6 (top)
	glVertex3f(0.0f, 0.3f, 0.25f);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glVertex3f(0.1f, 0.3f, 0.0f); //origin

	glEnd();
}

void drawHalfRec() {
	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.0f, 0.0f); // face 1 bottom
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.1f, 0.0f, 0.2f);
		glVertex3f(0.0f, 0.0f, 0.2f);

		glVertex3f(0.0f, 0.0f, 0.2f); // face 2 back
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.3f, 0.0f);
		glVertex3f(0.0f, 0.3f, 0.2f);

		glVertex3f(0.0f, 0.3f, 0.2f); // face 3 right
		glVertex3f(0.0f, 0.0f, 0.2f);
		glVertex3f(0.1f, 0.0f, 0.2f);
		glVertex3f(0.0f, 0.3f, 0.2f);

		glVertex3f(0.0f, 0.3f, 0.2f); // face 4 front
		glVertex3f(0.1f, 0.0f, 0.2f);
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.3f, 0.0f);

		glVertex3f(0.0f, 0.3f, 0.0f); // face 5 left
		glVertex3f(0.1f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();
}

void drawHandPalm() {
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 1 top
	glVertex3f(0.05f, 0.0f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.02f);
	glVertex3f(0.0f, 0.0f, 0.02f);

	glVertex3f(0.0f, 0.0f, 0.02f); // face 2 front
	glVertex3f(0.05f, 0.0f, 0.02f);
	glVertex3f(0.06f, -0.05f, 0.02f);
	glVertex3f(0.03f, -0.07f, 0.02f);
	glVertex3f(-0.01f, -0.05f, 0.02f);
	glVertex3f(0.0f, 0.0f, 0.02f);

	glVertex3f(0.0f, 0.0f, 0.02f); // face 3 right
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.02f);

	glVertex3f(-0.01f, -0.05f, 0.02f); // face 4 botton right
	glVertex3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(0.03f, -0.07f, 0.0f);
	glVertex3f(0.03f, -0.07f, 0.02f);

	glVertex3f(0.03f, -0.07f, 0.02f); // face 5 botton left
	glVertex3f(0.03f, -0.07f, 0.0f);
	glVertex3f(0.06f, -0.05f, 0.0f);
	glVertex3f(0.06f, -0.05f, 0.02f);

	glVertex3f(0.06f, -0.05f, 0.02f); // face 6 left
	glVertex3f(0.06f, -0.05f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.02f);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(0.0f, 0.0f, 0.0f); // face 7 back
		glVertex3f(0.05f, 0.0f, 0.0f);
		glVertex3f(0.06f, -0.05f, 0.0f);
		glVertex3f(0.03f, -0.07f, 0.0f);
		glVertex3f(-0.01f, -0.05f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

void drawHandPalmOutline() {
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 1 top
	glVertex3f(0.05f, 0.0f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.02f);
	glVertex3f(0.0f, 0.0f, 0.02f);

	glVertex3f(0.0f, 0.0f, 0.02f); // face 2 front
	glVertex3f(0.05f, 0.0f, 0.02f);
	glVertex3f(0.06f, -0.05f, 0.02f);
	glVertex3f(0.03f, -0.07f, 0.02f);
	glVertex3f(-0.01f, -0.05f, 0.02f);
	glVertex3f(0.0f, 0.0f, 0.02f);

	glVertex3f(0.0f, 0.0f, 0.02f); // face 3 right
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.02f);

	glVertex3f(-0.01f, -0.05f, 0.02f); // face 4 botton right
	glVertex3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(0.03f, -0.07f, 0.0f);
	glVertex3f(0.03f, -0.07f, 0.02f);

	glVertex3f(0.03f, -0.07f, 0.02f); // face 5 botton left
	glVertex3f(0.03f, -0.07f, 0.0f);
	glVertex3f(0.06f, -0.05f, 0.0f);
	glVertex3f(0.06f, -0.05f, 0.02f);

	glVertex3f(0.06f, -0.05f, 0.02f); // face 6 left
	glVertex3f(0.06f, -0.05f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.0f);
	glVertex3f(0.05f, 0.0f, 0.02f);

	glVertex3f(0.0f, 0.0f, 0.0f); // face 7 back
	glVertex3f(0.05f, 0.0f, 0.0f);
	glVertex3f(0.06f, -0.05f, 0.0f);
	glVertex3f(0.03f, -0.07f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}

void drawFinger(float fingerL, float fingerwidth) {
	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.0f, 0.0f); // face 1 (bottom)
		glVertex3f(fingerwidth, 0.0f, 0.0f);
		glVertex3f(fingerwidth, 0.0f, 0.02f);
		glVertex3f(0.0f, 0.0f, 0.02f); //origin

		glVertex3f(0.0f, 0.0f, 0.02f); // face 2 (front)
		glVertex3f(0.0f, fingerL, 0.02f);
		glVertex3f(fingerwidth, fingerL, 0.02f);
		glVertex3f(fingerwidth, 0.0f, 0.02f); //origin

		glVertex3f(fingerwidth, 0.0f, 0.02f); // face 3 (right)
		glVertex3f(fingerwidth, fingerL, 0.02f);
		glVertex3f(fingerwidth, fingerL, 0.0f);
		glVertex3f(fingerwidth, 0.0f, 0.0f); //origin

		glVertex3f(fingerwidth, 0.0f, 0.0f); // face 4 (back)
		glVertex3f(fingerwidth, fingerL, 0.0f);
		glVertex3f(0.0f, fingerL, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f); //origin

		glVertex3f(0.0f, 0.0f, 0.0f); // face 5 (left)
		glVertex3f(0.0f, 0.0f, 0.02f);
		glVertex3f(0.0f, fingerL, 0.02f);
		glVertex3f(0.0f, fingerL, 0.0f); //origin

		glVertex3f(0.0f, fingerL, 0.0f); // face 6 (top)
		glVertex3f(0.0f, fingerL, 0.02f);
		glVertex3f(fingerwidth, fingerL, 0.02f);
		glVertex3f(fingerwidth, fingerL, 0.0f); //origin
	glEnd();
}



void drawLeftArm() {
	/*glRotatef(0.01, 1.0, 1.0, 1.0);*/
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	/*glRotatef(-25, 1.0, 1.0, 0.0);*/
	glTranslatef(0.0, 0.3, 0.0);  //Temperory move whole left arm up abit

	glRotatef(rShoulder, 1.0, 0.0, 0.0);


	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawCylinder(0.1, 0.1, 0.1); // Shoulder Cylinder
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.04, -0.15, -0.125); 
		glRotatef(16, 0.0, 0.0, 1.0);
		glColor3f(0.2, 0.2, 0.2);
		drawShoulderRec(); // Shoulder rectangle
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.12, -0.16, -0.1);
		glColor3f(1.0, 0.27, 0.0);
		drawHalfRec(); // shoulder half rectangle 1
	glPopMatrix();


	glPushMatrix();
		glTranslatef(-0.08, -0.32, 0.1);
		glRotatef(180, 0.0, 1.0, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawHalfRec(); // shoulder half rectangle 2
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.04, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawCylinder(0.05, 0.05, 0.2); // upper Limp mini cylinder
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.07, 0.0, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(0.2, 0.2, 0.2);
		drawCylinder(0.04, 0.02, 0.4);  // Upper Limb Cylinder
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.07, -0.42, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawSphere(0.02, 10, 10);  // Sphere between limb
	glPopMatrix();


	glPushMatrix();

	glTranslatef(-0.07, -0.44, 0.0);
	glRotatef(rLowerLimb, 1.0, 0.0, 0.0);

	glPushMatrix();
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(0.2, 0.2, 0.2);
		drawCylinder(0.02, 0.04, 0.1); //lower Limb Cylinder (Upper)
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawCylinder(0.05, 0.05, 0.25); //Lower Limb Cylinder (Middle)
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.35, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(0.2, 0.2, 0.2);
		drawCylinder(0.05, 0.02, 0.05); //lower Limb Cylinder (lower)
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.42, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawSphere(0.02, 10, 10);  // Sphere between limb
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.43, 0.0); // move Hand and fingers to right location
	glRotatef(-90, 0.0, 1.0, 0.0);
	glRotatef(-10, 1.0, 0.0, 0.0);

	glPushMatrix();
		glScalef(1.1, 1.1, 1.1);
		glColor3f(1.0, 1.0, 0.0);
		drawHandPalm(); // Hand Palm
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0);
		drawHandPalmOutline(); // Hand palm Outline
	glPopMatrix();

	glPushMatrix();
		glRotatef(-35, 0.0, 0.0, 1.0);
		glRotatef(20, 1.0, 0.0, 0.0);
		glTranslatef(-0.01, -0.05, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawFinger(0.05f, 0.02f); // thump finger 1
	glPopMatrix();

	glPushMatrix();
		glRotatef(20, 1.0, 0.0, 0.0);
		glTranslatef(-0.04, -0.10, 0.0);
		glColor3f(0.3, 0.3, 0.3);
		drawFinger(0.06f, 0.02f); // thump finger 2
	glPopMatrix();

	glPushMatrix();
		glRotatef(20, 1.0, 0.0, 0.0);
		glTranslatef(-0.04, -0.13, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawFinger(0.03f, 0.02f); // thump finger 3
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.10, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawFinger(0.04f, 0.02f); // Middle finger 1
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.15, 0.0);
		glColor3f(0.3, 0.3, 0.3);
		drawFinger(0.05f, 0.02f); // Middle finger 2
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.18, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawFinger(0.03f, 0.02f); // Middle finger 3
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.04, -0.09, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawFinger(0.03f, 0.02f); // last finger 1
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0.04, -0.13, 0.0);
		glColor3f(0.3, 0.3, 0.3);
		drawFinger(0.04f, 0.02f); // last finger 2
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.04, -0.15, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawFinger(0.02f, 0.02f); // last finger 3
	glPopMatrix();
	
	glPopMatrix(); 

	glPushMatrix();
		glTranslatef(0.02, -0.2, -0.05);
		glColor3f(0.0, 0.74, 1.0);
		drawFinger(0.05f, 0.02f); // Blue light at lower cylinder
	glPopMatrix();


	glPopMatrix(); //Pop for retating lower arm

	glPushMatrix();
		glTranslatef(-0.02, -0.25, -0.04);
		glColor3f(0.0, 0.74, 1.0);
		drawSphere(0.01, 10, 10); // Blue light spot at uppder mini Cylinder
	glPopMatrix();

	glPopMatrix(); // Pop for rotating whole arm
}

void drawRightArm() {
	/*glRotatef(0.01, 1.0, 1.0, 1.0);*/
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(180, 0.0, 1.0, 0.0);
	/*glRotatef(-25, 1.0, 1.0, 0.0);*/
	glTranslatef(0.0, 0.3, 0.0);  //Temperory move whole left arm up abit

	glRotatef(rShoulder, 1.0, 0.0, 0.0);


	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	drawCylinder(0.1, 0.1, 0.1); // Shoulder Cylinder
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.04, -0.15, -0.125);
	glRotatef(16, 0.0, 0.0, 1.0);
	glColor3f(0.2, 0.2, 0.2);
	drawShoulderRec(); // Shoulder rectangle
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.12, -0.16, -0.1);
	glColor3f(1.0, 0.27, 0.0);
	drawHalfRec(); // shoulder half rectangle 1
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.08, -0.32, 0.1);
	glRotatef(180, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawHalfRec(); // shoulder half rectangle 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.04, -0.1, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	drawCylinder(0.05, 0.05, 0.2); // upper Limp mini cylinder
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.07, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawCylinder(0.04, 0.02, 0.4);  // Upper Limb Cylinder
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.07, -0.42, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	drawSphere(0.02, 10, 10);  // Sphere between limb
	glPopMatrix();


	glPushMatrix();

	glTranslatef(-0.07, -0.44, 0.0);
	glRotatef(-rLowerLimb, 1.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawCylinder(0.02, 0.04, 0.1); //lower Limb Cylinder (Upper)
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawCylinder(0.05, 0.05, 0.25); //Lower Limb Cylinder (Middle)
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.35, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawCylinder(0.05, 0.02, 0.05); //lower Limb Cylinder (lower)
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.42, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	drawSphere(0.02, 10, 10);  // Sphere between limb
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.43, 0.0); // move Hand and fingers to right location
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(10, 1.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(1.1, 1.1, 1.1);
	glColor3f(1.0, 1.0, 0.0);
	drawHandPalm(); // Hand Palm
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(5.0);
	drawHandPalmOutline(); // Hand palm Outline
	glPopMatrix();

	glPushMatrix();
	glRotatef(35, 0.0, 0.0, 1.0);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glTranslatef(-0.01, -0.05, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawFinger(0.05f, 0.02f); // thump finger 1
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 1.0, 0.0, 0.0);
	glTranslatef(-0.04, -0.10, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	drawFinger(0.06f, 0.02f); // thump finger 2
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 1.0, 0.0, 0.0);
	glTranslatef(-0.04, -0.13, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawFinger(0.03f, 0.02f); // thump finger 3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.10, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawFinger(0.04f, 0.02f); // Middle finger 1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.15, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	drawFinger(0.05f, 0.02f); // Middle finger 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.18, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawFinger(0.03f, 0.02f); // Middle finger 3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.04, -0.09, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawFinger(0.03f, 0.02f); // last finger 1
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.04, -0.13, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	drawFinger(0.04f, 0.02f); // last finger 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.04, -0.15, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	drawFinger(0.02f, 0.02f); // last finger 3
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.02, -0.2, 0.03);
	glColor3f(0.0, 0.74, 1.0);
	drawFinger(0.05f, 0.02f); // Blue light at lower cylinder
	glPopMatrix();


	glPopMatrix(); //Pop for retating lower arm

	glPushMatrix();
	glTranslatef(-0.02, -0.25, 0.04);
	glColor3f(0.0, 0.74, 1.0);
	drawSphere(0.01, 10, 10); // Blue light spot at uppder mini Cylinder
	glPopMatrix();

	glPopMatrix(); // Pop for rotating whole arm
}

//void drawWeapon()
//{
//	glBegin(GL_LINE_LOOP);
//	glColor3f(0.0, 1.0, 1.0);
//	//left1 back
//	glVertex3f(0.0, 0.0, 0.0);	//A
//	glVertex3f(0.0, 0.0, 1.3);	//B
//	glVertex3f(0.3, 0.0, 1.3);	//H
//	glVertex3f(0.3, 0.0, 0.0);	//G
//	glVertex3f(0.0, 0.0, 0.0);	//A
//
//	glVertex3f(0.0, 0.0, 1.3);	//B
//	glVertex3f(0.0, -1.0, 0.8);	//C
//	glVertex3f(0.3, -1.0, 0.8);	//I
//	glVertex3f(0.3, 0.0, 1.3);	//H
//	glVertex3f(0.0, 0.0, 1.3);	//B
//
//	glVertex3f(0.0, -1.0, 0.8);	//C
//	glVertex3f(0.0, -1.0, 0.6);	//D
//	glVertex3f(0.3, -1.0, 0.8);	//J
//	glVertex3f(0.3, -1.0, 0.8);	//I
//	glVertex3f(0.0, -1.0, 0.8);	//C
//
//	glVertex3f(0.0, -1.0, 0.6);	//D
//	glVertex3f(0.0, -1.2, 0.5);	//E
//	glVertex3f(0.3, -1.2, 0.5);	//K
//	glVertex3f(0.3, -1.0, 0.8);	//J
//	glVertex3f(0.0, -1.0, 0.6);	//D
//
//	glVertex3f(0.0, -1.2, 0.5);	//E
//	glVertex3f(0.0, -1.0, 0.3);	//F
//	glVertex3f(0.3, -1.0, 0.3);	//L
//	glVertex3f(0.3, -1.2, 0.5);	//K
//	glVertex3f(0.0, -1.2, 0.5);	//E
//
//	glVertex3f(0.0, -1.0, 0.3);	//F
//	glVertex3f(0.0, 0.0, 0.0);	//A
//	glVertex3f(0.3, 0.0, 0.0);	//G
//	glVertex3f(0.3, -1.0, 0.3);	//L
//	glVertex3f(0.0, -1.0, 0.3);	//F
//
//	//back to A
//	glVertex3f(0.0, 0.0, 0.0);	//A
//	glEnd();
//}

void drawSwordTips() {

	glPushMatrix();

	glRotatef(180, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
		glVertex3f(0.0f, 0.0f, 0.0f); // face 1 botton
		glVertex3f(0.0f, 0.0f, 0.02f);
		glVertex3f(0.05f, 0.0f, 0.02f);
		glVertex3f(0.05f, 0.0f, 0.0f);

		glVertex3f(0.05f, 0.0f, 0.0f); // face 2 top
		glVertex3f(0.05f, 0.0f, 0.02f);
		glVertex3f(0.0f, 0.1f, 0.02f);
		glVertex3f(0.0f, 0.1f, 0.0f);

		glVertex3f(0.0f, 0.1f, 0.0f); // face 3 back
		glVertex3f(0.05f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.1f, 0.0f);

		glVertex3f(0.0f, 0.1f, 0.0f); // face 4 right
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.02f);
		glVertex3f(0.0f, 0.1f, 0.02f);

		glVertex3f(0.0f, 0.1f, 0.02f); // face 5 front
		glVertex3f(0.0f, 0.0f, 0.02f);
		glVertex3f(0.05f, 0.0f, 0.02f);
		glVertex3f(0.0f, 0.1f, 0.02f);

	glEnd();
	glPopMatrix();
}

void drawSphereCore(float r, int sl, int h) {
	GLUquadricObj* sphere = NULL; //create quadric obj pointer
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_POINT);
	gluSphere(sphere, r, sl, h);
	gluDeleteQuadric(sphere);
}

void drawSword() {

	glColor3f(0.3, 0.3, 0.3);
	drawFinger(0.02, 0.05); //Sword handle 1

	glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		glTranslatef(0.0, 0.02, 0.0);
		drawFinger(0.02, 0.05); // sword handle 2
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(0.0, 0.04, 0.0);
		drawFinger(0.02, 0.05); // sword handle 3
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		glTranslatef(0.0, 0.06, 0.0);
		drawFinger(0.02, 0.05); // sword handle 4
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(0.0, 0.08, 0.0);
		drawFinger(0.02, 0.05); // sword handle 5
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(-0.05, 0.1, 0.0);
		drawFinger(0.02, 0.15); // sword Connector 1
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(-0.069, 0.12, 0.0);
		drawFinger(0.35, 0.05); // sword body 1 short
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(-0.018, 0.12, 0.0);
		drawFinger(0.45, 0.03); // sword body 2 short
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.05, 0.12, 0.0);
		drawFinger(0.5, 0.06); // sword body 1 long
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.10, 0.12, 0.0);
		drawFinger(0.6, 0.02); // sword body 2 long
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.018, 0.47, 0.02);
		drawSwordTips(); // Sword Tip 1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.10, 0.62, 0.02);
	drawSwordTips(); // Sword Tip 2
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(0.03, 0.57, 0.01);
		glRotatef(90, 1.0, 0.0, 0.0);
		drawCylinder(0.04, 0.04, 0.35); // sword cylinder 
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0, 0.74, 1.0);
		glTranslatef(0.03, 0.16, 0.01);
		drawSphereCore(0.025, 20, 20); // sword power core sphere
	glPopMatrix();
}

void background(float size) {

	/*glDisable(GL_LIGHTING);*/
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	GLuint textureArr[6];
	glColor3f(1.0, 1.0, 1.0);
	/*textureArr[1] = loadTexture("Back.bmp");*/
	textureArr[1] = loadTexture("concrete.bmp");
	glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(size/2, size/2, size/2); // back
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-size/2, size/2, size/2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-size/2, -size/2, size/2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(size/2, -size/2, size/2);

	glEnd();
	glDeleteTextures(1, &textureArr[1]);


	/*textureArr[0] = loadTexture("Left.bmp");*/
	textureArr[0] = loadTexture("concrete.bmp");
	glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-size/2, size/2, size/2); // left
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-size/2, size/2, -size/2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(-size/2, -size/2, -size/2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size/2, -size/2, size/2);

	glEnd();
	glDeleteTextures(1, &textureArr[0]);

	/*textureArr[3] = loadTexture("Front.bmp");*/
	textureArr[3] = loadTexture("concrete.bmp");
	glBegin(GL_QUADS);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(size/2, size/2, -size/2); // Front
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-size/2, size/2, -size/2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size/2, -size/2, -size/2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(size/2, -size/2, -size/2);

	glEnd();
	glDeleteTextures(1, &textureArr[3]);

	/*textureArr[2] = loadTexture("Right.bmp");*/
	textureArr[2] = loadTexture("concrete.bmp");
	glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(size/2, size/2, -size/2); // right
		glTexCoord2f(1.0, 0.0);
		glVertex3f(size/2, size/2, size/2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(size/2, -size/2, size/2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(size/2, -size/2, -size/2);

	glEnd();
	glDeleteTextures(1, &textureArr[2]);

	/*textureArr[4] = loadTexture("top.bmp");*/
	textureArr[4] = loadTexture("concrete.bmp");
	glBegin(GL_QUADS);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(size/2, size/2, size/2); // top
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-size/2, size/2, size/2);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size/2, size/2, -size/2);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(size/2, size/2, -size/2);

	glEnd();
	glDeleteTextures(1, &textureArr[4]);

	/*textureArr[5] = loadTexture("bottom.bmp");*/
	textureArr[5] = loadTexture("concrete.bmp");
	glBegin(GL_QUADS);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(size/2, -size/2, size/2); // bottom
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size/2, -size/2, size/2);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-size/2, -size/2, -size/2);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(size/2, -size/2, -size/2);

	glEnd();
	glDeleteTextures(1, &textureArr[5]);

	/*glEnable(GL_LIGHTING);*/
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D); 
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	/*glRotatef(0.01, 0.0, 1.0, 0.0);*/

	if (isOrtho) {
		background(4.0);
	}
	else {
		background(2.0);
	}
	//GLuint textureArr[2];

	//textureArr[0] = loadTexture("left.bmp");
	//textureArr[1] = loadTexture("back.bmp");
	//textureArr[2] = loadTexture("right.bmp");
	//textureArr[3] = loadTexture("front.bmp");
	//textureArr[4] = loadTexture("top.bmp");
	//textureArr[5] = loadTexture("bottom.bmp");

	//glColor3f(1.0, 1.0, 1.0);
	//background(1.0);

	//glDeleteTextures(1, &textureArr[0]);

	
	projection();

	glMatrixMode(GL_MODELVIEW);
	/*glRotatef(0.01, 1.0, 1.0, 1.0);*/
	glPushMatrix();
	/*glRotatef(pr, 0.0, 1.0, 0.0);*/
	glTranslatef(tx1, ty, tz);
	glRotatef(180, 0.0, 1.0, 0.0);

	glPushMatrix();
		glTranslatef(-0.2, 0.0, 0.0);
		drawLeftArm();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.2, 0.0, 0.0);
		drawRightArm();
	glPopMatrix();
	/*drawSword();*/

	glPopMatrix();

	/*Step 5 Remove texture info*/
	glDisable(GL_TEXTURE_2D);
}
//--------------------------------------------------------------------



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//glMatrixMode(GL_PROJECTION); // refer to the projection
	//glLoadIdentity(); // reset matrix
	///*glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);*/ // default
	//gluPerspective(20.0, 1.0, -1.0, 1.0);
	//glFrustum(-10.0, 10.0, -10.0, 10.0, 1.0, 21.0);

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------