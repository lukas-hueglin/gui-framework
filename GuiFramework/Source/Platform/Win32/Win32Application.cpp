#include "Gui.h"
#include "Platform/Win32/Win32Application.h"
#include <chrono>

Win32Application::Win32Application(int argc, char** argv) : IApplication(argc, argv) { }

int Win32Application::exec() {

    // create time stamp and duration object
    std::chrono::time_point<std::chrono::system_clock> now, lastFrame;
    std::chrono::duration<float> deltaTime;
    lastFrame = std::chrono::system_clock::now();

    // get and translate windows message
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {

        // handle Windows messages
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // measure time
        now = std::chrono::system_clock::now();
        deltaTime = now - lastFrame;

        if (deltaTime.count() >= 1.0f / 30.0f) {
            onTick(deltaTime.count());
            lastFrame = now;
        }
    }

	return 0;
}