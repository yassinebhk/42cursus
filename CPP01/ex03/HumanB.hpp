/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:14 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 22:40:14 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HumanB_HPP_
#define HumanB_HPP_

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
private:
	Weapon		*weapon;
	std::string name;
public:
	HumanB();
	~HumanB();
	HumanB(const std::string &name);
	void setWeapon(Weapon &weapon);
	void attack();
};

#endif
