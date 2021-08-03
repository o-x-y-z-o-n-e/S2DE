#include "Player.h"
#include <cmath>

void Player::FixedUpdate(float delta) {
    counter += delta;

    //Vector position = *new Vector(sin(counter)*32, cos(counter)*32);

    //GetObject()->SetPosition(position);

    Move(delta);
}

void Player::Move(float delta) {

    printf("left");

    Vector position = GetObject()->GetPosition();

    if(S2DE::Input::GetPress("up")) {
        velocity.y = -9.81f;
        printf("up");
    }

    if(position.y > 0) {
        velocity.y += 9.81f * delta;
    }

    //position += velocity * delta;
    position.x += velocity.x * delta;
    position.y += velocity.y * delta;

    if(position.y > 0) {
        position.y = 0;
        velocity.y = 0;
    }

    GetObject()->SetPosition(position);
}
