/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:45:11 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 13:50:58 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

void Server::run() {
    int server_socket = socket_handler.create_server_socket(8080);
    int epoll_fd = socket_handler.configure_epoll();
    std::cout << "Server running on port 8080 ..." << std::endl;
    socket_handler.change_events(epoll_fd, server_socket, EPOLLIN, true);

    while (true) {
        struct epoll_event events[MAX_EVENTS];
        int n_event = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < n_event; i++) {
            if (events[i].data.fd == server_socket) {
                int client_socket = accept(server_socket, NULL, NULL);
                socket_handler.change_events(epoll_fd, client_socket, EPOLLIN, true);
                clients[client_socket] = "";
            } else {
                int client_socket = events[i].data.fd;
                char buffer[1024];
                int bytes_read = read(client_socket, buffer, 1024);
                if (bytes_read == 0) {
                    socket_handler.change_events(epoll_fd, client_socket, 0, false); // remove from epoll
                    disconnect_client(client_socket);
                } else {
                    clients[client_socket] += std::string(buffer, bytes_read);
                    if (clients[client_socket].find("\n") != std::string::npos) {
                        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\nHello, World!";
                        write(client_socket, response.c_str(), response.size());
                        socket_handler.change_events(epoll_fd, client_socket, 0, false); // remove from epoll
                        disconnect_client(client_socket);
                    }
                }
            }
        }
    }
};

void    Server::disconnect_client(int client_socket) {
    clients.erase(client_socket);
    close(client_socket);
};

std::string Server::int_to_string(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
};

Server::Server() {
    std::cout << "Server created" << std::endl;
};