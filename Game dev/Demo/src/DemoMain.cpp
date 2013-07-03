#include "windows.h"
#include "DemoApp.h"
using namespace Demo;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
//int main()
{
	DemoApp *app = DemoApp::getSingletonPtr();
	app->go();

	return 0;
}