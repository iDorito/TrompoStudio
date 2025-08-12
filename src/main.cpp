#include "Engine/Engine.h"
#include <memory>

int main() {
    auto engine = std::make_shared<Trompo::Engine>();
    engine->Run();
    return 0;
}