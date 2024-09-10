/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:34:38 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/09 20:33:35 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int Fixed::fracctional = 8;

Fixed::Fixed() : value(0)   
{   
    std::cout << "\033[32;1m> Default constructor called\n";
}

Fixed::Fixed(const Fixed &fixed_point) : 
    value(fixed_point.value)
{
    std::cout << "\033[34;1m> Copy constructor called\n";
}

Fixed::~Fixed()
{
    std::cout << "\033[31;1m> Destructor called\n";
}

Fixed& Fixed::operator=(const Fixed& other)
{
    std::cout << "\033[93;1m> Copy assignment operator called\n";
    if (this != &other)
        this->value = other.value;
    return (*this);
}

int Fixed::getRawBits(void) const
{
    std::cout << "\033[35;1m> getRawBits member function called\n";
    return (this->value);
}

void Fixed::setRawBits( int const raw )
{
    this->value = raw;
}