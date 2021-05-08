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
	
	return (0);
}
