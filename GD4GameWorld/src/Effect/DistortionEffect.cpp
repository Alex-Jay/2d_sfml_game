#include "DistortionEffect.hpp"
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/System/Clock.hpp>
#include "Utility.hpp"


// Frag File and tutorial from Here https://www.lucidarme.me/sfml-distorsion-shader/

DistortionEffect::DistortionEffect()
	: mDistortionFactor(0.05f)
	, mRiseFactor(0.1f)
{
	//mShaders.load(Shaders::Distortion, "Media/Shaders/Distortion.frag", sf::Shader::Fragment);
	if (!mShader.loadFromFile("Media/Shaders/Distortion.frag", sf::Shader::Fragment))
	{
		throw std::runtime_error("Failed to load Media/Shaders/Distortion.frag");
	}
	mShaders.load(Shaders::AddPass, "Media/Shaders/Fullpass.vert", "Media/Shaders/Add.frag");
}

void DistortionEffect::setTextureMap(const TextureHolder & textures)
{

	mDistortionMap = textures.get(TextureIDs::DistortionMap);
	mDistortionMap.setRepeated(true);
	mDistortionMap.setSmooth(true);
	mShader.setUniform("currentTexture", sf::Shader::CurrentTexture);
	mShader.setUniform("distortionMapTexture", mDistortionMap);
}

void DistortionEffect::apply(const sf::RenderTexture& input, sf::RenderTarget& output)
{

	mSprite.setTexture(input.getTexture());

	centreOrigin(mSprite);

	mShader.setUniform("time", mTimer.getElapsedTime().asSeconds());
	mShader.setUniform("distortionFactor", mDistortionFactor);
	mShader.setUniform("riseFactor", mRiseFactor);

	output.clear();
	mSprite.setPosition(output.getSize().x / 2., output.getSize().y / 2.);
	output.draw(mSprite, &mShader);

	//prepareTextures(input.getSize());

	//distort(mFirstPassTextures[0]);

	//distort(mSecondPassTextures[0]);

	//add(mFirstPassTextures[0], mSecondPassTextures[0], mFirstPassTextures[1]);
	//mFirstPassTextures[1].display();
	//add(input, mFirstPassTextures[1], output);
}


void DistortionEffect::prepareTextures(sf::Vector2u size)
{
	if (mDistortionTexture.getSize() != size)
	{
		mDistortionTexture.create(size.x, size.y);
		//mDistortionTexture.setSmooth(true);

		mFirstPassTextures[0].create(size.x / 2, size.y / 2);
		//mFirstPassTextures[0].setSmooth(true);
		mFirstPassTextures[1].create(size.x / 2, size.y / 2);
		mFirstPassTextures[1].setSmooth(true);

		mSecondPassTextures[0].create(size.x / 4, size.y / 4);
		//mSecondPassTextures[0].setSmooth(true);
		mSecondPassTextures[1].create(size.x / 4, size.y / 4);
		mSecondPassTextures[1].setSmooth(true);
	}
}

void DistortionEffect::distort( sf::RenderTexture& output)
{

	mShader.setUniform("time", mTimer.getElapsedTime().asSeconds());
	mShader.setUniform("distortionFactor", mDistortionFactor);
	mShader.setUniform("riseFactor", mRiseFactor);
	applyShader(mShader, output);
	output.display();
}


void DistortionEffect::add(const sf::RenderTexture& source, const sf::RenderTexture& distort, sf::RenderTarget& output)
{
	sf::Shader& adder = mShaders.get(Shaders::AddPass);

	adder.setUniform("source", source.getTexture());
	adder.setUniform("distort", distort.getTexture());
	applyShader(adder, output);
}
