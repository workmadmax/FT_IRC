/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:04:49 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 17:56:32 by mdouglas         ###   ########.fr       */
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

void	Server::run()
{
	while (true) {
		int ret = poll(_poll_fds.data(), _poll_fds.size(), -1);
		if (ret == -1) {
			std::cerr << "poll failed" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (size_t i = 0; i < _poll_fds.size(); i++) {
			if (_poll_fds[i].revents & POLLIN) {
				if (_poll_fds[i].fd == _server_fd) {
					handle_new_connection();
				}
				else {
					handle_client_msg(_poll_fds[i].fd);
				}
			}
		}
	}
};

void	Server::handle_new_connection()
{
	sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int client_fd = accept(_server_fd, (sockaddr*)&client_addr, &client_addr_len);
	if (client_fd == -1) {
		std::cerr << "accept failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	
	pollfd pdf = { client_fd, POLLIN, 0 };
	_poll_fds.push_back(pdf);
	std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
	_clients[client_fd] = Client(client_fd);
};


void Server::handle_client_msg(int client_fd) {
    std::string message = _clients[client_fd].receive_message();
    if (message.empty()) {
        std::cerr << "Failed to receive message or client disconnected" << std::endl;
        remove_client(client_fd);
    }
    else {
        std::cout << "Received message from client " << client_fd << ": " << message << std::endl;
        bool send_result = _clients[client_fd].send_message(message);
        if (!send_result) {
            std::cerr << "Failed to send message" << std::endl;
            remove_client(client_fd);
        } else {
            std::cout << "Message sent successfully to client " << client_fd << std::endl;
        }
    }
};

void Server::remove_client(int client_fd) {
    close(client_fd);
    _clients.erase(client_fd);
    for (std::vector<pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); ++it) {
        if (it->fd == client_fd) {
            _poll_fds.erase(it);
            break;
        }
    }
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