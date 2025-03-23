#include "scene.h"

#include "raylib.h"

#include <memory>

int main() {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>();
    scene->run();

    return 0;
}
