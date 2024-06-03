/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:37:46 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/02 21:50:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SocketHandler.hpp"
#include "Client.hpp"
#include "Debug.hpp"
#include "libs.hpp"

class Server {
    public:
        Server();
        void    run();
    
    private:
        SocketHandler               socket_handler;
        std::map<int, std::string>  clients;
        Debug                       debug;

        void    disconnect_client(int client_socket);
        std::string                 int_to_string(int value);
};