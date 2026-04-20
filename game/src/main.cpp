#include "Engine/Core/Application.hpp"

int main() {
    Engine::Core::Application app;
    if (!app.Initialize()) {
        return 1;
    }

    const int result = app.Run();
    app.Shutdown();
    return result;
}
