/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:34:38 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 00:47:00 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>

const int Fixed::fracctional = 8;

Fixed::Fixed() : value(0)   
{   
}

Fixed::Fixed(const Fixed &fixed_point) : 
    value(fixed_point.value)
{
}

Fixed::Fixed(const int &num)
{
    this->value = num << fracctional;
}

Fixed::Fixed(const float &num)
{
    this->value = roundf(num * (1 << fracctional));    
}


Fixed::~Fixed()
{
}

Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
        this->value = other.value;
    return (*this);
}

bool Fixed::operator<(const Fixed& other) const
{
    return (this->value < other.value);
}

bool Fixed::operator>(const Fixed& other) const
{
    return (this->value > other.value);    
}

bool Fixed::operator<=(const Fixed& other) const
{
    return (this->value <= other.value);   
}

bool Fixed::operator>=(const Fixed& other) const
{
    return (this->value >= other.value);    
}

bool Fixed::operator==(const Fixed& other) const
{
    return (this->value == other.value);   
}

bool Fixed::operator!=(const Fixed& other) const
{
    return (this->value != other.value);    
}

Fixed Fixed::operator+(const Fixed& other) const
{
    Fixed aux;
    
    aux.value =  (this->value + other.value);
    return (aux);
}

Fixed Fixed::operator-(const Fixed& other) const
{
    Fixed aux;
    
    aux.value =  (this->value - other.value);
    return (aux);   
}

Fixed Fixed::operator*(const Fixed& other) const
{
    Fixed aux;
    
    aux.value =  (this->value * other.value) >> fracctional;
    return (aux);   
}

Fixed Fixed::operator/(const Fixed& other) const
{
    Fixed aux;
    
    aux.value = (this->value << fracctional) / other.value;
    return (aux);    
}

int Fixed::getRawBits(void) const
{
    return (this->value);
}

Fixed& Fixed::operator++() {
    this->value += 1; 
    return *this;
}

Fixed& Fixed::operator--() {
    this->value -= 1; 
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp = *this;
    ++(*this);
    return temp;
}

Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    --(*this);
    return temp;
}

void Fixed::setRawBits( int const raw )
{
    this->value = raw;
}

float Fixed::toFloat( void ) const
{
    return ((float)this->value / (1 << fracctional));    
}

int Fixed::toInt( void ) const
{
    return (this->value >> fracctional);       
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    if (a.value < b.value)
        return (a);
    else
        return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    if (a.value > b.value)
        return (a);
    else
        return (b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
    if (a.value < b.value)
        return (a);
    else
        return (b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
    if (a.value > b.value)
        return (a);
    else
        return (b);
}


std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}