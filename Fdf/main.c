#include "minilbx/minilibx.h"

#include "minilibx.h"

int main(void)
{
  // Crea una ventana
  t_mlx mlx;
  mlx.init = mlx_init();
  mlx.win = mlx_new_window(mlx.init, 640, 480, "Mi primera ventana");

  // Bucle principal
  while (1)
  {
    // Renderiza la ventana
    mlx_loop(mlx.init);
  }

  // Finaliza la biblioteca
  mlx_destroy_window(mlx.win);
  mlx_destroy_display(mlx.init);

  return 0;
}

// gcc -o fdf main.c -lmlx -framework Cocoa -I./minilbx
//./fdf
