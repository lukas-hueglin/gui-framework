#include "Gui.h"
#include "Platform/Win32/Win32Application.h"
#include <chrono>
#include <iostream>

Win32Application::Win32Application(int argc, char** argv) : IApplication(argc, argv) { }

int Win32Application::exec() {

    //AllocConsole();
    //freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    //std::cout << "This works" << std::endl;

    // create time stamp and duration object
    std::chrono::time_point<std::chrono::system_clock> now, lastFrame;
    std::chrono::duration<float> deltaTime;
    lastFrame = std::chrono::system_clock::now();

    // get and translate windows message
    MSG msg = { };
    while (true) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            
            // handle Windows messages
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // measure time
            now = std::chrono::system_clock::now();
            deltaTime = now - lastFrame;

            if (deltaTime.count() >= 1.0f / 30.0f) {
                onTick(deltaTime.count());
                lastFrame = now;
            }
        }


    }

	return 0;
}