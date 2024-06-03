/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:50:00 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 18:10:49 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
	: _socket_fd(0), _nickname(""), _username(""), _hostname(""), _is_authenticate(false)
{
};

Client::Client(int socket_fd)
	: _socket_fd(socket_fd), _nickname(""), _username(""), _hostname(""), _is_authenticate(false)
{
};

Client::~Client()
{
	close(_socket_fd);
};

// getters

std::string	Client::getNickname() const
{
	return _nickname;
};

std::string	Client::getUsername() const
{
	return _username;
};

std::string	Client::getHostname() const
{
	return _hostname;
};

bool	Client::isAuthenticated() const
{
	return _is_authenticate;
};

// setters

void	Client::setNickname(std::string nickname)
{
	_nickname = nickname;
};

void	Client::setUsername(std::string username)
{
	_username = username;
};

void	Client::setHostname(std::string hostname)
{
	_hostname = hostname;
};

void	Client::authenticate()
{
	_is_authenticate = true;
};

// communication methods

bool Client::send_message(std::string message) const
{
    size_t total_sent = 0;
    while (total_sent < message.size()) {
        ssize_t sent = send(_socket_fd, message.c_str() + total_sent, message.size() - total_sent, 0);
        if (sent == -1) {
            perror("send failed");
            return (false);
        }
        total_sent += sent;
    }
	std::cout << "message sent: " << message << std::endl;
    return (true);
};

std::string	Client::receive_message() const
{
	char buffer[1024];
	int bytes = recv(_socket_fd, buffer, sizeof(buffer) -1, 0);
	if (bytes <= 0) {
		if (bytes == 0) {
			std::cerr << "client disconnected" << std::endl;
		} else {
			std::cerr << "recv failed" << std::endl;
			throw std::runtime_error("recv failed execption");
		}
		return "";
	}
	buffer[bytes] = '\0';
	return std::string(buffer);
};