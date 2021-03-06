#ifndef BOOK_SOUNDNODE_HPP
#define BOOK_SOUNDNODE_HPP

#include "Node/SceneNode.hpp"
#include "Structural/ResourceIdentifiers.hpp"


class SoundPlayer;

class SoundNode : public SceneNode
{
	public:
		explicit				SoundNode(SoundPlayer& player);
		void					playSound(SoundEffect::ID sound, sf::Vector2f position);

		virtual unsigned int	getCategory() const;


	private:
		SoundPlayer&			mSounds;
};

#endif // BOOK_SOUNDNODE_HPP
