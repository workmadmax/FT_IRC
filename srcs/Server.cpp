/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:45:11 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/31 14:08:31 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

Server::Server() {
    server_socket = create_server_socket();
    struct sockaddr_in server_addr;
    configure_server_address(server_addr);
    bind_server_socket();
    listen_on_server_socket();
    epoll_fd = configure_epoll();
}

void Server::exit_with_perror(const std::string &msg) {
    std::cerr << msg;
    exit(1);
}

void Server::change_events(int fd, uint32_t events, int op) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    if (epoll_ctl(epoll_fd, op, fd, &ev) == -1)
        exit_with_perror("epoll_ctl error\n" + std::string(strerror(errno)));
}

void Server::disconnect_client(int client_socket) {
    close(client_socket);
    clients.erase(client_socket);
}

int Server::create_server_socket() {
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        exit_with_perror("socket() error\n" + std::string(strerror(errno)));
    return sock;
}

void Server::configure_server_address(struct sockaddr_in &server_addr) {
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);
}

void Server::bind_server_socket() {
    struct sockaddr_in server_addr;
    configure_server_address(server_addr);
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        exit_with_perror("bind() error\n" + std::string(strerror(errno)));
}

void Server::listen_on_server_socket() {
    if (listen(server_socket, 5) == -1)
        exit_with_perror("listen() error\n" + std::string(strerror(errno)));
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
}

int Server::configure_epoll() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
        exit_with_perror("epoll_create1() error\n" + std::string(strerror(errno)));
    return epoll_fd;
}

void Server::run() {
    struct epoll_event event_list[MAX_EVENTS];
    
    change_events(server_socket, EPOLLIN, EPOLL_CTL_ADD);
    debug.info("Echo server started");

    while (true) {
        int new_events = epoll_wait(epoll_fd, event_list, MAX_EVENTS, -1);
        if (new_events == -1)
            exit_with_perror("epoll_wait error\n" + std::string(strerror(errno)));

        for (int i = 0; i < new_events; ++i) {
            struct epoll_event* curr_event = &event_list[i];

            if (curr_event->events & EPOLLERR || curr_event->events & EPOLLHUP) {
                if (curr_event->data.fd == server_socket)
                    exit_with_perror("server socket error");
                else {
                    debug.error("Client socket error");
                    disconnect_client(curr_event->data.fd);
                }
            } else if (curr_event->events & EPOLLIN) {
                if (curr_event->data.fd == server_socket) {
                    int client_socket = accept(server_socket, NULL, NULL);
                    if (client_socket == -1)
                        exit_with_perror("accept error\n" + std::string(strerror(errno)));
                    debug.info("Accepted new client: " + int_to_string(client_socket));
                    fcntl(client_socket, F_SETFL, O_NONBLOCK);

                    change_events(client_socket, EPOLLIN | EPOLLOUT, EPOLL_CTL_ADD);
                    clients[client_socket] = "";
                } else if (clients.find(curr_event->data.fd) != clients.end()) {
                    char buf[1024];
                    int n = read(curr_event->data.fd, buf, sizeof(buf));

                    if (n <= 0) {
                        if (n < 0)
                            debug.error("Client read error");
                        disconnect_client(curr_event->data.fd);
                    } else {
                        buf[n] = '\0';
                        clients[curr_event->data.fd] += buf;
                        debug.info("Received data from " + int_to_string(curr_event->data.fd) + ": " + clients[curr_event->data.fd]);
                    }
                }
            } else if (curr_event->events & EPOLLOUT) {
                std::map<int, std::string>::iterator it = clients.find(curr_event->data.fd);
                if (it != clients.end()) {
                    if (!clients[curr_event->data.fd].empty()) {
                        int n = write(curr_event->data.fd, clients[curr_event->data.fd].c_str(), clients[curr_event->data.fd].size());
                        if (n == -1) {
                            debug.error("Client write error");
                            disconnect_client(curr_event->data.fd);
                        } else {
                            clients[curr_event->data.fd].clear();
                        }
                    }
                }
            }
        }
    }
}

std::string Server::int_to_string(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}