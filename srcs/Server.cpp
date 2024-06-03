/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:04:49 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 15:19:58 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

Server::Server(const char *port, const char *password) : _port(port), _password(password) {
	std::cout << YELLOW << "Inicializando server ..." << RESET << std::endl;
	init_server();
};

Server::~Server() {
	close(_server_fd);
};

void	Server::init_server()
{
	int	yes = 1;
	addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, _port, &hints, &res) != 0) {
		std::cerr << "getaddrinfo failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	_server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (_server_fd == -1) {
		std::cerr << "socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		std::cerr << "setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if (bind(_server_fd, res->ai_addr, res->ai_addrlen) == -1) {
		close(_server_fd);
		std::cerr << "bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(res);
	
	if (listen(_server_fd, 10) == -1) {
		close(_server_fd);
		std::cerr << "listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	fcntl(_server_fd, F_SETFL, O_NONBLOCK);
	
	pollfd pdf = { _server_fd, POLLIN, 0 };
	_poll_fds.push_back(pdf);

	std::cout << GREEN << "Server inicializado com sucesso!" << RESET << std::endl;
};