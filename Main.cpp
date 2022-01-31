#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <Windows.h>
#include "zUdoQfuncions.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32")

using namespace std;

int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	PlaySound(TEXT("Moanin'.wav"), NULL, SND_LOOP | SND_ASYNC);
	start();
	return 0;
}