/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/05 20:52:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
int main()
{
    std::string message = "HI THIS BRAIN";
    std::string *stringPTR = &message; 
    std::string &stringREF = message; 

    std::cout << std::setw(12) << std::right <<"|  memory adress  |"
              << std::setw(12) << std::right <<"     value      |\n"
              << std::setw(12) << "------------------------------------\n"
              << "| " << std::setw(12) << std::right << &message   << "  | "
                      << std::setw(12) << std::right << message    << "  | " << std::endl
              << "| " << std::setw(12) << std::right << stringPTR  << "  | "
                      << std::setw(12) << std::right << *stringPTR << "  | " << std::endl
              << "| " << std::setw(12) << std::right << &stringREF << "  | "
                      << std::setw(12) << std::right << stringREF  << "  | " << std::endl;
    return (0);
}
