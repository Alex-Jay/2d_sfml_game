#ifndef BOOK_GAMESERVER_HPP
#define BOOK_GAMESERVER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <Entity/Obstacle.hpp>

#include <vector>
#include <memory>
#include <map>

class GameServer {
public:
	explicit GameServer(sf::Vector2f battlefieldSize);
	~GameServer();

	void onDestroy();

	void notifyPlayerJoin(sf::Int32 characterIdentifier);
	void loadGame();
	void playerEvent(sf::Packet packet);
	void playerRealTimeChange(sf::Packet packet);
	void positionUpdate(sf::Packet packet);
	void notifyPlayerRealtimeChange(sf::Int32 characterIdentifier, sf::Int32 action, bool actionEnabled);
	void notifyPlayerEvent(sf::Int32 characterIdentifier, sf::Int32 action);
	void notifyLoadGame();
	void notifyStartGame();
	void notifyPlayerDied(sf::Int32 characterIdentifier);

private:
	// A GameServerRemotePeer refers to one instance of the game, may it be local or from another computer
	struct RemotePeer {
		RemotePeer();

		sf::TcpSocket socket;
		sf::Time lastPacketTime;
		std::vector<sf::Int32> characterIdentifiers;
		bool ready;
		bool timedOut;
	};

	// Structure to store information about current character state
	struct characterInfo {
		sf::Vector2f position;
		float rotation;
		sf::Int32 hitpoints;
		sf::Int32 missileAmmo;
		std::map<sf::Int32, bool> realtimeActions;
	};

	// Unique pointer to remote peers
	typedef std::unique_ptr<RemotePeer> PeerPtr;
public:
	void gameEvent(sf::Packet packet, RemotePeer& receivingPeer);
	void hitpointUpdate(sf::Packet packet);
private:
	void setListening(bool enable);
	void executionThread();
	void tick();
	std::vector<sf::Vector2f> getObjectSpwanPoints(int obstacleCount);
	std::vector<Obstacle::ObstacleData> getObjectData(int obstacleCount);
	void buildWorld();
	sf::Time now() const;

	void handleIncomingPackets();
	void handleIncomingPacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& detectedTimeout);
	void handleIncomingConnections();
	void handleDisconnections();

	void informWorldState(sf::TcpSocket& socket);
	void broadcastMessage(const std::string& message);
	void RemoveDestroyedCharacters();
	void SetInitialWorldState();
	void sendCharacters();
	void spawnObstacles();
	void setObstacles();
	void spawnEnemys();
	void sendToAll(sf::Packet& packet);
	void updateClientState();

private:
	sf::Thread mThread;
	sf::Clock mClock;
	sf::TcpListener mListenerSocket;
	bool mListeningState;
	sf::Time mClientTimeoutTime;

	std::size_t mMaxConnectedPlayers;
	std::size_t mConnectedPlayers;

	float mWorldHeight;
	sf::FloatRect mBattleFieldRect;
	float mBattleFieldScrollSpeed;

	std::size_t mCharacterCount;
	std::map<sf::Int32, characterInfo> mCharacterInfo;

	std::vector<PeerPtr> mPeers;
	sf::Int32 mCharacterIdentifierCounter;
	bool mWaitingThreadEnd;

	sf::Time mLastSpawnTime;
	sf::Time mTimeForNextSpawn;

	bool obstaclesSpawned{};

	int8_t mZombieCount;

	std::vector<int16_t> mPlayerIDs;

	bool mGameStarted{};
	bool mAllClientsReady{};

	int16_t mClientReadyCount;
	bool buildWorldPacketSent{};
	bool worldBuiltPacketRecieved{};
	bool mCharactersRecieved{};
};

#endif // BOOK_GAMESERVER_HPP