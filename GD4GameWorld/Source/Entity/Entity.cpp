#include "Entity/Entity.hpp"
#include "Constant/Constants.hpp"

#include <cassert>


Entity::Entity(int hitpoints) :
	mAngle(0),
	mHitpoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

int Entity::getHitpoints() const
{
	return mHitpoints;
}

void Entity::repair(int points)
{
	assert(points > 0);
	mHitpoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);
	mHitpoints -= points;
}

void Entity::destroy()
{
	mHitpoints = 0;
}

void Entity::remove()
{
	destroy();
}

bool Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}

//Mike
void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	move(mVelocity * dt.asSeconds());
}

// Alex - Get/Set Angle, Separating movement and rotation
void Entity::setAngle(float angle)
{
	mAngle = angle;
}

float Entity::getAngle() const
{
	return 0;// mAngle;
}

// da - Delta of angle
void Entity::applyRotation(float da)
{
	mAngle += da;
}
