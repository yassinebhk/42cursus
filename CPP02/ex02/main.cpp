/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 00:04:22 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main()
{
        Fixed a;
        Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
        std::cout << a << std::endl;
        std::cout << ++a << std::endl;
        std::cout << a << std::endl;
        std::cout << a++ << std::endl;
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << Fixed::max( a, b ) << std::endl;
        if (a > b)
            std::cout << "a mayor\n";
        else
            std::cout << "b mayor\n";
        a.setRawBits(2);
        std::cout << a << std::endl;
        std::cout << --a << std::endl;
        std::cout << a-- << std::endl;
        std::cout << a << std::endl;

    return (0);
}
