#include "Gui.h"
#include "Platform/Win32/Win32Application.h"

Win32Application::Win32Application(int argc, char** argv) : IApplication(argc, argv) { }

int Win32Application::exec() {

    // get and translate windows message
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}