/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:46:33 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 17:20:09 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Libs.hpp"

class Client
{
	private:
		int			_socket_fd;
		std::string	_nickname;
		std::string	_username;
		std::string	_hostname;
		bool		_is_authenticate;
	public:
		Client();
		Client(int socket_fd);
		~Client();
		
		// getters
		std::string	getNickname() const;
		std::string getUsername() const;
		std::string getHostname() const;
		bool		isAuthenticated() const;

		// setters
		void		setNickname(std::string nickname);
		void		setUsername(std::string username);
		void		setHostname(std::string hostname);
		void		authenticate();

		// communication methods
		bool		send_message(std::string message) const;
		std::string	receive_message() const;
		
};