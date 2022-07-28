#include <Core/Engine.h>

int main(int argc, char const *argv[])
{
    auto* engine = Engine::GetRef();

    engine->Init();

    while (engine->IsRunning()) {
        engine->Update(0.0f);
        engine->Render();
        engine->Events();
    }

    engine->Terminate();

    return 0;
}
