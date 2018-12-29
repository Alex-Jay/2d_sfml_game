#pragma once
//Entity/Scene node category, used to dispatch messages

enum class Category
{
	None = 0,
	SceneAirLayer = 1 << 0,
	PlayerCharacter = 1 << 1,
	AlliedCharacter = 1 << 2,
	EnemyCharacter = 1 << 3,
	Pickup = 1 << 4,
	AlliedProjectile = 1 << 5,
	EnemyProjectile = 1 << 6,
	ParticleSystem = 1 << 7,
	SoundEffect = 1 << 8,
	Explosion = 1 << 10,
	Obstacle = 1 << 11,

	Character = PlayerCharacter | AlliedCharacter | EnemyCharacter,
	Projectile = AlliedProjectile | EnemyProjectile
};
