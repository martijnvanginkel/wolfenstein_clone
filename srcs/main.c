#include "./minilibx/mlx.h"

typedef struct  s_data
{
    void    *img;
    char    *address;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    put_square(int x_size, int y_size, int color, t_data *img)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < x_size)
    {
        while (y < y_size)
        {
            my_mlx_pixel_put(img, x, y, color);
            y++;
        }
        y = 0;
        x++;
    }
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.address = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    put_square(250, 250, 0x30d5c8, &img);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
} 