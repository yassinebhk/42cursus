/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 20:27:00 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie* new_zombie = newZombie("yassine");
    new_zombie->announce();
    new_zombie->randomChump("paquito");
    delete new_zombie;
    return (0);
}
