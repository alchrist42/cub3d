#include "cub3d.h"

void	get_img(t_param *p, t_data *img) 
{
	int	col;
	int	start_ind;
	double	vx = img->plr->vx;
	double	vy = img->plr->vy;
	double	wall_h;
	// int up_board;
	// int down_board;

	col = -1;
	start_ind = img->plr->ind_v - p->res_x / 2;
	if (start_ind < 0)
		start_ind += p->cnt_v;
	while(++col < p->res_x)
	{
		vx = img->v[start_ind + col].x;
		vy = img->v[start_ind + col].y;
		wall_h = p->res_y / get_dist_to_wall(p, img, vx, vy) / img->v[ft_abs(p->res_x / 2 - col)].x;
		put_column(p, img, col, p->res_y / 2 - wall_h, p->res_y / 2 + wall_h);
	}
}

void	put_column(t_param *p, t_data *img, int col, int up, int down)
{
	int	row;

	row = 0;
	while (row <= up && row < p->res_y)
		my_mlx_pixel_put(img, row++, col, 0x00111111);
	while (row < down && row < p->res_y)
		my_mlx_pixel_put(img, row++, col, 0x00225522);
	while (row < p->res_y)
		my_mlx_pixel_put(img, row++, col, 0x00111111);
}

double	get_dist_to_wall(t_param *p, t_data *img, double vx, double vy)
{
	
	float row;
	float col;
	float row1;
	float col1;
	float row2;
	float col2;

	float	col_x;
	float	col_y;
	float	row_y;
	float	row_x;
	

	col_x = 1;
	if (vx < 0)
		col_x = -1;
	col_y = vy / vx * col_x;

	row_y = 1;
	if (vy < 0)
		row_y = -1;
	row_x = vx / vy * row_y;



	col1 = (int)img->plr->x + (col_x > 0);
	row1 = img->plr->y + (col1 - img->plr->x) * col_y * col_x;
	row2 = (int)img->plr->y + (row_y > 0);
	col2 = img->plr->x + (row2 - img->plr->y) * row_x * row_y;

	int i = 0;
	if (fabs(col1 - img->plr->x) + fabs(row1 - img->plr->y) < fabs(col2 - img->plr->x) + fabs(row2 - img->plr->y))
	{
		row = row1;
		col = col1;
		col1 = (int)col + (col_x > 0);
		row1 = row + (col1 - col) * col_y * col_x;
	}
	else
	{
		row = row2;
		col = col2;
		row2 = (int)row + (row_y > 0);
		col2 = col + (row2 - row) * row_x * row_y;

	}
	// founded first point!
	// printf("-----------\nplayer (%f %f)\npoint(%i): %f %f \n", img->plr->y, img->plr->x, i, row, col);
	my_mlx_pixel_put(img, row * p->res_y / (p->h_map * 3), col * p->res_x / (p->w_map * 2), 0x00BFF0FF);
	
	// return (sqrt((row - img->plr->y) * (row - img->plr->y) + (col - img->plr->x) * (col - img->plr->x)));


	// int srow = row;
	// int	scol = col;

	while (++i < 200)
	{
		
		if (p->map[(int)(row + 0.000001 * row_y)][(int)(col + 0.000001 * col_x )] == '1')
			return (sqrt((row - img->plr->y) * (row - img->plr->y) + (col - img->plr->x) * (col - img->plr->x)));
		if (fabs(col1 - img->plr->x) + fabs(row1 - img->plr->y) < fabs(col2 - img->plr->x) + fabs(row2 - img->plr->y))
		{
			row = row1;
			col = col1;
			col1 = (int)col + col_x;
			row1 = row + (col1 - col) * col_y * col_x;
		}
		else
		{
			row = row2;
			col = col2;
			row2 = (int)row + row_y;
			col2 = col + (row2 - row) * row_x * row_y;
		}
		// printf("-----------\nplayer (%f %f)\npoint(%i): %f %f \n", img->plr->y, img->plr->x, i, row, col);
		my_mlx_pixel_put(img, row * p->res_y / (p->h_map * 3), col * p->res_x / (p->w_map * 2), 0x00BFB0FF);
	}
	return (0);
	
}

