#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include<math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib") 

#define WINDOW_TITLE "FPS Robot"

int f = 1.0;
int c = 1.0;
int a = 1.0;
int b = 1.0;
int d = 1.0;

BITMAP BMP;
HBITMAP hBMP = NULL;

float tx1 = 0.0;
int qno = 0;
float rx = 0.0, rspeed = 1.0, rspeed1 = 7.0, sspeed = 0.1;
float tx = 0.0, ty = 0.2;
float tz = 0.0, tspeed = 0.2;
float oNear = -10.0, oFar = 10.0;
float pNear = 1.0, pFar = 21.0;
float ptx = 0.0, pty = 0.0, ptspeed = 0.5;
float pr = 0.0, prspeed = 2.0;
float rs1 = 1.0;
float shoot = 0.0;
float tbody = 0.0;
float rShoulderLeft = 0.0, rShoulderRight = 0.0;
float zShoulderRight = 0.0;
float rhead = 0.0;
float rhead1 = 0.0;
float rLowerLimb = 0.0, rLowerLimb1 = 0.0;
float rLeg = 0.0, rLeg1 = 0.0;
float rLowerLeg = 0.0, rLowerLeg1 = 0.0;

int temp = 1, temp1 = 1, temp2 = 0;
float zSword = 0.0, zSpeed = 0.005;
int waiting = 0;

int option = 0;

float amb[] = { 1.0, 0.0, 0.0 };	//Red Color
float pos[] = { 0.0, 1.0, -0.5 };	// amb light pos (0,1,0) above 
float dif[] = { 0.0, 0.0, 0.0 };	// Green color diffuse light 
float difM[] = { 1.0, 0.0, 0.0 };	// Red color diffuse Material

boolean isOrtho = false;
bool isLightOn = false;				// is light off?
bool changeLightType = false;				// is light off?


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //Only call once when you press key
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		else if (wParam == 'Z') {
				if (rhead != 10)
				{
					rhead += rspeed;
				}
		}
		else if (wParam == 'X') {
				if (rhead != -10)
				{
					rhead -= rspeed;
				}
		}
		else if (wParam == 'C') {
				if (rhead1 != 10)
				{
					rhead1 += rspeed;
				}
		}
		else if (wParam == 'V') {
				if (rhead1 != -10)
				{
					rhead1 -= rspeed;
				}
		}
		else if (wParam == 'B') {
			if (tbody != 45) {
				tbody += rspeed;
			}
		}
		else if (wParam == 'N') {
				if (tbody != -45) {
					tbody -= rspeed;
				}
		}
		else if (wParam == 'Q') {
				rShoulderLeft += rspeed;
		}
		else if (wParam == 'A') {
				rShoulderLeft -= rspeed;
		}
		else if (wParam == 'W') {
				rLowerLimb += rspeed;	
		}
		else if (wParam == 'S') {
				rLowerLimb -= rspeed;	
		}
		else if (wParam == 'E') {
				rShoulderRight -= rspeed;
		}
		else if (wParam == 'D') {
				rShoulderRight += rspeed;
		}
		else if (wParam == 'R') {
				//rLowerLimb += rspeed;	
				rLowerLimb1 += rspeed;	
		}
		else if (wParam == 'F') {
				//rLowerLimb -= rspeed;	
				rLowerLimb1 -= rspeed;	
		}
		else if (wParam == 'T') {
				rLeg += rspeed;	// change
		}
		else if (wParam == 'G') {
				rLeg -= rspeed;	// change
		}
		else if (wParam == 'Y') {
				rLowerLeg += rspeed; // change
		}
		else if (wParam == 'H') {
				rLowerLeg -= rspeed; // change
		}
		else if (wParam == 'U') {
			rLeg1 += rspeed;	// change
		}
		else if (wParam == 'J') {
			rLeg1 -= rspeed;	// change
		}
		else if (wParam == 'I') {
			rLowerLeg1 += rspeed; // change
		}
		else if (wParam == 'K') {
			rLowerLeg1 -= rspeed; // change
		}
		else if (wParam == 0x70 ) {
				a = 0.0; 
		}
		else if (wParam == 0x71 ) {
				c = 0.0;
		}
		else if (wParam == 0x72) {
				d = 0.0;
		}
		else if (wParam == 0x73) {
				f = 0.0;
		}
		else if (wParam == 0x30) {
			 f = 1.0;
			 c = 1.0;
			 a = 1.0;
			 d = 1.0;
		}
		else if (wParam == 0x31) {
			option = 1;
		}
		else if (wParam == 0x32) {
			option = 2;
		}
		else if (wParam == 0x33) {
			option = 3;
		}
		else if (wParam == 0x34) {
			option = 4;
		}
		else if (wParam == 0x35) {
			option = 5;
		}
		else if (wParam == 0x36) {
			option = 6;	
		}
		else if (wParam == 0x37) {
			option = 7;
		}
		else if (wParam == 0x38) {
			shoot = 0.0;
		}
		else if (wParam == 0x74) {
			pr += prspeed;
		}
		else if (wParam == 0x75) {
			pr -= prspeed;
		}
		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = 0.2;
		}
		else if (wParam == VK_UP) {
			if (ty >= -0.6) {
				ty -= tspeed;
			}
		}
		
		else if (wParam == VK_DOWN) {
			if (ty <= 0.6) {
				ty += tspeed;
			}
		}
		else if (wParam == VK_LEFT) {
			if (tx1 <= 1.0) {
					tx1 += tspeed;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (tx1 >= -1.0) {
					tx1 -= tspeed;
			}
		}
		else if (wParam == VK_PRIOR) {
			if (tz >= -0.4) {
				tz -= tspeed;
			}
		}
		else if (wParam == VK_NEXT) {
			if (tz <= 0.4) {
				tz += tspeed;
			}
		}
		else if (wParam == VK_SPACE) {
			isLightOn = !isLightOn;
		}
		else if (wParam == 0x78) {
			changeLightType = !changeLightType;
		}
		else if (wParam == 0x76) {
			b = 0.0;
		}
		else if (wParam == 0x77) {
			b = 1.0;
		}
		else if (wParam == 0x39) {
			option = 9;
		}
		else if (wParam == 'L') {
			rShoulderLeft = 0.0, rShoulderRight = 0.0, rLeg = 0.0, rLeg1 = 0.0;
			zSword = 0.0, zShoulderRight = 0.0;
			rLowerLimb = 0.0;
			rLowerLimb1 = 0.0;
			rLowerLeg = 0.0;
			rLowerLeg1 = 0.0;
			tbody = 0.0;
			rhead = 0.0;
			rhead1 = 0.0;
			waiting = 0;
			temp1 = 1;
			temp2 = 0;
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

void drawCube0(float sz) {
	glBegin(GL_QUADS);
	//Face 1 => Bottom
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Face 2 => Left
	glVertex3f(0.0f, 0.0f, 0.0f);	//Last point of face 1
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);
	//Face 3 => Front
	glVertex3f(0.0f, 0.0f, sz);	//Last point of Face 2
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);
	//Face 4 => Right
	glVertex3f(sz, 0.0f, sz);	//Last point of Face 3
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);
	//Face 5 => Back
	glVertex3f(sz, 0.0f, 0.0f);	//Last point of Face 4
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	//Face 6 => Top
	glVertex3f(sz, sz, 0.0f);	//Last point of Face 5
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();
}

