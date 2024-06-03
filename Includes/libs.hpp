/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:01:39 by mdouglas          #+#    #+#             */
/*   Updated: 2024/06/02 21:49:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstring>
# include <iostream>
# include <cstdlib>
# include <map>
# include <vector>
# include <algorithm>
# include <fcntl.h>
# include <cerrno>
# include <sstream>

# define MAX_EVENTS 10