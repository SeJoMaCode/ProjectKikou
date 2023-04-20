#include "object.hpp"
#include "player.hpp"
#include "window.hpp"
#include <SDL2/SDL_stdinc.h>
#include <vector>

int main(int argc, char *argv[]) {
  Window windowFPV("Project Kikou FPV", 800, 600);
  Window window("Project Kikou TD", 800, 600);

  SDL_Color red = {255, 0, 0, 255};

  std::vector<Object *> walls;
  walls.push_back(new Object(0, 0, 800, 10, red));
  walls.push_back(new Object(0, 0, 10, 600, red));
  walls.push_back(new Object(0, 590, 800, 10, red));
  walls.push_back(new Object(790, 0, 10, 600, red));
  walls.push_back(new Object(0, 0, 50, 50, red));

  Player player(400, 300, 5, 5);

  bool quit = false;
  Uint32 lastUpdate = 0;
  const Uint32 updateInterval = 1000 / 60;
  Uint32 accumulator = 0;

  while (!quit) {
    Uint32 currentTicks = SDL_GetTicks();
    Uint32 elapsed = currentTicks - lastUpdate;
    lastUpdate = currentTicks;
    accumulator += elapsed;

    while (accumulator >= updateInterval) {
      quit = window.pollEvents() || windowFPV.pollEvents();
      player.handleInput();
      player.move(walls);

      accumulator -= updateInterval;
    }

    window.clear();
    windowFPV.clear();

    window.render(walls);
    window.render(player);
    player.renderFPV(windowFPV.getRenderer(), walls);

    window.display();
    windowFPV.display();
  }

  return 0;
}
