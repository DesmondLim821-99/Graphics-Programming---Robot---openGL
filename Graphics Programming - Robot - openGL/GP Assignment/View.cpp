
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
float tx1 = 0.0;
int qno = 0;
float rx = 0.0, rspeed = 0.01;
float tx = 0.0, ty = 0.0;
float tz = 0.0, tspeed = 1.0;
float oNear = -10.0, oFar = 10.0;
float pNear = 1.0, pFar = 21.0;
float ptx = 0.0, pty = 0.0, ptspeed = 0.5;
float pr = 0.0, prspeed = 1.0;
float rs1 = 1.0;

boolean isOrtho = true;

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
			if (tz > oNear + rs1) {
				tz -= tspeed;
			}
			else {
				if (tz > pNear + rs1) {
					tz -= tspeed;
				}
			}
		}
		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (tz < oFar - rs1) {
					tz += tspeed;
				}
				else {
					if ((tz < pFar - rs1) / 2) {
						tz += tspeed;
					}
				}
			}
		}
		else if (wParam == VK_LEFT) {
			tx1 -= tspeed;
		}
		else if (wParam == VK_RIGHT) {
			tx1 += tspeed;
		}
		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = pNear + rs1;
		}
		else if (wParam == 'A') {
			ptx -= ptspeed;
		}
		else if (wParam == 'D') {
			ptx += ptspeed;
		}
		else if (wParam == 'W') {
			pty += ptspeed;
		}
		else if (wParam == 'S') {
			pty -= ptspeed;
		}
		else if (wParam == 'L') {
			pr += prspeed;
		}
		else if (wParam == 'R') {
			pr -= prspeed;
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

void drawCube(float sc) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.01, 1.0, 1.0, 1.0);
	/*glScalef(0.5, 0.5, 0.5);*/
	glBegin(GL_QUADS);
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
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, r, sl, h);
	gluDeleteQuadric(sphere);
}

void drawCylinder(float tr, float br, float h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
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
	glLoadIdentity(); // reset matrix


	glTranslatef(ptx, pty, 0.0); //translate x and y for projection
	glRotatef(pr, 0.0, 1.0, 0.0);
	if (isOrtho) {
		glOrtho(-10.0, 10.0, -10.0, 10.0, oNear, oFar);
	}
	else {

		gluPerspective(20.0, 1.0, -1.0, 1.0);
		glFrustum(-10.0, 10.0, -10.0, 10.0, pNear, pFar);
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	projection();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(tx1, 0.0, tz); //translation along the z-axis
	glRotatef(rx, 1.0, 1.0, 1.0);
	rx += rspeed;
	drawSphere(rs1, 30, 30);
	glPopMatrix();

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