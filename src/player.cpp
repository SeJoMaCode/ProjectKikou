#include "player.hpp"
#include <SDL2/SDL_render.h>
#include <cmath>

Player::Player(int x, int y, int w, int h)
    : Object(x, y, w, h, {255, 255, 255, 255}), m_health(100),
      m_speed(5), m_direction{0, 0}, m_heading(0.0) {
  for (int i = 0; i < 10; i++) {
    m_inventory[i] = 0;
  }
}

Player::~Player() {}

void Player::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
  SDL_RenderFillRect(renderer, &m_rect);
  int xCenter = m_rect.x + m_rect.w / 2;
  int yCenter = m_rect.y + m_rect.h / 2;
  SDL_RenderDrawLine(renderer, xCenter, yCenter,
                     xCenter + (std::cos(m_heading) * 10),
                     yCenter + (std::sin(m_heading) * 10));
}

void Player::attack() {
  // Code to handle player attacking
}

void Player::useItem(int itemId) {
  // Code to handle player using an item
}

int Player::getHealth() const { return m_health; }

void Player::setHealth(int health) { m_health = health; }

int Player::getSpeed() const { return m_speed; }

void Player::setSpeed(int speed) { m_speed = speed; }

void Player::move() {
  m_rect.x += std::cos(m_heading) * m_speed * m_direction[0];
  m_rect.y += std::sin(m_heading) * m_speed * m_direction[0];
}

void Player::setForwardVelocity(int x) { m_direction[0] = x; }

void Player::setLeftVelocity(int y) { m_direction[1] = y; }

void Player::changeHeading(float a) { m_heading += a * 0.1; }
