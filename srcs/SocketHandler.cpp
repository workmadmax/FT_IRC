/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:39:21 by user42            #+#    #+#             */
/*   Updated: 2024/06/03 13:58:03 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketHandler.hpp"

SocketHandler::SocketHandler()
{
	_server_socket = -1;
	_epoll_fd = -1;
};

SocketHandler::~SocketHandler()
{
	if (_server_socket != -1)
		close(_server_socket);
	if (_epoll_fd != -1)
		close(_epoll_fd);
};


int		SocketHandler::configure_epoll()
{
	int		epoll_fd;

	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		std::cerr << "Error: epoll creation failed" << std::endl;
		return (-1);
	}
	_epoll_fd = epoll_fd;
	return (epoll_fd);
};

void SocketHandler::change_events(int epoll_fd, int fd, uint32_t events, bool set)
{
    struct epoll_event event;

    event.events = events;
    event.data.fd = fd;
    if (set)
    {
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1)
            std::cerr << "Error: epoll_ctl ADD failed with error: " << std::endl;
			exit(1);
    }
    else
    {
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event) == -1)
            std::cerr << "Error: epoll_ctl DEL failed with error: " << std::endl;
    }
};

void	SocketHandler::configure_server_address(struct sockaddr_in *server_address, int port)
{
	server_address->sin_family = AF_INET;
	server_address->sin_addr.s_addr = INADDR_ANY;
	server_address->sin_port = htons(port);
};

bool SocketHandler::create_server_socket(int port)
{
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket == -1)
    {
        std::cerr << "Error: socket creation failed" << std::endl;
        return false;
    }
    struct sockaddr_in server_address;
    configure_server_address(&server_address, port);
    if (!bind_server_socket(server_address))
    {
        return false;
    }
    return true;
};

bool SocketHandler::bind_server_socket(struct sockaddr_in &server_address)
{
    if (bind(_server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error: bind failed" << std::endl;
        close(_server_socket);
        _server_socket = -1;
        return false;
    }
    return true;
};