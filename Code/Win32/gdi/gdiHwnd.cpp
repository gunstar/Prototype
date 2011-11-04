#include "gdiHwnd.h"

/*******************************************************************/

gdiHwnd::gdiHwnd(HWND handle)
{
	Handle = handle;
}

void gdiHwnd::clearStyleBits(int style_bits)
{
	int old = GetWindowLong(Handle, GWL_STYLE);

	SetWindowLong(Handle, GWL_STYLE, old & (~ style_bits));
}

void gdiHwnd::close()
{
	if(Handle)
	{
		DestroyWindow(Handle);

		Handle = 0;
	}
}

void gdiHwnd::getClientBrushRgb(int rgb[3])
{
	HGDIOBJ		brush;
	HDC			dc;
	LOGBRUSH	info;

	dc = GetDC(Handle);

	brush = SelectObject(dc, GetStockObject(BLACK_BRUSH));

	GetObject(brush, sizeof(info), &info);

	rgb[0] = GetRValue(info.lbColor);
	rgb[1] = GetGValue(info.lbColor);
	rgb[2] = GetBValue(info.lbColor);

	SelectObject(dc, brush);

	ReleaseDC(Handle, dc);
}

void gdiHwnd::getClientPos(int &cx, int &cy)
{
	POINT	point;

	point.x = 0;
	point.y = 0;

	ClientToScreen(Handle, &point);

	cx = point.x;
	cy = point.y;
}

void gdiHwnd::getClientRect(int &cx, int &cy, int &cw, int &ch)
{
	getClientPos(cx, cy);
	getClientSize(cw, ch);
}

void gdiHwnd::getClientSize(int &cw, int &ch)
{
	RECT	rect;

	GetClientRect(Handle, &rect);

	cw = rect.right;
	ch = rect.bottom;
}

void gdiHwnd::getClientSize(RECT& rect)
{
	GetClientRect(Handle, &rect);
}

void gdiHwnd::getFontSize(int &fw, int &fh)
{
	HDC			hdc;
	TEXTMETRIC	metric;

	hdc = GetDC(Handle);

	GetTextMetrics(hdc, &metric);

	fw = metric.tmMaxCharWidth;
	fh = metric.tmHeight;

	ReleaseDC(Handle, hdc);
}

char* gdiHwnd::getText()
{
	static char tmp[1024];

	int len = GetWindowText(Handle, tmp, 1024);

	tmp[len] = 0;

	return tmp;
}

void gdiHwnd::getWindowPos(int &wx, int &wy)
{
	RECT	rect;

	GetWindowRect(Handle, &rect);

	wx = rect.left;
	wy = rect.top;
}

void gdiHwnd::getWindowPosSize(int& wx, int& wy, int& ww, int& wh)
{
	getWindowPos(wx, wy);
	getWindowSize(ww, wh);
}

void gdiHwnd::getWindowSize(int &ww, int &wh)
{
	RECT	rect;

	GetWindowRect(Handle, &rect);

	ww = rect.right - rect.left;
	wh = rect.bottom - rect.top;
}

void gdiHwnd::hide()
{
	ShowWindow(Handle, SW_HIDE);
}

void gdiHwnd::invalidate(bool clearBackground, bool doItNow)
{
	RedrawWindow
	(
		Handle,
		0,
		0,
		RDW_INVALIDATE |
		(clearBackground ? RDW_ERASE : 0) |
		(doItNow? RDW_UPDATENOW : 0)
	);
}

bool gdiHwnd::isActive()
{
	return Handle == GetActiveWindow();
}

void gdiHwnd::maximize()
{
	ShowWindow(Handle, SW_MAXIMIZE);
}

void gdiHwnd::moveToTop()
{
	SetForegroundWindow(Handle);
}

void gdiHwnd::postUserMsg(UINT userMsg, WPARAM wpar, LPARAM lpar)
{
	PostMessage(Handle, WM_USER + userMsg, wpar, lpar);
}

void gdiHwnd::refresh()
{
	UpdateWindow(Handle);
}

void gdiHwnd::setClientPos(int cx, int cy)
{
	int	ox, oy;
	int	wx, wy;

	getClientPos(ox, oy);
	getWindowPos(wx, wy);

	setWindowPos(wx + (cx - ox), wy + (cy - oy));
}

void gdiHwnd::setClientSize(int cw, int ch)
{
	int	ow, oh;
	int	ww, wh;

	getClientSize(ow, oh);
	getWindowSize(ww, wh);

	setSize(ww + (cw - ow), wh + (ch - oh));
}

void gdiHwnd::setCursorClip(bool on)
{
	if(on)
	{
		RECT rect;

		GetWindowRect(Handle, &rect);

		ClipCursor(&rect);
	}
	else
		ClipCursor(0);
}

void gdiHwnd::setForeground()
{
	if(! Handle)
		return;

	SetForegroundWindow(Handle);
}

void gdiHwnd::setHScroll(float pos)
{
	if(pos < 0)
			pos = 0;

	if(pos > 1)
			pos = 1;

	SetScrollRange(Handle, SB_HORZ, 0, 10000, 0);
	SetScrollPos(Handle, SB_HORZ, (int) (pos * 10000), 1);
}

void gdiHwnd::setMenu(HMENU menu)
{
	SetMenu(Handle, menu);
}

void gdiHwnd::setParent(HWND parent)
{
	SetParent(Handle, parent);
}

void gdiHwnd::setPosSize(int wx, int wy, int ww, int wh)
{
	MoveWindow(Handle, wx, wy, ww, wh, 1);
}

void gdiHwnd::setSize(int ww, int wh)
{
	SetWindowPos(Handle, 0, 0, 0, ww, wh, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
}

void gdiHwnd::setStyleBits(int style_bits)
{
	int old = GetWindowLong(Handle, GWL_STYLE);

	SetWindowLong(Handle, GWL_STYLE, old | style_bits);
}

void gdiHwnd::setStyleBitsEx(int style_bits)
{
	int old = GetWindowLong(Handle, GWL_EXSTYLE);

	SetWindowLong(Handle, GWL_EXSTYLE, old | style_bits);
}

void gdiHwnd::setText(char *text)
{
	SetWindowText(Handle, text);
}

void gdiHwnd::setVScroll(float pos)
{
	if(pos < 0)
			pos = 0;

	if(pos > 1)
			pos = 1;

	SetScrollRange(Handle, SB_VERT, 0, 10000, 0);
	SetScrollPos(Handle, SB_VERT, (int) (pos * 10000), 1);
}

void gdiHwnd::setWindowPos(int wx, int wy)
{
	SetWindowPos(Handle, 0, wx, wy, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
}

void gdiHwnd::setWindowPosCenter()
{
	RECT	desktop;
	int		ww, wh;
	int		wx, wy;

	GetWindowRect(GetDesktopWindow(), &desktop);
	getWindowSize(ww, wh);

	wx = (desktop.right - desktop.left) / 2 - ww / 2;
	wy = (desktop.bottom - desktop.top) / 2 - wh / 2;

	setWindowPos(wx, wy);
}

void gdiHwnd::show()
{
	ShowWindow(Handle, SW_SHOW);
}
