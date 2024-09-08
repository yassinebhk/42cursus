/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:50:02 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/08 10:51:00 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void Harl::debug(void)
{
    std::cout << "\033[32;1m[ DEBUG ]\n";
	std::cout << "\033[32;1mI love having extra bacon for my 7XL-double-cheese-triple-\
	pickle-special-ketchup burger. I really do!\n";
}

void Harl::info(void)
{
    std::cout << "\033[34;1m[ INFO ]\n";
	std::cout << "\033[34;1mI cannot believe adding extra bacon costs more money. You didn't put\
	enough bacon in my burger! If you did, I wouldn't be asking for more!\n";
}

void Harl::warning(void)
{
    std::cout << "\033[33;1m[ WARNING ]\n";
	std::cout << "\033[33;1mI think I deserve to have some extra bacon for free. I've been coming for\
	years whereas you started working here since last month.\n";
}

void Harl::error(void)
{
    std::cout << "\033[31;1m[ ERROR ]\n";
	std::cout << "\033[31;1mThis is unacceptable! I want to speak to the manager now.\n";
}

int	get_level(const std::string &level)
{
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    
    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
            return (i);
    }
    return (-1);
}

void Harl::complain(std::string level)
{
    void (Harl::*complaints[])(void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
    switch (get_level(level))
    {
        case DEBUG:
            for (int i = get_level(level); i < 4; i++)
            {
                (this->*complaints[i])();
                std::cout << "\n";
            }
            break;
        case INFO:
            for (int i = get_level(level); i < 4; i++)
            {
                (this->*complaints[i])();
                std::cout << "\n";
            }
            break;
        case WARNING:
            for (int i = get_level(level); i < 4; i++)
            {
                (this->*complaints[i])();
                std::cout << "\n";
            }
            break;
        case ERROR:
            for (int i = get_level(level); i < 4; i++)
            {
                (this->*complaints[i])();
                std::cout << "\n";
            }
            break;    
        default:
            std::cout << "\033[37;1m[ Probably complaining about insignificant problems ]\n";
            break;
    }
}

