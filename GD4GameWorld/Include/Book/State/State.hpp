#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "State/StateIdentifiers.hpp"
#include "Structural/ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf {
	class RenderWindow;
	class TcpSocket;
}

class StateStack;
class MusicPlayer;
class SoundPlayer;
class KeyBinding;

class State {
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context {
		Context(sf::RenderWindow& window, sf::TcpSocket& socket, uint16_t& localID, TextureHolder& textures, FontHolder& fonts,
			MusicPlayer& music, SoundPlayer& sounds, KeyBinding& keys);

		sf::RenderWindow* window;
		sf::TcpSocket* socket;
		sf::Int32* localID;
		TextureHolder* textures;
		FontHolder* fonts;
		MusicPlayer* music;
		SoundPlayer* sounds;
		KeyBinding* keys;
	};

	void setLocalID(sf::Int32 id);
	sf::Int32 getLocalID();

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

	virtual void onActivate();
	virtual void onDestroy();


	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

	

private:
	StateStack* mStack;
	Context mContext;
};

#endif // BOOK_STATE_HPP
