#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_mmap(t_params *p, t_data	*img)
{
	int x;
	int	y;
	char ch;

	x = 0;
	while (x*3 < p->res_y)
	{
		y = 0;
		while (y*2 < p->res_x)
		{
			ch = p->map[x*3 * p->h_map / p->res_y][y*2 * p->w_map / p->res_x];
			if (ch == '1')
				my_mlx_pixel_put(img, y, x, 0x0FFF00FF);
			else if (char_in_str(ch, "NEWS"))
				my_mlx_pixel_put(img, y, x, 0x0F009F00);
			else if (char_in_str(ch, "2"))
				my_mlx_pixel_put(img, y, x, 0x0F800000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}



void	create_window(t_params *p)
{
	t_data	img;

	img.mlx = mlx_init();
	correct_resolution(&img, p);
	img.win = mlx_new_window(img.mlx, p->res_x, p->res_y, "Cub3D");
	img.img = mlx_new_image(img.mlx, p->res_x, p->res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.end);
	draw_mmap(p, &img);
	mlx_hook(img.win, 2, 1L<<0, close_win, &img);
	
	mlx_loop(img.mlx);
}

int	close_win(int keycode, t_data *img)
{
	(void)keycode;
	mlx_destroy_window(img->mlx, img->win);
	exit (0);
}