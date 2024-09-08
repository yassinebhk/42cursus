/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 19:25:09 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    int     N;
    Zombie* zombie;

    N = 4;
    zombie = zombieHorde(N, "yassine");
    for(int i=0; i < N; i++)
        zombie[i].announce();
    delete[] zombie;
    return (0);
}
