#include "./minilibx_macos/mlx.h" 



// int main(void) {
//     // Initialization (replace with actual function calls)
//     t_mlx mlx = mlx_init();  // Create MLX context
//     t_img img = load_image("path/to/image.jpg");  // Load image

//     // Window creation (replace with actual function calls)
//     int window_width = 640;
//     int window_height = 480;
//     Window window = create_window(mlx, window_width, window_height, "Image Viewer");

//     // Draw the image on the window (replace with actual function calls)
//     draw_image_on_window(window, &img);  // Pass a pointer to the image

//     // Event loop (replace with actual function calls)
//     handle_events_mlx(mlx);  // Process events (mouse clicks, window resizing, etc.)

//     // Cleanup (replace with actual function calls)
//     destroy_image(&img);  // Free image resources
//     destroy_window(window);  // Close the window
//     cleanup_mlx(mlx);  // Shut down MLX context

//     return 0;
// }


// gcc -o fdf main.c -lmlx -framework Cocoa -I./minilbx
//./fdf

int main (void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "mlx 42");
    mlx_loop(mlx);
    return (0);
}
