#ifndef BOOK_NETWORKPROTOCOL_HPP
#define BOOK_NETWORKPROTOCOL_HPP

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>


const unsigned short ServerPort = 5000;

namespace Server
{
	// Packets originated in the server
	enum PacketType
	{
		BroadcastMessage,	// format: [Int32:packetType] [string:message]
		SelfJoinLobby,
		JoinLobby,
		LeaveLobby,
		LobbyState,
		SetCharacters,
		SetObstacles,
		InitialState,
		PlayerEvent,
		PlayerRealtimeChange,
		PlayerLobbyConnect,
		PlayerLobbyDisconnect,
		PlayerConnect,
		PlayerDisconnect,
		PlayerDied,
		AcceptCoopPartner,
		SpawnEnemy,
		SpawnObstacle,
		SpawnPickup,
		UpdateClientState,
		MissionSuccess,
		LoadGame,
		StartGame
	};
}

namespace Client
{
	// Packets originated in the client
	enum PacketType
	{
		StartGame,
		LoadGame,
		Ready,
		WorldBuilt,
		PlayerEvent,
		PlayerRealtimeChange,
		RequestCoopPartner,
		PositionUpdate,
		HitpointUpdate,
		GameEvent,
		Quit
	};
}

namespace PlayerActions
{
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		ActionCount
	};
}

namespace GameActions
{
	enum Type
	{
		EnemyExplode,
	};

	struct Action
	{
		Action()
		{ // leave uninitialized
		}

		Action(Type type, sf::Vector2f position)
		: type(type)
		, position(position)
		{
		}

		Type			type;
		sf::Vector2f	position;
	};
}

#endif // BOOK_NETWORKPROTOCOL_HPP
