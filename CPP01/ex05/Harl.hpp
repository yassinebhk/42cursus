/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/08 10:33:08 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP_
#define HARL_HPP_

#include <iostream>
#include <limits>


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


#endif