void drawCube01(float sz) {
	glBegin(GL_QUADS);
	//Face 1 => Bottom

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Face 2 => Left
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);	//Last point of face 1
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	//Face 3 => Front
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);	//Last point of Face 2
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, sz);
	//Face 4 => Right
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);	//Last point of Face 3
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, sz, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	//Face 5 => Back
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);	//Last point of Face 4
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, 0.0f);
	//Face 6 => Top
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, 0.0f);	//Last point of Face 5
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, sz);
	glEnd();
}

void drawCube02(float sz) {
	glBegin(GL_QUADS);
	//Face 1 => Bottom

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Face 2 => Left
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);	//Last point of face 1
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	//Face 3 => Front
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);	//Last point of Face 2
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, sz);
	//Face 4 => Right
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);	//Last point of Face 3
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, sz, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);
	//Face 5 => Back
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);	//Last point of Face 4
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, 0.0f);
	//Face 6 => Top
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, 0.0f);	//Last point of Face 5
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, sz);
	glEnd();
}

void drawCubeFrame0(float sz) {
	glBegin(GL_LINE_LOOP);
	//Face 1 => Bottom
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	//Face 2 => Left
	glVertex3f(0.0f, 0.0f, 0.0f);	//Last point of face 1
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);
	//Face 3 => Front
	glVertex3f(0.0f, 0.0f, sz);	//Last point of Face 2
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);
	//Face 4 => Right
	glVertex3f(sz, 0.0f, sz);	//Last point of Face 3
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);
	//Face 5 => Back
	glVertex3f(sz, 0.0f, 0.0f);	//Last point of Face 4
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	//Face 6 => Top
	glVertex3f(sz, sz, 0.0f);	//Last point of Face 5
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();
}

void pyramidFrame0(float sc) {

	glLineWidth(0.4);
	glBegin(GL_LINE_LOOP);
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

void pyramid0(float sc) {

	glBegin(GL_QUADS);
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

void drawSphere0(float r, float slice, float stack) {
	GLUquadricObj* sphere = NULL;	//Create quadric object pointer
	sphere = gluNewQuadric();		//Create the quadric object
	gluQuadricDrawStyle(sphere, GLU_FILL);	//Set the draw style
	gluSphere(sphere, r, slice, stack);	//Draw sphere
	gluDeleteQuadric(sphere);
}

void drawSphereFrame0(float r, float slice, float stack) {
	GLUquadricObj* sphere = NULL;	//Create quadric object pointer
	sphere = gluNewQuadric();		//Create the quadric object
	gluQuadricDrawStyle(sphere, GLU_SILHOUETTE);	//Set the draw style
	gluSphere(sphere, r, slice, stack);	//Draw sphere
	gluDeleteQuadric(sphere);
}

void drawCylinder0(float tr, float br, float h, float slice, float stack) {

	GLUquadricObj* cylinder = NULL;					//Create quadric object pointer
	cylinder = gluNewQuadric();						//Create the quadric object
	gluQuadricDrawStyle(cylinder, GLU_FILL);		//Set the draw style
	gluCylinder(cylinder, tr, br, h, slice, stack);	//Draw cylinder
	gluDeleteQuadric(cylinder);

}

void drawCylinderFrame0(float tr, float br, float h, float slice, float stack) {

	GLUquadricObj* cylinder = NULL;					//Create quadric object pointer
	cylinder = gluNewQuadric();						//Create the quadric object
	gluQuadricDrawStyle(cylinder, GLU_SILHOUETTE);		//Set the draw style
	gluCylinder(cylinder, tr, br, h, slice, stack);	//Draw cylinder
	gluDeleteQuadric(cylinder);

}

void drawCone0(float r, float h, float slice, float stack) {

	GLUquadricObj* cylinder = NULL;					//Create quadric object pointer
	cylinder = gluNewQuadric();						//Create the quadric object
	gluQuadricDrawStyle(cylinder, GLU_FILL);		//Set the draw style
	gluCylinder(cylinder, 0.0, r, h, slice, stack);	//Draw cone
	gluDeleteQuadric(cylinder);

}

void drawConeFrame0(float r, float h, float slice, float stack) {

	GLUquadricObj* cylinder = NULL;					//Create quadric object pointer
	cylinder = gluNewQuadric();						//Create the quadric object
	gluQuadricDrawStyle(cylinder, GLU_POINT);		//Set the draw style
	gluCylinder(cylinder, 0.0, r, h, slice, stack);	//Draw cone
	gluDeleteQuadric(cylinder);

}

void drawConeFrame(float r, float h, float slice, float stack) {

	GLUquadricObj* cylinder = NULL;					//Create quadric object pointer
	cylinder = gluNewQuadric();						//Create the quadric object
	gluQuadricDrawStyle(cylinder, GLU_LINE);		//Set the draw style
	gluCylinder(cylinder, 0.0, r, h, slice, stack);	//Draw cone
	gluDeleteQuadric(cylinder);

}

void rectangle() {

	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.5f);
	glVertex3f(-0.9f, 0.0f, 0.5f);
	glVertex3f(-0.9f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(0.0f, 0.0f, 0.5f);

	glVertex3f(0.0f, 0.0f, 0.5f);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.9f, 0.5f, 0.5f);
	glVertex3f(-0.9f, 0.0f, 0.5f);

	glVertex3f(-0.9f, 0.0f, 0.5f);
	glVertex3f(-0.9f, 0.5f, 0.5f);
	glVertex3f(-0.9f, 0.5f, 0.0f);
	glVertex3f(-0.9f, 0.0f, 0.0f);

	glVertex3f(-0.9f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.9f, 0.5f, 0.0f);

	glVertex3f(-0.9f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.9f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();

}

void rectangle1() {

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.9f, 0.0f, 0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.9f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.5f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.9f, 0.5f, 0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.9f, 0.0f, 0.5f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.9f, 0.0f, 0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.9f, 0.5f, 0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.9f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.9f, 0.0f, 0.0f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.9f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.9f, 0.5f, 0.0f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.9f, 0.5f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.9f, 0.5f, 0.5f);

	glEnd();
	glPopMatrix();

}

void drawCube(float sc) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.01, 1.0, 1.0, 1.0);
	/*glScalef(0.5, 0.5, 0.5);*/
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sc); // face 1 (bottom)
	glVertex3f(sc, 0.0f, sc);
	glVertex3f(sc, 0.0f, sc);
	glVertex3f(0.0f, 0.0f, 0.0f); //origin

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 2 (Left)
	glVertex3f(0.0f, sc, 0.0f);
	glVertex3f(0.0f, sc, sc);
	glVertex3f(0.0f, 0.0f, sc); //origin

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sc); // face 3 (front)
	glVertex3f(0.0f, sc, sc);
	glVertex3f(sc, sc, sc);
	glVertex3f(sc, 0.0f, sc); //origin

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(sc, 0.0f, sc); // face 4 (right)
	glVertex3f(sc, sc, sc);
	glVertex3f(sc, sc, 0.0f);
	glVertex3f(sc, 0.0f, 0.0f); //origin

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(sc, 0.0f, 0.0f); // face 5 (back)
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sc, 0.0f);
	glVertex3f(sc, sc, 0.0f); //origin

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(sc, sc, 0.0f); // face 6 (top)
	glVertex3f(0.0f, sc, 0.0f);
	glVertex3f(0.0f, sc, sc);
	glVertex3f(sc, sc, sc); //origin
	glEnd();
}

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
	gluQuadricTexture(cylinder, true);
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
	/*glRotatef(pr, 0.0, 1.0, 0.0);*/
	glRotatef(180, 0.0, 1.0, 0.0);
	if (isOrtho) {
		glOrtho(-4.0, 4.0, -4.0, 4.0, oNear, oFar);
	}
	else {
		gluPerspective(20.0, 1.0, -1.0, 1.0);
		glFrustum(-4.0, 4.0, -4.0, 4.0, pNear, pFar);
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

void background(float size) {

	/*glDisable(GL_LIGHTING);*/
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	GLuint textureArr[6];
	glColor3f(1.0, 1.0, 1.0);
	textureArr[1] = loadTexture("Back.bmp");
	/*textureArr[1] = loadTexture("concrete.bmp");*/
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(size / 2, size / 2, size / 2); // back
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(size / 2, -size / 2, size / 2);

	glEnd();
	glDeleteTextures(1, &textureArr[1]);


	textureArr[0] = loadTexture("Left.bmp");
	/*textureArr[0] = loadTexture("concrete.bmp");*/
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-size / 2, size / 2, size / 2); // left
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-size / 2, -size / 2, size / 2);

	glEnd();
	glDeleteTextures(1, &textureArr[0]);

	textureArr[3] = loadTexture("Front.bmp");
	/*textureArr[3] = loadTexture("concrete.bmp");*/
	glBegin(GL_QUADS);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(size / 2, size / 2, -size / 2); // Front
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(size / 2, -size / 2, -size / 2);

	glEnd();
	glDeleteTextures(1, &textureArr[3]);

	textureArr[2] = loadTexture("Right.bmp");
	/*textureArr[2] = loadTexture("concrete.bmp");*/
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(size / 2, size / 2, -size / 2); // right
	glTexCoord2f(1.0, 1.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(size / 2, -size / 2, -size / 2);

	glEnd();
	glDeleteTextures(1, &textureArr[2]);

	textureArr[4] = loadTexture("Top.bmp");
	/*textureArr[4] = loadTexture("concrete.bmp");*/
	glBegin(GL_QUADS);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(size / 2, size / 2, size / 2); // top
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(size / 2, size / 2, -size / 2);

	glEnd();
	glDeleteTextures(1, &textureArr[4]);

	textureArr[5] = loadTexture("Bottom.bmp");
	/*textureArr[5] = loadTexture("concrete.bmp");*/
	glBegin(GL_QUADS);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(size / 2, -size / 2, size / 2); // bottom
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(size / 2, -size / 2, -size / 2);

	glEnd();
	glDeleteTextures(1, &textureArr[5]);

	/*glEnable(GL_LIGHTING);*/
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void drawShoulderRec() {   // Shoulder rectangle

	glBegin(GL_QUADS);
	/*glColor3f(1.0, 0.0, 0.0);*/
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 1 (bottom)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.25f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.25f); // face 2 (front)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.25f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.25f); // face 3 (right)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.0f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.0f); // face 4 (back)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 5 (left)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.0f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.0f); // face 6 (top)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.0f); //origin

	glEnd();
}

