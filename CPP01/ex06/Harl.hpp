/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/08 11:06:23 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP_
#define HARL_HPP_

#include <iostream>
#include <limits>
#include <string>

enum		level
{
	DEBUG = 0,
	INFO = 1, 
	WARNING = 2,
	ERROR = 3	
};

class Harl
{
private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

public:
	Harl();
	~Harl();
	void complain(std::string level);
};

int	get_level(const std::string &level);

#endif
