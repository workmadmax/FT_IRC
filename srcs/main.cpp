/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:55:43 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/03 17:51:38 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Libs.hpp"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./server <port> <password>" << std::endl;
        return (EXIT_FAILURE);
    }
    std::string port = argv[1];
    std::string password = argv[2];
    Server server(port.c_str(), password.c_str());
    server.run();
    
    return 0;
};