void drawLegRec() {   // Shoulder rectangle

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

void drawLegRec1() {   // Shoulder rectangle

	glBegin(GL_QUADS);
	/*glColor3f(1.0, 0.0, 0.0);*/
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 1 (bottom)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.25f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.25f); // face 2 (front)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.25f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.25f); // face 3 (right)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.0f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.0f); // face 4 (back)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 5 (left)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.0f); //origin

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.0f); // face 6 (top)
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.25f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.25f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1f, 0.3f, 0.0f); //origin

	glEnd();
}

void drawHalfRec() {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // face 1 bottom
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.2f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.2f); // face 2 back
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.2f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.2f); // face 3 right
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.2f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.2f); // face 4 front
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.3f, 0.0f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.3f, 0.0f); // face 5 left
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
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

	glRotatef(rShoulderLeft, 1.0, 0.0, 0.0);

	if (b == 1.0) {
		glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawCylinder(0.1, 0.1, 0.1); // Shoulder Cylinder
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];

		glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		textureArr1[0] = loadTexture("Rust.bmp");
		drawCylinder(0.1, 0.1, 0.1); // Shoulder Cylinder
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(-0.04, -0.15, -0.125);
		glRotatef(16, 0.0, 0.0, 1.0);
		glColor3f(0.2, 0.2, 0.2);
		drawShoulderRec(); // Shoulder rectangle
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];

		glPushMatrix();
		glTranslatef(-0.04, -0.15, -0.125);
		glRotatef(16, 0.0, 0.0, 1.0);
		textureArr1[0] = loadTexture("BlackLeather.bmp");
		drawShoulderRec(); // Shoulder rectangle
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
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
	}
	else if (b == 0.0) {

		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();
		glTranslatef(-0.12, -0.16, -0.1);
		textureArr1[0] = loadTexture("Lava.bmp");
		drawHalfRec();
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.08, -0.32, 0.1);
		glRotatef(180, 0.0, 1.0, 0.0);
		textureArr1[1] = loadTexture("Lava.bmp");
		drawHalfRec();
		glDeleteTextures(1, &textureArr1[1]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(-0.04, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawCylinder(0.05, 0.05, 0.2); // upper Limp mini cylinder
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();
		glTranslatef(-0.04, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		textureArr1[0] = loadTexture("Rust.bmp");
		drawCylinder(0.05, 0.05, 0.2); // upper Limp mini cylinder
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

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

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawCylinder(0.05, 0.05, 0.25); //Lower Limb Cylinder (Middle)
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		textureArr1[0] = loadTexture("Lava.bmp");
		drawCylinder(0.05, 0.05, 0.25); //Lower Limb Cylinder (Middle)
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

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
	glTranslatef(0.0, -0.43, -0.025); // move Hand and fingers to right location
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

	glRotatef(rShoulderRight, 1.0, 0.0, 0.0);

	if (b == 1.0) {
		glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawCylinder(0.1, 0.1, 0.1); // Shoulder Cylinder
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		textureArr1[0] = loadTexture("Rust.bmp");
		drawCylinder(0.1, 0.1, 0.1); // Shoulder Cylinder
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(-0.04, -0.15, -0.125);
		glRotatef(16, 0.0, 0.0, 1.0);
		glColor3f(0.2, 0.2, 0.2);
		drawShoulderRec(); // Shoulder rectangle
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];

		glPushMatrix();
		glTranslatef(-0.04, -0.15, -0.125);
		glRotatef(16, 0.0, 0.0, 1.0);
		textureArr1[0] = loadTexture("BlackLeather.bmp");
		drawShoulderRec(); // Shoulder rectangle
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
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
	}
	else if (b == 0.0) {

		GLuint textureArr1[2];


		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.12, -0.16, -0.1);
		textureArr1[0] = loadTexture("Lava.bmp");
		drawHalfRec();
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.08, -0.32, 0.1);
		glRotatef(180, 0.0, 1.0, 0.0);
		textureArr1[1] = loadTexture("Lava.bmp");
		drawHalfRec();
		glDeleteTextures(1, &textureArr1[1]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(-0.04, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(0.6, 0.6, 0.6);
		drawCylinder(0.05, 0.05, 0.2); // upper Limp mini cylinder
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();
		glTranslatef(-0.04, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		textureArr1[0] = loadTexture("Rust.bmp");
		drawCylinder(0.05, 0.05, 0.2); // upper Limp mini cylinder
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

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
	glRotatef(-rLowerLimb1, 1.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawCylinder(0.02, 0.04, 0.1); //lower Limb Cylinder (Upper)
	glPopMatrix();
	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawCylinder(0.05, 0.05, 0.25); //Lower Limb Cylinder (Middle)
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		textureArr1[0] = loadTexture("Lava.bmp");
		drawCylinder(0.05, 0.05, 0.25); //Lower Limb Cylinder (Middle)
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}
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
	glTranslatef(-0.01, -0.43, 0.025); // move Hand and fingers to right location
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
	glRotatef(-35, 0.0, 0.0, 1.0);
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

void Weapon()
{
	glPushMatrix();
	glTranslatef(0.38, 0.15, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.5);
	glTranslatef(0.1, 0.1, 0.3);
	glScalef(0.5, 0.5, 0.9);
	glColor3f(0.0, 0.0, 1.0);
	drawCube0(0.6);
	glTranslatef(-0.09, -0.1, 0.4);
	glScalef(1.0, 2.5, 0.5);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.8);
	glTranslatef(0.4, 0.01, 0.4);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCone0(0.3, 0.8, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.87, 0.3, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glTranslatef(-2.34, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.38, 0.15, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.5);
	glTranslatef(0.1, 0.1, 0.3);
	glScalef(0.5, 0.5, 0.9);
	glColor3f(0.0, 0.0, 1.0);
	drawCube0(0.6);
	glTranslatef(-0.09, -0.1, 0.4);
	glScalef(1.0, 2.5, 0.5);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.8);
	glTranslatef(0.35, 0.01, 0.4);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCone0(0.3, 0.8, 12, 12);
	glPopMatrix();
}

void lazer() {
	if (c >= 0.0) {
		glPushMatrix();
		glTranslatef(-0.185, 0.325, shoot);
		glColor3f(0.0, 1.0, 1.0);
		drawSphereCore(0.025, 20, 20);
		glPopMatrix();

		glPushMatrix();

		glTranslatef(0.19, 0.325, shoot);
		glColor3f(0.0, 1.0, 1.0);
		drawSphereCore(0.025, 20, 20);
		glPopMatrix();
	}
	else {

	}
}

void upWeapon()
{

	glPushMatrix();
	glTranslatef(0.38, 0.15, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.5);

	glTranslatef(0.15, 0.45, 0.1);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0.0, 0.0, 1.0);
	drawCube0(0.6);

	glTranslatef(-0.1, 0.35, -1.2);
	glScalef(1.0, 1.0, 2.5);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.8);

	glTranslatef(0.4, 0.41, 0.775);
	glRotatef(0, 0.0, 1.0, 0.0);
	glRotatef(-180, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCone0(0.3, 0.8, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.87, 0.3, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glTranslatef(-2.34, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.38, 0.15, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.5);

	glTranslatef(0.05, 0.45, 0.1);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0.0, 0.0, 1.0);
	drawCube0(0.6);

	glTranslatef(-0.11, 0.35, -1.3);
	glScalef(1.0, 1.0, 2.5);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.8);

	glTranslatef(0.385, 0.4, 0.775);
	glRotatef(0, 0.0, 1.0, 0.0);
	glRotatef(-180, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCone0(0.3, 0.8, 12, 12);
	glPopMatrix();
}

void drawPistol() {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);

	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0.412, 0.412, 0.412);
	glRotatef(180, 1.0, 0.0, 0.0);   //long gun tube
	drawCylinder(0.04, 0.04, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.09, 0.0);
	glColor3f(0.502, 0.502, 0.502);
	glRotatef(180, 1.0, 0.0, 0.0);   //short gun tube
	drawCylinder(0.04, 0.04, 0.3);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.6, 0.6);
	glTranslatef(-0.12, -0.22, 0.0);   //link gun tube
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.312, 0.312, 0.312);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.2, 2.0);
	glTranslatef(-0.12, -0.05, 0.10);   //bullet top
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.412, 0.412, 0.412);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.2, 2.0);
	glTranslatef(-0.12, -0.34, 0.10);   //bullet middle
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.502, 0.502, 0.502);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.2, 2.0);
	glTranslatef(-0.12, -0.65, 0.10);   //bullet bottom
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.663, 0.663, 0.663);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.6, 0.6);
	glTranslatef(-0.12, -0.22, 0.43);   //link bullet tube
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.312, 0.312, 0.312);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 1.2, 1.4);
	glTranslatef(-0.12, -0.26, 0.283);   //handle
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.252, 0.252, 0.252);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.095, 0.33);   //botton sphere
	drawSphere(0.04, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 1.4, 0.4);
	glTranslatef(0.10, 0.00, 0.85);
	glRotatef(270, 1.0, 0.0, 0.0);      //aimpoint
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.2, 0.4, 0.2);
	glTranslatef(0.10, 0.09, -2.7);
	glRotatef(270, 1.0, 0.0, 0.0);   //front aim
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.4, 0.4, 0.4);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.2, 0.4, 0.2);
	glTranslatef(0.10, 0.10, 1.9);
	glRotatef(90, 1.0, 0.0, 0.0);   //tail
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.212, 0.212, 0.212);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.3, 0.5, 0.3);
	glTranslatef(0.1, -0.25, 0.60);
	glRotatef(90, 1.0, 0.0, 0.0);   //fire 
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.212, 0.212, 0.212);
	drawHalfRec();
	glPopMatrix();

	glPopMatrix();


	glPopMatrix();

}

