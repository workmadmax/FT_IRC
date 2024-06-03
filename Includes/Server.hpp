/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:07:13 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 17:41:06 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Libs.hpp"
# include "Client.hpp"

class Server
{
	public:
		Server(const char *port, const char *password);
		~Server();
		void run();

	private:
		int							_server_fd;
		const char					*_port;
		const char					*_password;
		std::vector<pollfd>			_poll_fds;
		std::map<int, Client>		_clients;

		// server functions
		void						init_server();
		void						handle_new_connection();
		//void						remove_client();
		//void						send_message(int client, std::string message);
		//void						process_message(int client, std::string message);
		void						handle_client_msg(int client_fd);
		void						remove_client(int client_fd);
};