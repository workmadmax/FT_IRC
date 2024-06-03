/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:33:39 by user42            #+#    #+#             */
/*   Updated: 2024/06/02 21:44:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

class SocketHandler
{
private:
	int		_server_socket;
	int		_epoll_fd;
public:
	SocketHandler();
	~SocketHandler();
	int		create_server_socket(int port);
	int		configure_epoll();
	void	change_events(int epoll_fd, int fd, uint32_t events, bool set);
	void	configure_server_address(struct sockaddr_in *server_address, int port);
	void	bind_server_socket(struct sockaddr_in server_address);
};