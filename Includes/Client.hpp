/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:07:31 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/02 21:33:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libs.hpp"

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