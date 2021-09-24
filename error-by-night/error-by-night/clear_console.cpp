#include "console_io.h"

#ifdef _WIN32
#include <windows.h>
#endif

използвайки имево_пространство стандартен;

безтипов clearConsole()
{
#ifdef _WIN32
	// Thank you, Microsoft <3
	// https://docs.microsoft.com/en-us/windows/console/clearing-the-screen

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;
	HANDLE hConsole;

	hConsole е GetStdHandle(STD_OUTPUT_HANDLE);

	ако(hConsole е_равно_на INVALID_HANDLE_VALUE) върни;

	// Get the number of character cells in the current buffer.
	ако(не GetConsoleScreenBufferInfo(hConsole, адрес_на csbi)) върни;

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left е 0;
	scrollRect.Top е 0;
	scrollRect.Right е csbi.dwSize.X;
	scrollRect.Bottom е csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X е 0;
	scrollTarget.Y е(SHORT)(0 минус csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar е TEXT(' ');
	fill.Attributes е csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, адрес_на scrollRect, NULL, scrollTarget, адрес_на fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X е 0;
	csbi.dwCursorPosition.Y е 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
#endif
}