void head() {

	glPushMatrix();
	glRotatef(rhead, 1.0, 0.0, 0.0);
	glRotatef(rhead1, 0.0, 1.0, 0.0);

	glPushMatrix();						// eye 
	glTranslatef(0.15, 0.4, -0.02);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glTranslatef(0.3, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glPopMatrix();

	glPushMatrix();						// mouth
	glTranslatef(0.3, 0.2, -0.02);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glTranslatef(0.1, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glTranslatef(-0.2, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawCube0(0.1);
	glPopMatrix();

	glPushMatrix();						// black face
	glTranslatef(0.1, 0.15, -0.01);
	glColor3f(0.0, 0.0, 0.0);
	drawCube0(0.5);
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();						// head
		glTranslatef(0.0, 0.1, 0.0);
		glColor3f(1.0, 0.27, 0.0);
		drawCube0(0.7);
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// head
		glTranslatef(0.0, 0.1, 0.0);
		textureArr1[0] = loadTexture("Lava.bmp");
		drawCube01(0.7);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	glPushMatrix();						// head back 
	glTranslatef(0.1, 0.2, 0.25);
	glColor3f(1.0, 0.27, 0.0);
	drawCube0(0.5);
	glPopMatrix();

	glPushMatrix();						// head top
	glTranslatef(0.05, 0.22, 0.05);
	glColor3f(1.0, 0.27, 0.0);
	drawCube0(0.6);
	glPopMatrix();

	glPushMatrix();						// screw
	glTranslatef(0.6, 0.78, 0.58);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawSphere0(0.05, 30, 30);
	glPopMatrix();

	glPushMatrix();						// screw
	glTranslatef(0.6, 0.78, 0.1);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawSphere0(0.05, 30, 30);
	glPopMatrix();

	glPushMatrix();						// screw
	glTranslatef(0.1, 0.78, 0.1);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawSphere0(0.05, 30, 30);
	glPopMatrix();

	glPushMatrix();						// screw
	glTranslatef(0.1, 0.78, 0.58);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawSphere0(0.05, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();								// cylinder - yellow 
	glTranslatef(0.35, -0.2, 0.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	drawCylinder0(0.25, 0.25, 0.5, 30, 30);
	glPopMatrix();

	glPushMatrix();							// cylinder black
	glTranslatef(0.35, -0.15, 0.35);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawCylinder0(0.45, 0.4, 0.2, 30, 30);
	glPopMatrix();
}

void body() {
	glPushMatrix();
	glPushMatrix();						//body - square , cylinder, pyramid
	glTranslatef(0.03, -0.2, 0.051);
	glScalef(0.4, 0.9, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	rectangle();
	glTranslatef(0.25, 0.8, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	pyramid0(-0.8);
	glTranslatef(-0.4, -1.5, -0.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	drawCylinder0(0.1, 0.1, 0.8, 30, 30);
	glTranslatef(0.0, 0.0, 0.45);
	glColor3f(0.7, 0.7, 0.7);
	drawCylinder0(0.11, 0.11, 0.2, 30, 30);
	glTranslatef(0.0, 0.0, -0.55);
	glColor3f(0.7, 0.7, 0.7);
	drawCylinder0(0.11, 0.11, 0.2, 30, 30);
	glPopMatrix();

	glPushMatrix();						//body - top and second

	if (b == 1.0) {
		glTranslatef(0.53, 0.6, 0.0);
		glScalef(1.5, 0.395, 1.0);
		glColor3f(1.0, 0.27, 0.0);
		rectangle();
	}
	else if (b == 0.0) {
		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);        // leg shield small					
		glTranslatef(0.53, 0.6, 0.0);
		glScalef(1.5, 0.395, 1.0);
		glColor3f(1.0, 1.0, 0.0);

		textureArr1[0] = loadTexture("Lava.bmp");
		rectangle1();
		glDeleteTextures(1, &textureArr1[0]);
	}

	if (b == 1.0) {
		glTranslatef(0.48, 0.35, 0.0);
		glScalef(1.4, 0.5, 0.95);
		glColor3f(0.0, 0.74, 1.0);
		rectangle();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glTranslatef(0.48, 0.35, 0.0);
		glScalef(1.4, 0.5, 0.95);
		textureArr1[0] = loadTexture("Blue.bmp");
		rectangle1();
		glDeleteTextures(1, &textureArr1[0]);
	}
	/*glTranslatef(0.09, 0.03, 0.0);
	glScalef(0.3, 0.3, 0.3);
	glScalef(1.0, 0.5, 0.95);
	glColor3f(1.0, 0.27, 0.0);
	rectangle();*/
	glPopMatrix();

	glPopMatrix();
}

void leg() {
	glPushMatrix();
	if (b == 1.0) {

		glPushMatrix();						// top
		glTranslatef(0.15, -0.5, 0.0);
		glScalef(0.5, 0.2, 0.35);
		glColor3f(1.0, 0.27, 0.0);
		rectangle();
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// middle rectangle
		glTranslatef(0.15, -0.5, 0.0);
		glScalef(0.5, 0.2, 0.35);
		textureArr1[0] = loadTexture("Lava.bmp");
		rectangle1();
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();						// middle rectangle
		glTranslatef(-0.03, -0.58, -0.016);
		glScalef(0.1, 0.7, 0.1);
		glColor3f(0.0, 0.74, 1.0);
		rectangle();
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// middle rectangle
		glTranslatef(-0.03, -0.58, -0.016);
		glScalef(0.1, 0.7, 0.1);
		textureArr1[0] = loadTexture("Blue.bmp");
		rectangle1();
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	//glPushMatrix();						//- left big leg
	//glTranslatef(-0.25, -0.62, -0.05);
	//glScalef(0.1, 0.7, 0.5);
	//glColor3f(1.0, 0.27, 0.0);
	//rectangle();
	//glPopMatrix();

	//glPushMatrix();						//- right big leg
	//glTranslatef(0.17, -0.62, -0.05);
	//glScalef(0.1, 0.7, 0.5);
	//glColor3f(1.0, 0.27, 0.0);
	//rectangle();
	//glPopMatrix();

	//////////////////glPushMatrix();						// middle 
	//////////////////glTranslatef(0.1, -0.6, -0.015);
	//////////////////glScalef(0.4, 0.2, 0.4);
	//////////////////glColor3f(0.0, 0.0, 0.0);
	//////////////////rectangle();
	//////////////////glPopMatrix();

	//glPushMatrix();						// bottom 
	//glTranslatef(0.145, -0.45, 0.08);
	//glRotatef(90, 0.0, 1.0, 0.0);
	//glRotatef(0, 1.0, 0.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	//drawCone0(0.05, 0.0275, 12, 12);
	//glPopMatrix();drawLegRec();

	//glPushMatrix();						// bottom 
	//glTranslatef(-0.315, -0.45, 0.08);
	//glRotatef(90, 0.0, 1.0, 0.0);
	//glRotatef(180, 1.0, 0.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	//drawCone0(0.05, 0.0275, 12, 12);
	//glPopMatrix();
	glPopMatrix();
}

void drawRightLeg() {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);

	glRotatef(rLeg1, 1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(0.05, 0.0, 0.0);   //middle sphere 
	glColor3f(1.0, 0.27, 0.0);
	drawSphere(0.04, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	drawCylinder(0.1, 0.1, 0.1);  //linker for leg
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(-0.1, -0.15, -0.125);
		glColor3f(1.0, 0.27, 0.0);
		drawLegRec(); // big leg
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// middle rectangle
		glTranslatef(-0.1, -0.15, -0.125);
		textureArr1[0] = loadTexture("BlackLeather.bmp");
		drawLegRec1(); // big leg
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}


	glPushMatrix();						// cone light blue in big leg
	glTranslatef(-0.075, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCone0(0.05, 0.0275, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.05, 0.0, 0.0);  //bone inside thigh
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawCylinder(0.04, 0.04, 0.4);
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();						// leg shield big
		glTranslatef(-0.22, -0.8, -0.06);
		glColor3f(1.0, 0.27, 0.0);
		glScalef(1.6, 2.7, 0.1);
		drawCube0(0.2);
		glPopMatrix();
	}
	else if (b == 0.0) {

		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(-0.22, -0.8, -0.06);
		glColor3f(1.0, 0.27, 0.0);
		glScalef(1.6, 2.7, 0.1);

		textureArr1[0] = loadTexture("Lava.bmp");
		drawCube01(0.2);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();						// leg shield small
		glTranslatef(-0.13, -0.85, -0.07);
		glColor3f(1.0, 1.0, 0.0);
		glScalef(0.8, 3.4, 0.1);
		drawCube0(0.2);
		glPopMatrix();
	}
	else if (b == 0.0) {

		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(-0.13, -0.85, -0.07);
		glColor3f(1.0, 1.0, 0.0);
		glScalef(0.8, 3.4, 0.1);

		textureArr1[0] = loadTexture("Lava.bmp");
		drawCube01(0.2);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}


	glPushMatrix();						// shield linker 
	glTranslatef(-0.05, -0.7, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawSphere(0.05, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.05, -0.2, 0.0);   //middle sphere 
	glColor3f(1.0, 0.27, 0.0);
	drawSphere(0.05, 10, 10);
	glPopMatrix();


	glPushMatrix();

	glTranslatef(-0.05, -0.4, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);   //middle bone
	drawCylinder(0.04, 0.03, 0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(-0.05, -0.81, 0.0);  //botton sphere
	drawSphere(0.02, 10, 10);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.05, -0.82, 0.0);
	glRotatef(rLowerLeg1, 1.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);        //top calves
	drawCylinder(0.02, 0.05, 0.1);
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glColor3f(1.0, 0.27, 0.0);//main calves
		glRotatef(90, 1.0, 0.0, 0.0);
		drawCylinder(0.05, 0.02, 0.4);
		glPopMatrix();

	}
	else if (b == 0.0) {
		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(0.0, -0.1, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);

		textureArr1[0] = loadTexture("Lava.bmp");
		drawCylinder(0.05, 0.02, 0.4);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(0.0, -0.52, 0.0);  //sphere inside foot
	drawSphere(0.02, 10, 10);
	glPopMatrix();


	//foot

	glPushMatrix();

	glTranslatef(0.0, -0.52, 0.0);


	glPushMatrix();
	glScalef(0.4, 0.4, 0.6);
	glTranslatef(-0.13, -0.3, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);     //link foot
	glColor3f(0.2, 0.2, 0.2);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 1.5, 0.5);
	glTranslatef(-0.1, -0.135, 0.0);   //BACK FOOT
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.35, 1, 1);
	glTranslatef(-0.10, -0.15, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	glRotatef(270, 1.0, 0.0, 0.0);  //FROND LEFT FOOT
	glRotatef(270, 0.0, 1.0, 0.0);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.035, -0.2, 0.);
	glScalef(0.30, 0.5, 1.0);
	glRotatef(270, 1.0, 0.0, 0.0);   // LEFT OUTSOLE
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(-0.4, -0.5, -0.3);
	glRotatef(90, 0.0, 1.0, 0.0);     //UP LEFT LACE 
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(-0.4, -0.6, -0.7);
	glRotatef(90, 0.0, 1.0, 0.0);     //DOWN LEFT LACE
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.35, 1, 1);
	glTranslatef(0.28, -0.15, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	glRotatef(270, 1.0, 0.0, 0.0);  //FROND RIGHT FOOT
	glRotatef(270, 0.0, 1.0, 0.0);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.10, -0.2, 0.);
	glScalef(0.30, 0.5, 1.0);
	glRotatef(270, 1.0, 0.0, 0.0);   // RIGHT OUTSOLE
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(0.13, -0.5, -0.3);
	glRotatef(90, 0.0, 1.0, 0.0);     //UP RIGHT LACE 
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(0.13, -0.6, -0.7);
	glRotatef(90, 0.0, 1.0, 0.0);     //DOWN RIGHT LACE
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();


	glPopMatrix();

}

void drawLeftLeg() {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);

	glRotatef(rLeg, 1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(-0.13, 0.0, 0.0);   //middle sphere 
	glColor3f(1.0, 0.27, 0.0);
	drawSphere(0.04, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-0.30, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	drawCylinder(0.1, 0.1, 0.1);  //linker for leg
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(-0.1, -0.15, -0.125);
		glColor3f(1.0, 0.27, 0.0);
		drawLegRec(); // big leg
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[2];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// middle rectangle
		glTranslatef(-0.1, -0.15, -0.125);
		textureArr1[0] = loadTexture("BlackLeather.bmp");
		drawLegRec1(); // big leg
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	glPushMatrix();						// cone light blue in big leg
	glTranslatef(-0.025, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCone0(0.05, 0.0275, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.05, 0.0, 0.0);  //bone inside thigh
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawCylinder(0.04, 0.04, 0.4);
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();						// leg shield big
		glTranslatef(-0.22, -0.8, -0.06);
		glColor3f(1.0, 0.27, 0.0);
		glScalef(1.6, 2.7, 0.1);
		drawCube0(0.2);
		glPopMatrix();
	}
	else if (b == 0.0) {

		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(-0.22, -0.8, -0.06);
		glColor3f(1.0, 0.27, 0.0);
		glScalef(1.6, 2.7, 0.1);

		textureArr1[0] = loadTexture("Lava.bmp");
		drawCube02(0.2);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	if (b == 1.0) {
		glPushMatrix();						// leg shield small
		glTranslatef(-0.13, -0.85, -0.07);
		glColor3f(1.0, 1.0, 0.0);
		glScalef(0.8, 3.4, 0.1);
		drawCube0(0.2);
		glPopMatrix();
	}
	else if (b == 0.0) {

		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(-0.13, -0.85, -0.07);
		glColor3f(1.0, 1.0, 0.0);
		glScalef(0.8, 3.4, 0.1);

		textureArr1[0] = loadTexture("Lava.bmp");
		drawCube01(0.2);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	glPushMatrix();						// shield linker 
	glTranslatef(-0.05, -0.7, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawSphere(0.05, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.05, -0.2, 0.0);   //middle sphere 
	glColor3f(1.0, 0.27, 0.0);
	drawSphere(0.05, 10, 10);
	glPopMatrix();


	glPushMatrix();

	glTranslatef(-0.05, -0.4, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);   //middle bone
	drawCylinder(0.04, 0.03, 0.4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(-0.05, -0.81, 0.0);  //botton sphere
	drawSphere(0.02, 10, 10);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.05, -0.82, 0.0);
	glRotatef(rLowerLeg, 1.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);        //top calves
	drawCylinder(0.02, 0.05, 0.1);
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glColor3f(1.0, 0.27, 0.0);//main calves
		glRotatef(90, 1.0, 0.0, 0.0);
		drawCylinder(0.05, 0.02, 0.4);
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(0.0, -0.1, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);

		textureArr1[0] = loadTexture("Lava.bmp");
		drawCylinder(0.05, 0.02, 0.4);
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(0.0, -0.52, 0.0);  //sphere inside foot
	drawSphere(0.02, 10, 10);
	glPopMatrix();


	//foot

	glPushMatrix();

	glTranslatef(0.0, -0.52, 0.0);


	glPushMatrix();
	glScalef(0.4, 0.4, 0.6);
	glTranslatef(-0.13, -0.3, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);     //link foot
	glColor3f(0.2, 0.2, 0.2);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 1.5, 0.5);
	glTranslatef(-0.1, -0.135, 0.0);   //BACK FOOT
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.35, 1, 1);
	glTranslatef(-0.10, -0.15, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	glRotatef(270, 1.0, 0.0, 0.0);  //FROND LEFT FOOT
	glRotatef(270, 0.0, 1.0, 0.0);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.035, -0.2, 0.);
	glScalef(0.30, 0.5, 1.0);
	glRotatef(270, 1.0, 0.0, 0.0);   // LEFT OUTSOLE
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(-0.4, -0.5, -0.3);
	glRotatef(90, 0.0, 1.0, 0.0);     //UP LEFT LACE 
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(-0.4, -0.6, -0.7);
	glRotatef(90, 0.0, 1.0, 0.0);     //DOWN LEFT LACE
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.35, 1, 1);
	glTranslatef(0.28, -0.15, 0.0);
	glColor3f(1.0, 0.27, 0.0);
	glRotatef(270, 1.0, 0.0, 0.0);  //FROND RIGHT FOOT
	glRotatef(270, 0.0, 1.0, 0.0);
	drawHalfRec();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.10, -0.2, 0.);
	glScalef(0.30, 0.5, 1.0);
	glRotatef(270, 1.0, 0.0, 0.0);   // RIGHT OUTSOLE
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(0.13, -0.5, -0.3);
	glRotatef(90, 0.0, 1.0, 0.0);     //UP RIGHT LACE 
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.3, 0.3);
	glTranslatef(0.13, -0.6, -0.7);
	glRotatef(90, 0.0, 1.0, 0.0);     //DOWN RIGHT LACE
	glColor3f(0.5, 0.5, 0.5);
	drawLegRec();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();


	glPopMatrix();

}

void shield() {
	glPushMatrix();								// shield
	glPointSize(8.0);
	glTranslatef(0.0, 0.0, -0.85);			//-1.07
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawConeFrame0(0.75, 0.25, 20, 10);
	glPopMatrix();

	glPushMatrix();								// shield
	glPointSize(8.0);
	glTranslatef(0.0, 0.0, 0.0);			//-1.07
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.74, 1.0);
	drawConeFrame0(0.1, 0.8, 10, 5);
	glPopMatrix();

}

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);		// Enable the lighting
	}
	else if (changeLightType) {
		glEnable(GL_LIGHTING);		// Enable the lighting
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glEnable(GL_LIGHT0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);	//red color dif mat
	}
	else
		glDisable(GL_LIGHTING);		// Disable the lighting
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (isOrtho) {
		glPushMatrix();
		glRotatef(180, 0.0, 1.0, 0.0);
		background(8.0);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glRotatef(180, 0.0, 1.0, 0.0);
		background(4.0);
		glPopMatrix();
	}


	lighting();
	/*glRotatef(0.01, 0.0, 1.0, 0.0);*/
	projection();
	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();   // animation Switch
	if (option == 1) {

			if (rhead != 4 && temp == 1)
			{
				rhead += rspeed;
				if (rhead == 4) {
					temp = 0;
				}
			}
			if (rhead != -10 && temp == 0) {
				rhead -= rspeed;

				if (rhead == -10) {
					temp = 1;
				}
		}
	
	}
	if (option == 2) {

		if (rhead1 != 10 && temp == 1)
		{
			rhead1 += rspeed;
			if (rhead1 == 10) {
				temp = 0;
			}
		}
		if (rhead1 != -10 && temp == 0) {
			rhead1 -= rspeed;

			if (rhead1 == -10) {
				temp = 1;
			}
		}

	}
	if (option == 3) {
		rLowerLimb = 20.0;
		rLowerLimb1 = 20.0;
		rLowerLeg = -20;
		rLowerLeg1 = -20;

		if (rShoulderLeft != 30 && temp == 1) {
			rShoulderLeft += rspeed;
			rShoulderRight += rspeed;
			rLeg += rspeed;
			rLeg1 -= rspeed;
			if (rShoulderLeft == 30) {
				temp = 0;
			}
		}

		if (rShoulderLeft != -30 && temp == 0) {
			rShoulderLeft -= rspeed;
			rShoulderRight -= rspeed;
			rLeg -= rspeed;
			rLeg1 += rspeed;
			if (rShoulderLeft == -30) {
				temp = 1;
			}
		}
	}
	else if (option == 4) {
		rLowerLimb = 30;
		rLowerLimb1 = 30;
		rLowerLeg = -50;
		rLowerLeg1 = -50;

		if (rShoulderLeft != 70 && temp == 1) {
			rShoulderLeft += rspeed1;
			rShoulderRight += rspeed1;
			rLeg += rspeed1;
			rLeg1 -= rspeed1;

			if (rShoulderLeft == 70) {
				temp = 0;
			}
		}

		if (rShoulderLeft != -70 && temp == 0) {
			rShoulderLeft -= rspeed1;
			rShoulderRight -= rspeed1;
			rLeg -= rspeed1;
			rLeg1 += rspeed1;

			if (rShoulderLeft == -70) {
				temp = 1;
			}
		}
	}
	else if (option == 5) {

		a = 0.0;

		if (rShoulderRight != -135 && temp1 == 1) {
			rShoulderRight -= rspeed * 3;
			zShoulderRight -= rspeed * 1.5;
			zSword -= zSpeed * 5;

			if (rShoulderRight <= -135) {
				temp1 = 0;
			}
		}

		if (rShoulderRight != 0 && temp1 == 0) {
			rShoulderRight += rspeed * 10;
			zShoulderRight += rspeed * 5.0;

			zSword += zSpeed * 16.5;

			if (rShoulderRight >= 0) {
				temp1 = 1;
			}
		}
	}
	else if (option == 6) {
		if (rShoulderLeft != 90 && temp2 == 0) {
			rShoulderLeft += rspeed;

			if (rShoulderLeft >= 90) {
				temp2 = 1;
			}
		}

		if (waiting != 30 && temp2 == 1) {
			waiting++;
			f = 0.0;

			if (waiting == 30) {
				temp2 = 2;
			}
		}

		if (temp2 == 2) {
			f = 1.0;
			temp2 = 3;
			waiting = 0;
		}

		if (rShoulderLeft != 0 && temp2 == 3) {
			rShoulderLeft -= rspeed;

			if (rShoulderLeft <= 0) {
				temp2 = 0;
			}
		}
	}
	else if (option == 7) {
			c = 0.0;
			if (shoot != -100 && temp == 1)
			{
				shoot -= sspeed;
				if (shoot == -100) {
					temp = 0;
				}
			}
	}
	else if (option == 9){
		rShoulderLeft = 0.0, rShoulderRight = 0.0, rLeg = 0.0, rLeg1 = 0.0;
		zSword = 0.0, zShoulderRight = 0.0;
		rLowerLimb = 0.0;
		rLowerLimb1 = 0.0;
		rLowerLeg = 0.0;
		rLowerLeg1 = 0.0;
		tbody = 0.0;
		rhead = 0.0;
		rhead1 = 0.0;
		shoot = 0.0;
		waiting = 0;
		temp1 = 1;
		temp2 = 0;

	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(tbody, 0.0, 1.0, 0.0);
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(-0.1, 0.3, 0.0);
	glScalef(0.3, 0.3, 0.3);
	head();                         // head
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(tbody, 0.0, 1.0, 0.0);
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(0.05, 0.015, 0.0);
	glScalef(0.3, 0.3, 0.3);
	body();                  // body
	glPopMatrix();

	if (b == 1.0) {
		glPushMatrix();						//body - last 
		glTranslatef(0.0, 0.0, tz);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glRotatef(pr, 0.0, 1.0, 0.0);
		glTranslatef(0.14, 0.045, 0.0);
		glScalef(0.3, 0.3, 0.3);
		glScalef(1.0, 0.5, 0.95);
		glColor3f(1.0, 0.27, 0.0);
		rectangle();
		glPopMatrix();
	}
	else if (b == 0.0) {
		GLuint textureArr1[1];
		glColor3f(1.0, 1.0, 1.0);

		glPushMatrix();						// leg shield small
		glTranslatef(0.0, 0.0, tz);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glRotatef(pr, 0.0, 1.0, 0.0);
		glTranslatef(0.14, 0.045, 0.0);
		glScalef(0.3, 0.3, 0.3);
		glScalef(1.0, 0.5, 0.95);

		textureArr1[0] = loadTexture("Lava.bmp");
		rectangle1();
		glDeleteTextures(1, &textureArr1[0]);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(0.05, 0.05, 0.0);
	glScalef(0.6, 0.6, 0.6);
	leg();
	glPopMatrix();

	glPushMatrix();						// middle 
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.05, 0.0);
	glTranslatef(0.11, -0.36, 0.0);
	glScalef(0.6, 0.6, 0.6);
	glScalef(0.4, 0.2, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	rectangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(tbody, 0.0, 1.0, 0.0);
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(-0.24, 0.02, 0.05);
	glScalef(0.6, 0.6, 0.6);
	drawLeftArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(tbody, 0.0, 1.0, 0.0);
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(0.247, 0.02, 0.05);
	glScalef(0.6, 0.6, 0.6);
	drawRightArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);
	/*glRotatef(180, 0.0, 1.0, 0.0);*/
	glRotatef(pr, 0.0, 1.0, 0.0);
	glTranslatef(0.20, -0.45, 0.05);         //leftleg
	glScalef(0.6, 0.6, 0.6);
	drawLeftLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, tz);              //rightleg
	glRotatef(pr, 0.0, 1.0, 0.0);
	//glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(-0.13, -0.45, 0.05);
	glScalef(0.6, 0.6, 0.6);
	drawRightLeg();
	glPopMatrix();

	if (c >= 1.0) {
		glPushMatrix();						// weapon
		glTranslatef(0.0, 0.0, tz);
		glRotatef(pr, 0.0, 1.0, 0.0);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glScalef(0.2, 0.2, 0.2);
		glTranslatef(0.275, 0.65, 0.27);
		Weapon();
		glPopMatrix();
	}
	else if (c >= 0.0) {
		glPushMatrix();						// up weapon
		glTranslatef(0.0, 0.0, tz);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glRotatef(pr, 0.0, 1.0, 0.0);
		glScalef(0.2, 0.2, 0.2);
		glTranslatef(0.275, 0.65, 0.27);
		upWeapon();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, tz);
		glRotatef(pr, 0.0, 1.0, 0.0);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		lazer();
		glPopMatrix();
	}
	else {
		glPushMatrix();						// weapon
		glTranslatef(0.0, 0.0, tz);
		glRotatef(pr, 0.0, 1.0, 0.0);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glScalef(0.2, 0.2, 0.2);
		glTranslatef(0.275, 0.65, 0.27);
		Weapon();
		glPopMatrix();
	}

	if (f >= 1.0) {

	}
	else if (f >= 0.0) {
		glPushMatrix();						// up shield
		glTranslatef(0.0, 0.0, tz);
		glRotatef(pr, 0.0, 1.0, 0.0);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glScalef(0.8, 0.8, 0.8);
		glTranslatef(-0.38, 0.25, -0.6);
		shield();
		glPopMatrix();
	}
	else {

	}

	if (a == 1.0) {

	}
	else if (a == 0.0) {

		glPushMatrix();
		glTranslatef(0.0, 0.0, tz);
		glRotatef(pr, 0.0, 1.0, 0.0);
		/*glRotatef(180, 0.0, 1.0, 0.0);*/
		glTranslatef(0.3, -0.4, 0.1);
		glRotatef(-zShoulderRight, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, zSword);
		glRotatef(-90, 1.0, 0.0, 0.0);
		glRotatef(-90, 0.0, 1.0, 0.0);

		drawSword();                              // draw sword
		glPopMatrix();
	}
	if (d == 1.0) {

	}
	else if (d == 0.0) {

		glPushMatrix();
		glTranslatef(0.0, 0.0, tz);
		glRotatef(pr, 0.0, 1.0, 0.0);
		glRotatef(tbody, 0.0, 1.0, 0.0);
		glScalef(0.3, 0.3, 0.3);
		glTranslatef(0.95, -1.6, 0.3);      //draw pistol
		glRotatef(270, 1.0, 0.0, 0.0);

		drawPistol();
		glPopMatrix();
	}

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
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
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