#include "diDik2Keys.h"

#include "diDef.h"
#include "diKeys.h"

/*******************************************************************/

static struct
{
	short	Dik;
	short	Key;
}
Table[] =
{
// Arrows:

	{DIK_DOWN	, diKeys::ArrowDown},
	{DIK_LEFT	, diKeys::ArrowLeft},
	{DIK_RIGHT	, diKeys::ArrowRight},
	{DIK_UP		, diKeys::ArrowUp},

// Ascii:

	{DIK_SPACE	, ' '},
	{DIK_A		, 'A'},
	{DIK_B		, 'B'},
	{DIK_C		, 'C'},
	{DIK_D		, 'D'},
	{DIK_E		, 'E'},
	{DIK_F		, 'F'},
	{DIK_G		, 'G'},
	{DIK_H		, 'H'},
	{DIK_I		, 'I'},
	{DIK_J		, 'J'},
	{DIK_K		, 'K'},
	{DIK_L		, 'L'},
	{DIK_M		, 'M'},
	{DIK_N		, 'N'},
	{DIK_O		, 'O'},
	{DIK_P		, 'P'},
	{DIK_Q		, 'Q'},
	{DIK_R		, 'R'},
	{DIK_S		, 'S'},
	{DIK_T		, 'T'},
	{DIK_U		, 'U'},
	{DIK_V		, 'V'},
	{DIK_W		, 'W'},
	{DIK_X		, 'X'},
	{DIK_Y		, 'Y'},
	{DIK_Z		, 'Z'},
	{DIK_1		, '1'},
	{DIK_2		, '2'},
	{DIK_3		, '3'},
	{DIK_4		, '4'},
	{DIK_5		, '5'},
	{DIK_6		, '6'},
	{DIK_7		, '7'},
	{DIK_8		, '8'},
	{DIK_9		, '9'},
	{DIK_0		, '0'},

// Function keys:

	{DIK_F1			, diKeys::F1},
	{DIK_F2			, diKeys::F2},
	{DIK_F3			, diKeys::F3},
	{DIK_F4			, diKeys::F4},
	{DIK_F5			, diKeys::F5},
	{DIK_F6			, diKeys::F6},
	{DIK_F7			, diKeys::F7},
	{DIK_F8			, diKeys::F8},
	{DIK_F9			, diKeys::F9},
	{DIK_F10		, diKeys::F10},
	{DIK_F11		, diKeys::F11},
	{DIK_F12		, diKeys::F12},
	{DIK_F13		, diKeys::F13},
	{DIK_F14		, diKeys::F14},
	{DIK_F15		, diKeys::F15},

// Punctuation:

	{DIK_MINUS		, '-'},
	{DIK_EQUALS		, '='},
	{DIK_LBRACKET	, '['},
	{DIK_RBRACKET	, ']'},
	{DIK_SLASH		, '/'},
	{DIK_SEMICOLON	, ';'},
	{DIK_APOSTROPHE	, '\''},
	{DIK_COMMA		, ','},
	{DIK_PERIOD		, '.'},
	{DIK_BACKSLASH	, '\\'},
	{DIK_GRAVE		, '`'},

// Others:

	{DIK_LMENU		, diKeys::AltL},
	{DIK_RMENU		, diKeys::AltR},
	{DIK_BACK		, diKeys::Backspace},	// Backspace.
	{DIK_CAPSLOCK	, diKeys::CapsLock},
	{DIK_LCONTROL	, diKeys::CtrlL},
	{DIK_RCONTROL	, diKeys::CtrlR},
	{DIK_DELETE		, diKeys::Delete},
	{DIK_END		, diKeys::End},
	{DIK_RETURN		, diKeys::Enter},		// Enter on main keypad.
	{DIK_NUMPADENTER, diKeys::EnterNumPad},	// Enter on numeric keypad.
	{DIK_ESCAPE		, diKeys::Esc},
	{DIK_HOME		, diKeys::Home},
	{DIK_INSERT		, diKeys::Insert},
	{DIK_NUMLOCK	, diKeys::NumLock},
	{DIK_PAUSE		, diKeys::Pause},
	{DIK_PRIOR		, diKeys::PageUp},
	{DIK_NEXT		, diKeys::PageDown},
	{DIK_SCROLL		, diKeys::Scroll},			// Scroll lock.
	{DIK_LSHIFT		, diKeys::ShiftL},
	{DIK_RSHIFT		, diKeys::ShiftR},
	{DIK_TAB		, diKeys::Tab},
	{DIK_LWIN		, diKeys::WinL},			// Left windows key.
	{DIK_RWIN		, diKeys::WinR},			// Right windows key.

// Stop:

	{diKeys::Min}
};

/*******************************************************************/

bool diDik2Keys::getKey(int dik, int& key)
{
	for(int i = 0; Table[i].Dik != diKeys::Min; i++)
		if(Table[i].Dik == dik)
		{
			key = Table[i].Key;

			return true;
		}

	key = diKeys::Min;

	return false;
}
