#include "Player.h"
#include <cmath>

void Player::FixedUpdate(float delta) {
    counter += delta;

    Vector position = *new Vector(sin(counter)*32, cos(counter)*32);

    GetObject()->SetPosition(position);
}
