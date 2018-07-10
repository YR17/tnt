#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include <SFML/Network.hpp>

#include <GameModel.hpp>
#include <string>
#include <mutex>
#include <thread>

class INetworkListener {
	public:
		virtual void onMessage(std::string) = 0; 
};

class NetworkManager {
public:
	NetworkManager();
	NetworkManager(const NetworkManager& ob);
	~NetworkManager();
	
	bool connect();
	void send(std::string msg);
	void setListener(INetworkListener* listener);
	void unsetListener();
	void listen();
	bool isError();
private:
	INetworkListener* listener;
	std::mutex socket_lock;
	std::mutex listener_lock;
	std::thread* listening;
	sf::TcpSocket socket;
	bool error;
};

#endif //NETWORK_MANAGER_HPP