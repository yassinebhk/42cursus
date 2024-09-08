/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 19:25:51 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP_
#define ZOMBIE_HPP_

#include <iostream>

class Zombie
{
private:
	std::string name;
public:
	Zombie();
	Zombie(std::string arg);
	~Zombie();
	void announce(void) const;
	void set_name(const std::string name);
};
	Zombie* zombieHorde(int N, std::string str);


#endif
