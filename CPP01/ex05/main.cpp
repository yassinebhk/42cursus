/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/07 12:52:15 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main()
{
    Harl        harl;
    std::string level;
    
    while (1)
    {
        std::cout << "\n\033[37;1m> Please, select a level : \n";
        std::cout << "  -> DEBUG\n"
                << "  -> WARNING\n"
                << "  -> INFO\n"
                << "  -> ERROR\n"
                << "  -> exit\n\033[0;90m";
        std::cin >> level;
        if (std::cin.eof()) 
        {
            std::cout << "\033[31;1m> Detected EOF, exiting...\n";
            break;
        }
        if (level == "exit")
        {
            std::cout << "\033[31;1m> Leaving the program...\n";
            break;
        }
        else if (!std::cin.fail() && !level.empty())
            harl.complain(level);
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return (0);
}
