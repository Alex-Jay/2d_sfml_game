#pragma once
//Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

enum class TextureIDs{
	Entities, Water,
	TitleScreen, Buttons,
	Explosion, Grenade,
	Particle, FinishLine,
	PlayerMove, PlayerDeath,
	ZombieMove, ZombieDeath,
	MapTiles, Crate
};

enum class Shaders{BrightnessPass, DownSamplePass, GaussianBlurPass, AddPass};
enum class FontIDs{Main};
enum class MusicIDs{MenuTheme, MissionTheme};
enum class SoundEffectIDs{AlliedGunfire, EnemyGunfire, Explosion1, Explosion2, LaunchGrenade, CollectPickup, Button};


//Forward declaration and typedef
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, TextureIDs> TextureHolder;
typedef ResourceHolder<sf::Font, FontIDs> FontHolder;
typedef ResourceHolder<sf::Shader, Shaders> ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffectIDs> SoundBufferHolder;
