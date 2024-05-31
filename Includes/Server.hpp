/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:37:46 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/31 14:09:03 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "libs.hpp"

class Server {
public:
    Server();
    void	run();

private:
    int							server_socket;
    int							epoll_fd;
    std::map<int, std::string>	clients;
    Debug                       debug;

    void						exit_with_perror(const std::string &msg);
    void						change_events(int fd, uint32_t events, int op);
    void						disconnect_client(int client_socket);
    void						configure_server_address(struct sockaddr_in &server_addr);
    void						bind_server_socket();
    void						listen_on_server_socket();
    int							create_server_socket();
    int							configure_epoll();
    
    std::string                 int_to_string(int value);
};