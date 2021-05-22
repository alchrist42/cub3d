/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantigon <pantigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:00:56 by pantigon          #+#    #+#             */
/*   Updated: 2021/04/18 20:56:24 by pantigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
**	@brief	put type int to string by bytes
**	
**	@param	ch		point to char
**	@param	x		int
*/
void	ft_put_int(unsigned char *ch, int x)
{
	ch[0] = (unsigned char)x;
	ch[1] = (unsigned char)(x >> 8);
	ch[2] = (unsigned char)(x >> 16);
	ch[3] = (unsigned char)(x >> 24);
}

/*
**	@brief	wrrite to file bpm header
**	
**	@param	img		the mlx instance
**	@param	fd		the bmp file destiptor
**	@param	size	size of bmp file
*/
void	ft_bmp_header(t_data *img, int fd, int size)
{
	unsigned char	header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	ft_put_int(header + 2, size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	ft_put_int(header + 18, img->p->res_x);
	ft_put_int(header + 22, img->p->res_y);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	write(fd, header, 54);
}

/*
**	@brief	Get the pixel img object
**	
**	@param	img		the mlx instance
**	@param	row		the row index
**	@param	col		the column index
**	@return	int		color im TRGB format
*/
int	get_pixel_img(t_data *img, int row, int col)
{
	int	*color;

	color = (int *)(img->addr + img->llen * row
			+ (img->bpp / 8) * col);
	return (*color);
}

/*
**	@brief	put img to bmp file
**	
**	@param	img		the mlx instance
**	@param	fd		the bmp file descriptor
*/
void	ft_bmp_put_pixels(t_data *img, int fd)
{
	int	row;
	int	col;
	int	color;

	row = img->p->res_y;
	while (row--)
	{
		col = -1;
		while (++col < img->p->res_x)
		{
			color = get_pixel_img(img, row, col);
			write(fd, &color, 3);
		}
		write(fd, "\0\0\0", col % 4);
	}
}

/*
**	@brief	save screenshot screen game to bmp file
**	
**	@param	img		the mlx instance
*/
void	ft_save_bmp(t_data *img)
{
	int	fd;
	int	size;

	size = 54 + (img->p->res_x + (img->p->res_x + 1) % 4) * img->p->res_y * 3;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT
			| O_TRUNC, S_IRWXU);
	if (!fd)
		ft_raise_error("Cann't create screenshoy file\n");
	ft_bmp_header(img, fd, size);
	ft_bmp_put_pixels(img, fd);
	close(fd);
	exit(0);
}
