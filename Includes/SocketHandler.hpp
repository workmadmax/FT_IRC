/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:33:39 by user42            #+#    #+#             */
/*   Updated: 2024/06/03 13:58:43 by mdouglas         ###   ########.fr       */
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
	bool	create_server_socket(int port);
	int		configure_epoll();
	void	change_events(int epoll_fd, int fd, uint32_t events, bool set);
	void	configure_server_address(struct sockaddr_in *server_address, int port);
	bool	bind_server_socket(struct sockaddr_in &server_address);
};