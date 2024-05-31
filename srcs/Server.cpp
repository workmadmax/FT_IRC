/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:45:11 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/30 17:34:13 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

Server::Server(int port, const std::string& password)
    : _port(port), _serverSocket(-1), _password(password)
{
    memset(&_serverAddr, 0, sizeof(_serverAddr));
}


Server::~Server()
{
	if (_serverSocket != -1) {
		close(_serverSocket);
		std::cout << "Connect socket error: " << std::endl;
	}
}

void	Server::initServer()
{
	//create socket
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == -1) {
		std::cerr << "Error ao criar o socket" << std::endl;
		exit(EXIT_FAILURE);
	}

	// conf address server
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	_serverAddr.sin_port = htons(_port);

	// bind socket to addrss
	if (bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) == -1){
		std::cerr << "Error : bind" << std::endl;
		close(_serverSocket);
		exit(EXIT_FAILURE);
	}

	if (listen(_serverSocket, 5) == -1) {
		std::cerr << "Error in listen" << std::endl;
		close(_serverSocket);
		exit(EXIT_FAILURE);
	}
}

void	Server::startServer()
{
	initServer();
	std::cout << "Server init port " << _port << std::endl;
	
	while (true) {
		struct sockaddr_in clientAddr;
		socklen_t clientLen = sizeof(clientAddr);
		int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
		if (clientSocket == -1) {
			std::cerr << "error ao aceitar o conexao" << std::endl;
			continue;
		}
		std::cout << "Cliente conectado: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
		close(clientSocket);
	}
}