#include "DataTables.hpp"
#include "Character.hpp"
#include "Explosion.hpp"
#include "Projectile.hpp"
#include "Particle.hpp"
#include "Pickup.hpp"
#include "Constants.hpp"
#include "MapTiler.hpp"


using namespace std::placeholders;

std::vector<CharacterData> initializeCharacterData()
{
	std::vector<CharacterData> data(static_cast<int>(Character::Type::TypeCount));
	data[static_cast<int>(Character::Type::Player)].hitpoints = PLAYERHITPOINTS;
	data[static_cast<int>(Character::Type::Player)].speed = PLAYERSPEED;
	data[static_cast<int>(Character::Type::Player)].rotationSpeed = ROTATION_SPEED; // Alex - Add rotation speed
	data[static_cast<int>(Character::Type::Player)].fireInterval = sf::seconds(PLAYERFIREINTERVAL);
	data[static_cast<int>(Character::Type::Player)].texture = TextureIDs::PlayerMove;
	data[static_cast<int>(Character::Type::Player)].textureRect = sf::IntRect(
		0, 0, PLAYER_MOVE_ANIMATION_WIDTH, PLAYER_MOVE_ANIMATION_HEIGHT);
	data[static_cast<int>(Character::Type::Player)].moveScale = 0.5f;
	data[static_cast<int>(Character::Type::Player)].deathScale = 0.5f;
	data[static_cast<int>(Character::Type::Player)].moveFrames = 18;
	data[static_cast<int>(Character::Type::Player)].deathFrames = 6;
	data[static_cast<int>(Character::Type::Player)].moveAnimation = TextureIDs::PlayerMove;
	data[static_cast<int>(Character::Type::Player)].moveRect = sf::IntRect(
		0, 0, PLAYER_MOVE_ANIMATION_WIDTH, PLAYER_MOVE_ANIMATION_HEIGHT);
	data[static_cast<int>(Character::Type::Player)].deathAnimation = TextureIDs::PlayerDeath;
	data[static_cast<int>(Character::Type::Player)].deathRect = sf::IntRect(
		0, 0, PLAYER_DEATH_ANIMATION_WIDTH, PLAYER_DEATH_ANIMATION_HEIGHT);

	data[static_cast<int>(Character::Type::Zombie)].hitpoints = ZOMBIEHITPOINTS;
	data[static_cast<int>(Character::Type::Zombie)].speed = ZOMBIESPEED;
	data[static_cast<int>(Character::Type::Zombie)].rotationSpeed = ROTATION_SPEED; // Alex - Add rotation speed
	data[static_cast<int>(Character::Type::Zombie)].texture = TextureIDs::Entities;
	data[static_cast<int>(Character::Type::Zombie)].textureRect = sf::IntRect(
		144, 0, ZOMBIE_MOVE_ANIMATION_WIDTH, ZOMBIE_MOVE_ANIMATION_HEIGHT);
	data[static_cast<int>(Character::Type::Zombie)].fireInterval = sf::Time::Zero;
	data[static_cast<int>(Character::Type::Zombie)].directions.push_back(Direction(+45.f, 80.f));
	data[static_cast<int>(Character::Type::Zombie)].directions.push_back(Direction(-45.f, 160.f));
	data[static_cast<int>(Character::Type::Zombie)].directions.push_back(Direction(+45.f, 80.f));
	data[static_cast<int>(Character::Type::Zombie)].moveAnimation = TextureIDs::ZombieMove;
	data[static_cast<int>(Character::Type::Zombie)].moveRect = sf::IntRect(
		0, 0, ZOMBIE_MOVE_ANIMATION_WIDTH, ZOMBIE_MOVE_ANIMATION_HEIGHT);
	data[static_cast<int>(Character::Type::Zombie)].deathAnimation = TextureIDs::ZombieDeath;
	data[static_cast<int>(Character::Type::Zombie)].deathRect = sf::IntRect(
		0, 0, ZOMBIE_DEATH_ANIMATION_WIDTH, ZOMBIE_DEATH_ANIMATION_HEIGHT);
	data[static_cast<int>(Character::Type::Zombie)].moveScale = 2.f;
	data[static_cast<int>(Character::Type::Zombie)].deathScale = 2.f;
	data[static_cast<int>(Character::Type::Zombie)].moveFrames = 28;
	data[static_cast<int>(Character::Type::Zombie)].deathFrames = 17;

	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(static_cast<int>(Projectile::ProjectileIDs::TypeCount));

	data[static_cast<int>(Projectile::ProjectileIDs::AlliedBullet)].damage = BULLETDAMAGE;
	data[static_cast<int>(Projectile::ProjectileIDs::AlliedBullet)].speed = BULLETSPEED;
	data[static_cast<int>(Projectile::ProjectileIDs::AlliedBullet)].texture = TextureIDs::Entities;
	data[static_cast<int>(Projectile::ProjectileIDs::AlliedBullet)].textureRect = sf::IntRect(175, 64, 3, 14);
	data[static_cast<int>(Projectile::ProjectileIDs::AlliedBullet)].textureScale = 1;

	data[static_cast<int>(Projectile::ProjectileIDs::EnemyBullet)].damage = BULLETDAMAGE;
	data[static_cast<int>(Projectile::ProjectileIDs::EnemyBullet)].speed = BULLETSPEED;
	data[static_cast<int>(Projectile::ProjectileIDs::EnemyBullet)].texture = TextureIDs::Entities;
	data[static_cast<int>(Projectile::ProjectileIDs::EnemyBullet)].textureRect = sf::IntRect(178, 64, 3, 14);
	data[static_cast<int>(Projectile::ProjectileIDs::EnemyBullet)].textureScale = 1;

	data[static_cast<int>(Projectile::ProjectileIDs::Grenade)].damage = GRENADEDAMAGE;
	data[static_cast<int>(Projectile::ProjectileIDs::Grenade)].speed = GRENADESPEED;
	data[static_cast<int>(Projectile::ProjectileIDs::Grenade)].texture = TextureIDs::Grenade;
	data[static_cast<int>(Projectile::ProjectileIDs::Grenade)].textureRect = sf::IntRect(0, 0, 718, 800);
	data[static_cast<int>(Projectile::ProjectileIDs::Grenade)].textureScale = 0.03f;

	return data;
}

