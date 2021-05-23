#include "cub3d_bonus.h"

void	draw_mmap(t_param *p, t_data *img)
{
	int row;
	int	col;
	char ch;

	row = -1;
	while (++row < p->mmap_y)
	{
		col = -1;
		while (++col < p->mmap_x)
		{
			ch = p->map[p->h_map * row / p->mmap_y][p->w_map * col / p->mmap_x];
			if (ch == '1' && p->mmap[p->mmap_x * row + col])
				my_mlx_pixel_put(img, row, col, 0x004F204F);
			// else if (char_in_str(ch, "NEWS"))
			// 	my_mlx_pixel_put(img, y, x, 0x0F009F00);
			else if (char_in_str(ch, "2"))
				my_mlx_pixel_put(img, row, col, 0x00008000);
			// else
			// 	my_mlx_pixel_put(img, row, col, 0x00000000);
		}
	}
	draw_player(p, img);
}

void	draw_player(t_param *p, t_data *img)
{
	int	row;
	int	col;
	int	i;
	int j;
	int m;
	
	row = img->plr->y * p->mmap_y / p->h_map;
	col = img->plr->x * p->mmap_x / p->w_map;
	i = -3;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
		{
			my_mlx_pixel_put(img, row + i, col + j, CLR_PLR);
			m = 0;
			while (++m < p->mmap_dst)
				p->mmap[ft_min(p->mmap_len, ft_max(0, p->mmap_x * (row + m * i) + col + m * j))] = 1;
		}
	}
}

void	create_mini_map(t_data *img, t_param *p)
{
	p->mmap_x = img->p->res_x / 4;
	p->mmap_y = ft_min(p->res_y / 2, p->mmap_x * p->h_map / p->w_map);
	p->mmap_len = p->mmap_x * p->mmap_y;
	p->mmap_dst = p->mmap_x / p->w_map * 1.4;
	p->mmap = ft_calloc(p->mmap_len, sizeof(*p->mmap));
	if(!p->mmap)
		ft_raise_error("Cann't allocation memory for minimap\n");
	
	
}

void	draw_ray_mmap(t_data *img, t_dot *dot)
{
	int	row;
	int	col;

	if (!img->plr->i_mmap)
		return ;
	row = dot->y * img->p->mmap_y / img->p->h_map;
	col = dot->x * img->p->mmap_x / img->p->w_map;
	my_mlx_pixel_put(img, row, col, CLR_RAY);
}
