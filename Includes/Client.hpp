/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:07:31 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/31 10:23:23 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "libs.hpp"

class Client
{
	public:
		void	setPass(bool check);
		void	setNick(bool check);
		void	setUser(bool check);
		void	setNickname(const std::string& nickname);
		void	setJoinedChannel(const std::string& channel_name);
		Client(const std::string& name, int fd);

	private:
		std::string	_nickname;
		int							_fd;
		bool						_pass;
		bool						_nick;
		bool						_user;
		std::vector<std::string>	_joined_channel;
};