std::vector<ExplosionData> initializeExplosionData()
{
	std::vector<ExplosionData> data(static_cast<int>(Explosion::ExplosionIDs::TypeCount));

	data[static_cast<int>(Explosion::ExplosionIDs::GrenadeExplosion)].damage = GRENADEDAMAGE;
	data[static_cast<int>(Explosion::ExplosionIDs::GrenadeExplosion)].radious = 10;
	data[static_cast<int>(Explosion::ExplosionIDs::GrenadeExplosion)].lifeTimeSeconds = 1;
	data[static_cast<int>(Explosion::ExplosionIDs::GrenadeExplosion)].texture = TextureIDs::Entities;
	data[static_cast<int>(Explosion::ExplosionIDs::GrenadeExplosion)].textureRect = sf::IntRect(0, 64, 40, 40);

	return data;
}

std::vector<MapTileData> initializeMapTileData()
{
	std::vector<MapTileData> data(static_cast<int>(MapTiler::MapID::TypeCount));

	data[static_cast<int>(MapTiler::MapID::Dessert)].mapFile = "map.txt";
	data[static_cast<int>(MapTiler::MapID::Dessert)].texture = TextureIDs::MapTiles;
	data[static_cast<int>(MapTiler::MapID::Dessert)].tileSize = sf::Vector2u(DESSERT_TILE_WIDTH, DESSERT_TILE_HEIGHT);

	return data;
}


std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(static_cast<int>(Pickup::PickupID::TypeCount));

	data[static_cast<int>(Pickup::PickupID::HealthRefill)].texture = TextureIDs::Entities;
	data[static_cast<int>(Pickup::PickupID::HealthRefill)].textureRect = sf::IntRect(0, 64, 40, 40);
	data[static_cast<int>(Pickup::PickupID::HealthRefill)].action = [](Character& a)
	{
		a.repair(HEALTHPICKUPREPAIRVALUE);
	};

	data[static_cast<int>(Pickup::PickupID::GrenadeRefill)].texture = TextureIDs::Entities;
	data[static_cast<int>(Pickup::PickupID::GrenadeRefill)].textureRect = sf::IntRect(40, 64, 40, 40);
	data[static_cast<int>(Pickup::PickupID::GrenadeRefill)].action = std::bind(
		&Character::collectGrenades, _1, GRENADEPICKUPAMMOVALUE);

	data[static_cast<int>(Pickup::PickupID::FireSpread)].texture = TextureIDs::Entities;
	data[static_cast<int>(Pickup::PickupID::FireSpread)].textureRect = sf::IntRect(80, 64, 40, 40);
	data[static_cast<int>(Pickup::PickupID::FireSpread)].action = std::bind(&Character::increaseSpread, _1);

	data[static_cast<int>(Pickup::PickupID::FireRate)].texture = TextureIDs::Entities;
	data[static_cast<int>(Pickup::PickupID::FireRate)].textureRect = sf::IntRect(120, 64, 40, 40);
	data[static_cast<int>(Pickup::PickupID::FireRate)].action = std::bind(&Character::increaseFireRate, _1);

	return data;
}

std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(static_cast<int>(Particle::Type::ParticleCount));
	data[static_cast<int>(Particle::Type::Exhaust)].color = sf::Color(255, 255, 50);
	data[static_cast<int>(Particle::Type::Exhaust)].lifetime = sf::seconds(0.6f);

	data[static_cast<int>(Particle::Type::Smoke)].color = sf::Color(50, 50, 50);
	data[static_cast<int>(Particle::Type::Smoke)].lifetime = sf::seconds(4.0);

	return data;
}
