#pragma once
#include "ResourceIdentifiers.hpp"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"

#include <vector>
#include <functional>

class Character;
class Explosion;

struct Direction
{
	Direction(float angle, float distance) : angle(angle), distance(distance)
	{
	}

	float angle;
	float distance;
};

struct CharacterData
{
	int hitpoints;
	float speed;
	float rotationSpeed;
	TextureIDs texture;
	sf::IntRect textureRect;
	sf::Time fireInterval;
	std::vector<Direction> directions;
	bool hasAnimation;
};


struct ProjectileData
{
	int damage;
	float speed;
	float textureScale;
	TextureIDs texture;
	sf::IntRect textureRect;
};

struct ExplosionData
{
	int damage;
	float radious;
	int lifeTimeSeconds;
	TextureIDs texture;
	sf::IntRect textureRect;
};

struct PickupData
{
	std::function<void(Character&)> action;
	TextureIDs texture;
	sf::IntRect textureRect;
};

struct ParticleData
{
	sf::Color color;
	sf::Time lifetime;
};

std::vector<CharacterData> initializeCharacterData();
std::vector<ExplosionData> initializeExplosionData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();
std::vector<ParticleData> initializeParticleData();