#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include <SDL2/SDL_render.h>
#include <vector>

class Player : public Object {
public:
  Player(int x, int y, int w, int h);
  ~Player();

  void render(SDL_Renderer *renderer);

  void attack();
  void useItem(int itemId);

  int getHealth() const;
  void setHealth(int health);

  int getSpeed() const;
  void setSpeed(int speed);

  bool checkCollision(std::vector<Object *> &objs);

  void move(std::vector<Object *> &objs);
  void changeHeading(float a);

protected:
  int m_health;
  int m_speed;
  int m_inventory[10]; // array to hold up to 10 items
  int m_velocity[2];
  float m_heading;
};

#endif // PLAYER_HPP
