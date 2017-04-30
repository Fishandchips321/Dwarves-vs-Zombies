#pragma once
#include <string>
#include <queue>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <string>
#include "eventController.h"
#include "loginController.h"
#include "counter.h"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

/*
net message structure (client=>server)
timestamp - string 8 long <- total universal miliseconds
client ID (-1 if there isn't one) - int 4 long <- change to unsigned char
network control message - int 4 long <- change to unsigned char
paramaters - string ?? long

net message structure (server=>client)
timestamp - string 8 long <- total universal miliseconds
network control message - int 4 long <- change to unsigned char
paramaters - string ?? long

For the changes to unsigned char. they will need to be converted into signed ints somehow. static_cast?

*/

class netController
{
public:
	struct netMessage;
	netController();
	static bool connect(std::string address);
	static void update();
	static void updateLobby();
	static void updateGame();
	static void eventUpdate();
	static void send(std::string data);
	static bool nextMessage();
	static void sendControl(std::string data);
	static void sendControl(int ncm, std::string params = "");
	static void sendControl(netMessage message);
	static bool nextControlMessage();
	~netController();

	static boost::mutex gameRecLock, gameSendLock, controlRecLock, controlSendLock;

	enum class nState
	{
		DISCONNECTED,
		CONNECTING,
		CONNECTED,
		AUTHENTICATING,
		AUTHREPLY,
		SEND_USER_DATA,
		LOBBY,
		LOAD_GAME,
		PLAY_GAME,
		GAME_END,
		DISCONNECTING,
		QUICK_DISCONNECT,
		ERROR_CONNECTING,
		ERROR_DISCONNECTING,
		ERROR_SENDING,
		ERROR_RECIEVING,
		ERROR_SEND_RECIEVE
	};

	enum NCM
	{
		//control messages
		KEEPALIVE_PING,
		KEEPALIVE_PONG,
		UDP_CONNECT, //both TCP (server to client) and UDP (client to server)
		AUTHENTICATE, //client to server: client username, client login token // server to client: no paramaters
		USER_ID, //server to client: player ID
		LOBBY_PLAYER_UPDATE,
		LOAD_MAP, //server to client: map ID // client to server: no paramaters
		MAP_LOADED, //client to server: no paramaters
		MAP_LOAD_ERROR, //client to server: no paramaters
		PLAYER_SPAWN, //client to server: class ID
		PLAYER_MOB_SELECT,// client to server: class ID //for lobby
		DISCONNECT,
		GET_STATE,
		RESYNC_STATE,
		QUICK_DISCONNECT, //client to server: no paramaters
		//game messages //client to server: updates of client player. server to clients: updates of other players and resyncing of client player
		PLAYER_UPDATE, // client to server: x, y, x velocity, y velocity, flying (optional; bool)
		PLAYER_ATTACK, //client to server: equipped weapon (player hit will be determined by the server) // server to client: clientID (person attacking), equipped weapon (for animation), clientID (person being attacked; optional, only if a player was hit)
		PLAYER_PLACE, //client to server: blockID, x, y
		PLAYER_BREAK,
		PLAYER_DIE,
		PLAYER_DAMAGED
	};

	struct netMessage
	{
		int NCM;
		std::string paramaters;
		boost::posix_time::ptime timestamp; //23 chars for timestamp 2002-01-20 23:59:59.000
		std::string completeMessage;
	};

	static bool connected;
	static std::queue<std::string> gameRecieved;
	static std::queue<std::string> gameToSend;

	static int netID;

	static std::string currentMessage;
	static netMessage currentControlMessage;

private:
	static void netControlSend();
	static void netControlRecieve();
	static void netGameSend();
	static void netGameRecieve();
	static void connectUDP();
	static std::vector<std::string> splitString(std::string to_split);

	static boost::asio::io_service io_service;
	static boost::thread gameSendThread, gameRecieveThread, controlSendThread, controlRecieveThread;

	static udp::endpoint UDPEndpoint;
	static udp::socket USocket;
	static boost::mutex USLock;

	static tcp::resolver::iterator endpoint_iterator;
	static tcp::socket TSocket;
	static boost::mutex TSLock;

	static const std::string port;
	static nState state;

	static std::queue<netMessage> controlRecieved;
	static std::queue<std::string> controlToSend;

	static counter keepaliveTimer;
	static bool keepaliveSent;
};

