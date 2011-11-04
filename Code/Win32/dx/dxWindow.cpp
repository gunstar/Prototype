#include "dxWindow.h"

#include "dxDeviceFactory.h"
#include "gdi/gdiHwnd.h"

/*******************************************************************/

static void makeWindowClass(char* wndClassName)
{
	WNDCLASS wndClass;

	wndClass.style			= CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= DefWindowProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= NULL;
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= wndClassName;

	RegisterClass(&wndClass);
}

/*******************************************************************/

dxWindow::dxWindow(IDirect3D9* d9)
{
	D9		= d9;
	Window	= 0;
}

dxWindow::~dxWindow()
{
	close();
}

void dxWindow::getDesktopSize(int& dw, int& dh)
{
	RECT rect;

	GetWindowRect(GetDesktopWindow(), &rect);

	dw = rect.right;
	dh = rect.bottom;
}

bool dxWindow::open(const char* title)
{
	if(! createWindow(title))
		return false;

	gdiHwnd win(Window);

	win.maximize();
	win.show();

	return true;
}

bool dxWindow::open(const char* title, int ww, int wh)
{
	if(! createWindow(title))
		return false;

	gdiHwnd win(Window);

	win.setClientSize(ww, wh);
	win.setWindowPosCenter();
	win.show();

	return true;
}

void dxWindow::close()
{
	if(Window)
	{
		gdiHwnd win(Window);

		win.close();
	}
}

dxDevice* dxWindow::makeDevice()
{
	dxDeviceFactory deviceFactory(D9);

	return deviceFactory.makeDevice(Window);
}

/*******************************************************************/

bool dxWindow::createWindow(const char* windowTitle)
{
// Close:

	close();

// Make class:

	char* wndClassName = "dxWindowWindowClass";

	makeWindowClass(wndClassName);

// Make window:

	Window = CreateWindow
	(
		wndClassName,
		windowTitle,
		WS_OVERLAPPEDWINDOW,
		0, 0, 0, 0,
		NULL, NULL, NULL, NULL
	);

	return Window != 0;
}
