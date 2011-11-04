/*
	diKeys defines all non-ascii keys.
*/

#ifndef _diKeys
#define	_diKeys

class diKeys
{
public:
	enum
	{
	// Min:

		Min	= -1000,

	// Joy:

		Joy0,
		Joy1,
		Joy2,
		Joy3,
		Joy4,
		Joy5,
		Joy6,
		Joy7,
		Joy8,
		Joy9,
		Joy10,
		Joy11,
		Joy12,
		Joy13,
		Joy14,
		Joy15,

	// Keys:

		AltL,
		AltR,
		ArrowDown,
		ArrowLeft,
		ArrowRight,
		ArrowUp,
		Backspace,			// Backspace
		CapsLock,
		CtrlL,
		CtrlR,
		Delete,
		End,
		Enter,				// Enter on main keyboard.
		EnterNumPad,		// Enter on numeric keypad.
		Esc,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Home,
		Insert,
		NumLock,
		Pause,
		PageDown,
		PageUp,
		Scroll,
		ShiftL,
		ShiftR,
		Tab,
		WinL,				// Left windows key
		WinR,				// Right windows key

	// Mouse:

		Mouse0,				// Left
		Mouse1,				// Right
		Mouse2,

	// Xbox:

		XboxAnalogDown,		// Interpreting analog stick as digital stick (useful for Xbox UI).
		XboxAnalogLeft,
		XboxAnalogRight,
		XboxAnalogUp,
		XboxDigitalDown,
		XboxDigitalLeft,
		XboxDigitalRight,
		XboxDigitalUp,
		XboxBack,
		XboxButtonA,
		XboxButtonB,
		XboxButtonX,
		XboxButtonY,
		XboxShoulderLeft,
		XboxShoulderRight,
		XboxStart,
		XboxThumbLeft,		// Left analog stick pressed down.
		XboxThumbRight,		// Right analog stick pressed down.
		XboxTriggerLeft,
		XboxTriggerRight,

	// PS3:	IMPORTANT - these correspond directly to XboxYYYYYY enums (based on physical correlation)

		Ps3AnalogDown = XboxAnalogDown,		// Interpreting analog stick as digital stick (useful for PS3 UI).
		Ps3AnalogLeft,
		Ps3AnalogRight,
		Ps3AnalogUp,
		Ps3DigitalDown,
		Ps3DigitalLeft,
		Ps3DigitalRight,
		Ps3DigitalUp,
		Ps3Select,			// == XboxBack
		Ps3ButtonCross,		// == XboxButtonA
		Ps3ButtonCircle,	// == XboxButtonB
		Ps3ButtonSquare,	// == XboxButtonX
		Ps3ButtonTriangle,	// == XboxButtonY
		Ps3L1,				// == XboxShoulderLeft
		Ps3R1,				// == XboxShoulderRight
		Ps3Start,
		Ps3L3,				// == XboxThumbLeft
		Ps3R3,				// == XboxThumbRight
		Ps3L2,				// == XboxTriggerLeft
		Ps3R2,				// == XboxTriggerRight

	// PSP:

		PspAnalogDown = XboxAnalogDown,
		PspAnalogLeft,
		PspAnalogRight,
		PspAnalogUp,
		PspDigitalDown,
		PspDigitalLeft,
		PspDigitalRight,
		PspDigitalUp,
		PspSelect,
		PspButtonCross,
		PspButtonCircle,
		PspButtonSquare,
		PspButtonTriangle,
		PspL,
		PspR,
		PspStart,
		PspL3,				// == XboxThumbLeft
		PspR3,				// == XboxThumbRight
		PspL2,				// == XboxTriggerLeft
		PspR2,				// == XboxTriggerRight
		
	// Max:

		Max,

	// Special:

		Space = 32
	};
};

#endif
