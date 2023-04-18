#include "object.hpp"
#include "player.hpp"
#include "window.hpp"
#include <SDL2/SDL_stdinc.h>
#include <chrono>
#include <thread>
#include <vector>

int main(int argc, char *argv[]) {
  Window window("Project Kikou", 800, 600);

  // set frame rate
  const int fps = 60;
  const auto frameTime = std::chrono::milliseconds(1000 / fps);

  // get initial time
  auto lastTime = std::chrono::steady_clock::now();

  SDL_Color red = {255, 0, 0, 255};

  std::vector<Object *> walls;
  walls.push_back(new Object(0, 0, 800, 10, red));
  walls.push_back(new Object(0, 0, 10, 600, red));
  walls.push_back(new Object(0, 590, 800, 10, red));
  walls.push_back(new Object(790, 0, 10, 600, red));
  window.addRenderObjects(walls);

  Player player(400, 300, 5, 5);
  window.addRenderObject(player);

  bool quit = false;
  Uint32 lastUpdate = 0;
  const Uint32 updateInterval = 1000 / 60;

  while (!quit) {
    Uint32 currentTicks = SDL_GetTicks();
    Uint32 elapsed = currentTicks - lastUpdate;

    if (elapsed >= updateInterval) {
      lastUpdate = currentTicks;

      quit = window.pollEvents(player);

      window.render();
    }
  }

  return 0;
}
