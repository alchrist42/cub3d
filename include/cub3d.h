#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/errno.h>

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"

# define DEBUG 1

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_UP 126
# define KEY_DW 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_Q 12
# define KEY_E 14
# define KEY_ESC 53

typedef struct	s_player
{
	float	x;
	float	y;
	float	z;
	double	vx;
	double	vy;
	double	vz;
	float	speed;
}	t_player;

typedef struct s_buttons
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	q;
	bool	e;
}	t_buttons;


typedef struct s_params
{
	int		res_x;
	int		res_y;
	char	*t_no;
	char	*t_so;
	char	*t_we;
	char	*t_ea;
	char	*t_sp;
	int		floor[3];
	int		cel[3];
	bool	got_res;
	bool	got_floor;
	bool	got_cel;
	bool	got_params;

	bool	end_map;
	int		h_map;
	int		w_map;
	t_list	*lst_map;
	char	**map;

	int		plr_x;
	int		plr_y;
	bool	save;

	double	sin_a;
	double	cos_a;

	double	angle_x;
	double	angle_y;
	double	start_cos;
	double	start_sin;
	double	angle_step;
	double	sin_step;
	double	cos_step;
}	t_params;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			llen;
	int			end;
	t_params 	*params;
	t_player	*plr;
	t_buttons	*btn;
}				t_data;

// raise_error.c
void	ft_raise_error(char *s);

// parcer_utils.c
int		ft_arrlen(char **arr);
int		ft_min(int a, int b);
int		only_digits(char *s);
void	ft_free_split(char **arr);
int		char_in_str(char ch, char *charset);

// parser.c
int		parcer(int argc, char **argv, t_params *p);
int		parsing_args(int argc, char **argv, t_params *p);
void	inicialise_params(t_params *p);
void	parsing_params(int fd, t_params *p);
void	parsing_line(char *s, t_params *p);

// parser_lines.c
void	get_resolution(char *s, t_params *p);
void	get_colors(char *s, bool is_floor, t_params *p);
void	get_texture(char *s, t_params *p);

// parcer_map.c
void	check_line_map(char *s, t_params *p);
void	create_map(t_params *p);
void	check_field(t_params *p);

// window.c
void	create_window(t_data *img, t_params *p, t_buttons *btn);
int		close_win(t_data *img);
void	correct_resolution(t_data *img, t_params *p);

// get_img.c
void	get_img(t_params *p, t_data *img);
double	get_dist_to_wall(t_params *p, t_data *img, double vx, double vy);


// get_img_helpers.c
void	my_mlx_pixel_put(t_data *data, int row, int col, int color);
void	draw_mmap(t_params *p, t_data	*img);
int		create_trgb(int t, int r, int g, int b);
int		both_equal_sign(float x, float y);


int 	prepare_frame(t_data *img);
void	draw_player(t_params *p, t_data *img);
void	draw_ray_of_sight(t_params *p, t_data *img);

// hooks.c
int		press_button(int keycode, t_data *img);
int		release_button(int keycode, t_data *img);

// game.c
void	run_game(t_data *img);
int		main_game(t_data *img);

// player.c
void	inicialise_buttons(t_buttons *btn);
void	initialise_player(t_data *img, t_params *p, t_player *plr);

// mooving.c
void	change_position(t_params *p, t_player *plr, t_buttons *btn);
void	rotate_view(t_params *p, t_player *plr, t_buttons *btn);
void	rotate_by_ange(double *x, double *y, double sin_a, double cos_a);

#endif
