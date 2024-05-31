/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:16:04 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/31 10:22:25 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(const std::string& nickname, int fd)
: _nickname(nickname), _fd(fd), _pass(0), _nick(0), _user(0)
{
};

void	Client::setJoinedChannel(const std::string& channel_name)
{
	this->_joined_channel.push_back(channel_name);
};

void	Client::setPass(bool check) { this->_pass = check; }
void	Client::setNick(bool check) { this->_pass = check; }
void	Client::setUser(bool check) { this->_pass = check; }
void	Client::setNickname(const std::string& nickname) { this->_nickname = nickname; }