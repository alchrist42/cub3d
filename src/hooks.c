#include "cub3d.h"

int	press_button(int keycode, t_data *img)
{
	if (keycode == KEY_ESC)
		close_win(img);
	else if (keycode == KEY_W)
		img->btn->w = true;
	else if (keycode == KEY_S)
		img->btn->s = true;
	else if (keycode == KEY_A)
		img->btn->a = true;
	else if (keycode == KEY_D)
		img->btn->d = true;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		img->btn->q = true;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		img->btn->e = true;
	return (0);
}

int	release_button(int keycode, t_data *img)
{
	if (keycode == KEY_ESC)
		close_win(img);
	else if (keycode == KEY_W)
		img->btn->w = false;
	else if (keycode == KEY_S)
		img->btn->s = false;
	else if (keycode == KEY_A)
		img->btn->a = false;
	else if (keycode == KEY_D)
		img->btn->d = false;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		img->btn->q = false;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		img->btn->e = false;
	
	return (0);
}
