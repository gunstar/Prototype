/*
	gdiHwnd manages a HWND.

	IMPORTANT: Call close() to close the HWND. The destructor does NOT automatically do this.
*/

#ifndef _gdiHwnd
#define _gdiHwnd

#include "gdiDef.h"

class gdiHwnd
{
public:
				gdiHwnd				(HWND handle = 0);

	void		clearStyleBits		(int styleBits);
	void		close				();

	void		getClientBrushRgb	(int rgb[3]);
	void		getClientPos		(int& cx, int& cy);						// Screen position top-left corner.
	void		getClientRect		(int& cx, int& cy, int& cw, int& ch);
	void		getClientSize		(int& cw, int& ch);
	void		getClientSize		(RECT& rect);
	void		getFontSize			(int& fw, int& fh);
	HWND		getHandle			()										{ return Handle; }
	char*		getText				();
	void		getWindowPos		(int& wx, int& wy);
	void		getWindowPosSize	(int& wx, int& wy, int& ww, int& wh);
	void		getWindowSize		(int& ww, int& wh);

	void		hide				();

	void		invalidate			(bool clearBackground = true, bool doItNow = false);

	bool		isActive			();
	bool		isOpen				()										{ return Handle != 0; }

	void		maximize			();
	void		moveToTop			();
	void		postUserMsg			(UINT userMsg, WPARAM wpar, LPARAM lpar);
	void		refresh				();

	void		setClientPos		(int cx, int cy);
	void		setClientSize		(int cw, int ch);
	void		setCursorClip		(bool on);
	void		setForeground		();										// Moves window to the foreground (top).
	void		setHScroll			(float pos);							// 0 <= pos <= 1.
	void		setMenu				(HMENU menu);
	void		setParent			(HWND parent);
	void		setPosSize			(int wx, int wy, int ww, int wh);
	void		setSize				(int ww, int wh);
	void		setStyleBits		(int styleBits);
	void		setStyleBitsEx		(int styleBits);
	void		setText				(char* text);
	void		setVScroll			(float pos);							// 0 <= pos <= 1.
	void		setWindowPos		(int wx, int wy);
	void		setWindowPosCenter	();

	void		show				();

protected:
	HWND		Handle;				// != 0 if open.
};

#endif
