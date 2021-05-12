
float	get_dist_to_wall(t_data *img, t_vector vray)
{
	t_dot	dot;
	t_dot	d1;
	t_dot	d2;
	int		i;

	get_first_cross(img, &vray, &dot, &d1, &d2);
	my_mlx_pixel_put(img, dot.y * img->param->res_y / (img->param->h_map * 3), dot.x * img->param->res_x / (img->param->w_map * 2), 0x00BFF0FF);

	i = -1;
	while (++i < 300)
	{
		
		if (img->param->map[(int)(dot.y + 0.000001 * vray.ry)][(int)(dot.x + 0.000001 * vray.cx )] == '1')
			return (sqrt((dot.y - img->plr->y) * (dot.y - img->plr->y) + (dot.x - img->plr->x) * (dot.x - img->plr->x)));
		if (fabs(d1.x - img->plr->x) + fabs(d1.y - img->plr->y) < fabs(d2.x - img->plr->x) + fabs(d2.y - img->plr->y))
		{
			dot.y = d1.y;
			dot.x = d1.x;
			d1.x = (int)dot.x + vray.cx;
			d1.y = dot.y + (d1.x - dot.x) * vray.cy * vray.cx;
		}
		else
		{
			dot.y = d2.y;
			dot.x = d2.x;
			d2.y = (int)dot.y + vray.ry;
			d2.x = dot.x + (d2.y - dot.y) * vray.rx * vray.ry;
		}
		// printf("-----------\nplayer (%f %f)\npoint(%i): %f %f \n", img->plr->y, img->plr->x, i, dot.y, dot.x);
		my_mlx_pixel_put(img, dot.y * img->param->res_y / (img->param->h_map * 3), dot.x * img->param->res_x / (img->param->w_map * 2), 0x00BFB0FF);
	}
	return (300);
	
}

void	get_first_cross(t_data *img, t_vector *vray, t_dot *dot, t_dot *d1, t_dot *d2)
{
	d1->x = (int)img->plr->x + (vray->cx > 0);
	d1->y = img->plr->y + (d1->x - img->plr->x) * vray->cy * vray->cx;
	d2->y = (int)img->plr->y + (vray->ry > 0);
	d2->x = img->plr->x + (d2->y - img->plr->y) * vray->rx * vray->ry;

	int i = 0;
	if (fabs(d1->x - img->plr->x) + fabs(d1->y - img->plr->y) < fabs(d2->x - img->plr->x) + fabs(d2->y - img->plr->y))
	{
		dot->y = d1->y;
		dot->x = d1->x;
		d1->x = (int)dot->x + (vray->cx > 0);
		d1->y = dot->y + (d1->x - dot->x) * vray->cy * vray->cx;
	}
	else
	{
		dot->y = d2->y;
		dot->x = d2->x;
		d2->y = (int)dot->y + (vray->ry > 0);
		d2->x = dot->x + (d2->y - dot->y) * vray->rx * vray->ry;
	}
}