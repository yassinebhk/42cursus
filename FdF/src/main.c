/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:53:28 by ybouhaik          #+#    #+#             */
/*   Updated: 2024/02/26 12:40:34 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

// int	handle_no_event(void *data)
// {
//     /* This function needs to exist, but it is useless for the moment */
//     (void)data;
//     return (0);
// }

// int	handle_input(int keysym, t_data *data)
// {
//     if (keysym == 53)
//         mlx_destroy_window(data->mlx, data->win);
//     return (0);
// }

// int main (void)
// {   
//     int fd;
//     size_t size_column;
//     int size_row;
//     char *line;

//     fd = open("./test_maps/42.fdf", O_RDONLY);
//     if (fd < 0)
//         return (0);
//     line = get_next_line(fd);
//     if (!line)
//         return (0);
//     size_row = 0;
//     size_column = ft_strlen(line);
//     while (!line)
//     {
//         if (size_column != ft_strlen(line))
//             return (0);
//         line = get_next_line(fd);
//         size_row++;
//     }

//     printf("size_row: %d\n", size_row);
//     printf("size_column: %zu\n", size_column);
    
//     close(fd);
//     t_data	data;
//     // void *mlx; // void *mlx es un puntero a void que se utiliza para almacenar la dirección de memoria de la estructura MLX.
//     // void *win; // void *win es un puntero a void que se utiliza para almacenar la dirección de memoria de la estructura Window.
//     // void *img; // void *img es un puntero a void que se utiliza para almacenar la dirección de memoria de la estructura Image.

//     data.mlx = mlx_init();
//     if (!data.mlx)
//         return (0);
//     data.win = mlx_new_window(data.mlx, WINDOW_HEIGHT, WINDOW_HEIGHT, "mlx 42");
//     if (!data.win)
//         return (0);
//     data.img = mlx_new_image(data.mlx, 20, 20);
//     if (!data.img)
//         return (0);
//     // if (!mlx_string_put(data.mlx, data.win, 60, 10, GOLD, "Hello World!"))
//     //     return (0);
//     // if (mlx_put_image_to_window(data.mlx, data.win, data.img, WINDOW_HEIGHT/2, WINDOW_HEIGHT/2))
//     //     return (0);
    
//     int i = 0;
//     while (i < 1200)
//     {
//         mlx_pixel_put(data.mlx, data.win, i, 0, WHITE);
//         mlx_pixel_put(data.mlx, data.win, 0, i, WHITE);
//         mlx_pixel_put(data.mlx, data.win, i, WINDOW_HEIGHT - 1, WHITE);
//         mlx_pixel_put(data.mlx, data.win, WINDOW_WIDTH - 1, i, WHITE);
//         i++;
//     }
    
//     int j = 1;
//     while (j < 20)
//     {   
//         i = 0;
//         while (i < WINDOW_HEIGHT - 1)
//         {
//             mlx_pixel_put(data.mlx, data.win, j*60, i,  WHITE);
//             mlx_pixel_put(data.mlx, data.win, i, j*60,  WHITE);
//             i++;
//         }
//         j++;
//     }
//     /* Setup hooks */ 
//     mlx_loop_hook(data.mlx, &handle_no_event, &data);
//     mlx_key_hook(data.win, &handle_input, &data);
//     mlx_loop(data.mlx);
//     // mlx_destroy_display(data.mlx);
//     // free(data.mlx);
//     return (0);
// }

int main (void)
{
    mlx_t *mlx;
    mlx_image_t* image;
    mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true);
    image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_image_to_window(mlx, image, 0, 0);
    mlx_loop(mlx);
    return (0);
}