#ifndef BOOK_MULTIPLAYERGAMESTATE_HPP
#define BOOK_MULTIPLAYERGAMESTATE_HPP

#include "State/State.hpp"
#include "Core/World.hpp"
#include "Entity/Player.hpp"
#include "Entity/Obstacle.hpp"
#include "Networking/GameServer.hpp"
#include "Networking/NetworkProtocol.hpp"
#include "Networking/PacketHandler.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>

class PacketHandler;

class MultiplayerGameState : public State
{
public:
	//MultiplayerGameState(StateStack & stack, Context context, bool isHost, sf::TcpSocket * socket);

	MultiplayerGameState(StateStack& stack, Context context, bool isHost);

	virtual void				draw();
	virtual bool				update(sf::Time dt);
	virtual bool				handleEvent(const sf::Event& event);
	virtual void				onActivate();
	void						onDestroy();


	void						disableAllRealtimeActions();
	sf::Int32 getLocalID();

	void spawnSelf();

	void spawnPlayers(std::vector<sf::Int32> playerIds);
	void spawnObstacles(std::vector<Obstacle::ObstacleData> obstacleData);
private:
	void						updateBroadcastMessage(sf::Time elapsedTime);
	void						handlePacket(sf::Int32 packetType, sf::Packet& packet);

	void broadcastMessage(sf::Packet & packet);

	void playerDisconnect(sf::Packet & packet);

	void playerEvent(sf::Packet & packet);

	void playerRealTimeChange(sf::Packet & packet);

	void spawnEnemy(sf::Packet & packet);

	void spawnObstacle(sf::Packet & packet);

	void spawnPickup(sf::Packet & packet);

	void updateClientState(sf::Packet & packet);

	sf::Vector2f assignCharacterSpawn(int Identifier);

	void handleCharacterCount(sf::Time dt);

	void handleRealTimeInput();

	void handleNetworkInput();

	void handleServerMessages(sf::Time dt);

	void handleGameActions();

	void handlePositionUpdates();


private:
	typedef std::unique_ptr<Player> PlayerPtr;


private:
	World						mWorld;
	sf::RenderWindow&			mWindow;
	sf::TcpSocket&				mSocket;
	uint16_t					mLocalPlayerID;
	TextureHolder&				mTextureHolder;

	std::map<int, PlayerPtr>	mPlayers;
	std::vector<sf::Int32>		mLocalPlayerIdentifiers;
	bool						mConnected;
	std::unique_ptr<GameServer> mGameServer;
	sf::Clock					mTickClock;

	std::vector<std::string>	mBroadcasts;
	sf::Text					mBroadcastText;
	sf::Time					mBroadcastElapsedTime;

	sf::Text					mLoadingText;

	sf::Text					mFailedConnectionText;
	sf::Clock					mFailedConnectionClock;

	bool						mActiveState;
	bool						mHasFocus;
	bool						mHost;
	bool						mGameStarted;
	bool mCharactersRecieved{};
	bool mObstaclesRecieved{};
	bool mServerNotifiedReady{};
	bool mSeverNotifiedBuilt{};
	sf::Time					mClientTimeout;
	sf::Time					mTimeSinceLastPacket;

	PacketHandler* mPacketHandler;
};

#endif // BOOK_MULTIPLAYERGAMESTATE_HPP