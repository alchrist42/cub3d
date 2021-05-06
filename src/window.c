#include "cub3d.h"

int	create_window(t_params *p)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, p->res_x, p->res_y, "Cub3D");
	mlx_loop(mlx);
	return (0);
}