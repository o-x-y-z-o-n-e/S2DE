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

    S2DE::vect oldPosition = GetObject()->GetPosition();
	S2DE::vect newPosition = *new S2DE::vect(oldPosition.x, oldPosition.y);

    if(S2DE::Input::GetPress("up")) {
        velocity.y = -9.81f;
        printf("up");
    }

	velocity.y += 9.81f * delta;

    //newPosition.x += velocity.x * delta;
    //newPosition.y += velocity.y * delta;

	newPosition = newPosition + (velocity * delta);

	if (S2DE::Physics::RectIntersects(bounds, newPosition, floor, *new S2DE::vect())) {
		newPosition = oldPosition;
	}

    GetObject()->SetPosition(newPosition);
}
