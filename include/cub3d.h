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

typedef struct	s_vector
{
	double	x;
	double	y;
	double	rx;
	double	ry;
	double	cx;
	double	cy;
}	t_vector;

typedef struct	s_player
{
	float	x;
	float	y;
	float	z;
	float	dot_x; //del
	float	dot_y;
	float	dot_z;

	float	diff;
	int		texture_ind;
	double	vx;
	double	vy;
	double	vz;
	int		ind_v;
	int		rotate_speed;
	float	speed;
}	t_player;

typedef struct s_button
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	q;
	bool	e;
}	t_button;


typedef struct s_param
{
	int		res_x;
	int		res_y;
	char	*t_no;
	char	*t_so;
	char	*t_we;
	char	*t_ea;
	char	*t_sp;
	int		floor;
	int		cel;
	bool	got_param;

	bool	end_map;
	int		h_map;
	int		w_map;
	t_list	*lst_map;
	char	**map;

	int		plr_x;
	int		plr_y;
	bool	save;

	int		cnt_v;
	
	double	sin_a;
	double	cos_a;

	double	angle_x;
	double	angle_y;
	double	start_cos;
	double	start_sin;
	double	angle_step;
	double	sin_step;
	double	cos_step;
}	t_param;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		llen;
	int		end;
}	t_texture;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			llen;
	int			end;


	t_texture	xpm[5];
	t_param 	*param;
	t_player	*plr;
	t_button	*btn;
	t_vector	*v;
}				t_data;

typedef	struct s_sprite
{
	t_texture	*texture;
	int			height;
	int			diff;
}	t_sprite;

typedef struct s_dot
{
	float	x;
	float	y;
	float	z;
}	t_dot;	


// raise_error.c
void	ft_raise_error(char *s);

//utils.c
int		ft_abs(int a);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

// parcer_utils.c
int		ft_arrlen(char **arr);
int		only_digits(char *s);
void	ft_free_split(char **arr);
int		char_in_str(char ch, char *charset);

// parser.c
int		parcer(int argc, char **argv, t_param *p);
int		parsing_args(int argc, char **argv, t_param *p);
void	inicialise_params(t_param *p);
void	parsing_params(int fd, t_param *p);
void	parsing_line(char *s, t_param *p);

// parser_lines.c
void	get_resolution(char *s, t_param *p);
void	get_colors(char *s, bool is_floor, t_param *p);
void	get_texture(char *s, t_param *p);

// parcer_map.c
void	check_line_map(char *s, t_param *p);
void	create_map(t_param *p);
void	check_field(t_param *p);

// window.c
void	create_window(t_data *img, t_param *p, t_button *btn);
int		close_win(t_data *img);
void	correct_resolution(t_data *img, t_param *p);
void	get_textures(t_data *img, t_texture *xpm, t_param *p);

// get_img.c
void	draw_floor_and_cel(t_param *p, t_data *img);
void	draw_walls(t_param *p, t_data *img);
void	put_column(t_param *p, t_data *img, int col, int up, int down);
void	get_first_cross(t_data *img, t_vector *vray, t_dot *dot, t_dot *d1, t_dot *d2);
float	get_dist_to_wall(t_data *img, t_vector vray);



// get_img_helpers.c
void	my_mlx_pixel_put(t_data *data, int row, int col, int color);
void	my_mlx_row_put(t_data *data, int row, int color);
void	draw_mmap(t_param *p, t_data	*img);
int		create_trgb(int t, int r, int g, int b);
int		both_equal_sign(float x, float y);
void	pe4em_vectora(t_data *img, t_param *p);


int 	prepare_frame(t_data *img);
void	draw_player(t_param *p, t_data *img);
void	draw_ray_of_sight(t_param *p, t_data *img);

// hooks.c
int		press_button(int keycode, t_data *img);
int		release_button(int keycode, t_data *img);

// game.c
void	run_game(t_data *img);
int		main_game(t_data *img);

// player.c
void	inicialise_buttons(t_button *btn);
void	initialise_player(t_data *img, t_param *p, t_player *plr);

// mooving.c
void	change_pos(t_param *p, t_player *plr, t_button *btn, t_vector *vs);
void	rotate_view(t_param *p, t_player *plr, t_button *btn, t_data *img);
void	rotate_by_ange(double *x, double *y, double sin_a, double cos_a);

#endif
