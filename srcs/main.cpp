/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouglas <mdouglas@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:01:28 by mdouglas          #+#    #+#             */
/*   Updated: 2024/05/30 17:03:54 by mdouglas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0] << " <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}
	int port = std::atoi(argv[1]);
	std::string password = argv[2];

	Server server(port, password);
	server.startServer();
	return (0);
}