/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/08 11:07:14 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char **argv)
{
    Harl        harl;

    if (argc != 2)
    {
        std::cout << "INVALID ARGUMENTS\n";
        return (1);
    }
    std::string level(argv[1]);
    if (level == "exit")
    {
        std::cout << "\033[31;1m> Leaving the program...\n";
        return (0);
    }
    else if (!level.empty())
        harl.complain(level);
    return (0);
}
