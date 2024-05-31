/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:37:46 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/31 10:02:31 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "libs.hpp"

class Server
{
	public:
		Server(int port, const std::string& password);
		~Server();
		void				startServer();
	private:
		int					_port;
		int					_serverSocket;
		void				initServer();
		std::string			_password;
		struct sockaddr_in	_serverAddr;
};