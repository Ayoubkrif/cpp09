/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitcoin.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:49:35 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include <map>
#include <string>
std::map<std::string, std::string>	csvReader(const char* path);
std::string	nbrToString(size_t nbr);
