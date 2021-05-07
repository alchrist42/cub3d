#include "cub3d.h"

int	press_button(int keycode, t_data *img)
{
	if (keycode == 53)
		close_win(img);
	else if (keycode == 13)
		img->btn_w = true;
	else if (keycode == 1)
		img->btn_w = true;
	return (0);
}

int	release_button(int keycode, t_data *img)
{
	if (keycode == 53)
		close_win(img);
	else if (keycode == 13)
		img->btn_w = false;
	else if (keycode == 1)
		img->btn_w = false;
	return (0);
}
