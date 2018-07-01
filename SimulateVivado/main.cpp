#include "stdafx.h"
#include "Vivado.h"
#include <termios.h>

int _getch()
{
	struct termios stored_settings;
	struct termios new_settings;
	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);

	int c;

	c = getchar();

	tcsetattr(0, TCSANOW, &stored_settings);

	return c;
}

void HideCursor()
{
	cout << "\033[?25l";
	system("stty -echo");
}

void ResetCursor()
{
	cout << "\33[?25h";
	cout << "\033[0m";
	system("stty echo");
}

void ShowWhite()
{
	cout << "\033[47m";
	cout << "\033[30m";
}

void ShowBlack()
{
	cout << "\033[40m";
	cout << "\033[37m";
}

int main()
{
	Vivado::GetInstence();
	Vivado::DestroyInstence();
    return 0;
}