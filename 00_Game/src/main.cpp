#include "Engine/Core/Application.hpp"

#include <exception>
#include <iostream>
#include <string>

#if defined(_WIN32)
#include <Windows.h>
#endif

int main() {
    try {
        Engine::Core::Application app;
        if (!app.Initialize()) {
#if defined(_WIN32)
            MessageBoxA(nullptr, "Application failed to initialize. See FullGame.log for details.", "Startup Error", MB_OK | MB_ICONERROR);
#endif
            return 1;
        }

        const int result = app.Run();
        app.Shutdown();
        return result;
    } catch (const std::exception& ex) {
        std::cerr << "Unhandled exception: " << ex.what() << '\n';
#if defined(_WIN32)
        MessageBoxA(nullptr, ex.what(), "Unhandled Exception", MB_OK | MB_ICONERROR);
#endif
        return 2;
    } catch (...) {
        std::cerr << "Unhandled unknown exception\n";
#if defined(_WIN32)
        MessageBoxA(nullptr, "Unhandled unknown exception", "Unhandled Exception", MB_OK | MB_ICONERROR);
#endif
        return 3;
    }
}
