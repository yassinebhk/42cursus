/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:09:22 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 00:55:16 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0)
{}

Point::~Point()
{
}

Point::Point(const float &n1, const float &n2)  : x(n1) , y(n2)
{
	
}

Point::Point(const Point &point) : x(point.x) , y(point.y)
{}

Fixed Point::getX() const
{
    return x;
}

Fixed Point::getY() const
{
    return y;
}

Point &Point::operator=(const Point &other)
{
	(void)other;
	return (*this);	
}

