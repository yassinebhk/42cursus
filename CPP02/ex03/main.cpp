/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:32:16 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/09/11 01:03:19 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int main()
{
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(0.0f, 10.0f);
    Point inside(2.0f, 2.0f);
    Point outside(7.0f, 7.0f);
    Point onEdge(5.0f, 0.0f);

    if (bsp(a, b, c, inside))
        std::cout << "Point is inside the triangle.\n";
    else
        std::cout << "Point is outside the triangle.\n";

    if (bsp(a, b, c, outside))
        std::cout << "Point is inside the triangle.\n";
    else
        std::cout << "Point is outside the triangle.\n";

    if (bsp(a, b, c, onEdge))
        std::cout << "Point is inside the triangle.\n";
    else
        std::cout << "Point is outside the triangle.\n";

    return (0);
}
