
#include <iostream>
using namespace std;
#include <NetworkManager.hpp>
#include <cstring>

NetworkManager::NetworkManager():
	listening(nullptr),
	error(false) {
}

NetworkManager::NetworkManager(const NetworkManager& ob) {

}

NetworkManager::~NetworkManager() {
	listening->join();
	delete listening;
}

bool NetworkManager::connect() {
	cout << " start " << endl;
	sf::Socket::Status status = socket.connect("192.168.1.106", 8080);
	if (status != sf::Socket::Done) {
		cout << "Error:" << status << endl;
		error = true;
		return false;
	} else {
		cout << "connected" << endl;
		listening = new std::thread(&NetworkManager::listen, this);
		return true;
	}
}

void NetworkManager::send(std::string msg) {
	std::lock_guard<std::mutex> lock(socket_lock);
	sf::Socket::Status status = socket.send(msg.c_str(), msg.size());
	if (sf::Socket::Done != status) {
	  //error
	}
	cout << "Message sent: " << msg << endl;
}

void NetworkManager::setListener(INetworkListener* _listener) {
	std::lock_guard<std::mutex> lock(listener_lock);
	listener = _listener;
}

void NetworkManager::unsetListener() {
	std::lock_guard<std::mutex> lock(listener_lock);
	listener = nullptr;
}

void NetworkManager::listen() {
	while (true) {
		char msg_buf[1024];
		memset(msg_buf, 0, sizeof(msg_buf));
		std::size_t size;
		sf::Socket::Status status = socket.receive(msg_buf, 1024, size);
		if (sf::Socket::Done != status) {
			cout << "Error: " << status << endl;
			error = true;
			return;
		} else {
			std::string msg(msg_buf, size);
			cout << "Receive message (" << size << "):" << msg << endl;
			{
				std::lock_guard<std::mutex> lock(listener_lock);
				if (nullptr != listener) {
					std::size_t pos = msg.find('}');
					while (pos < msg.size()){
						std::string ob = msg.substr(0, pos);
						listener->onMessage(msg);
						msg = msg.substr(pos);
						pos = msg.find('}');	
					}
				}	
			}
		}
	}
}

bool NetworkManager::isError() {
	return error;
}