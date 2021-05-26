/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/09 09:38:15 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_save(char **arg, t_game *game, t_system *sys, t_cub *cubstat)
{
	int		fd;

	if (arg[2][0] != '-' || arg[2][1] != '-' || arg[2][2] != 's' || arg[2][3]
	!= 'a' || arg[2][4] != 'v' || arg[2][5] != 'e' || arg[2][6] != '\0')
		error_exit(arg[2], ARG_ERROR);
	sys->mlx = mlx_init();
	if (sys->mlx == NULL)
		game_error_exit(game, "init error", MLX_ERROR);
	cubstat_init(cubstat, sys->mlx);
	map_init(cubstat->map);
	fd = open(arg[1], O_RDONLY);
	cubstat_input(cubstat, fd, 1);
	close(fd);
	map_check(&game->cubstat, game->cubstat.map);
	sys->img.img = mlx_new_image(sys->mlx, cubstat->width, cubstat->height);
	sys->img.addr = (int *)mlx_get_data_addr(\
		sys->img.img, &sys->img.bpp, &sys->img.size_l, &sys->img.endian);
	system_init(sys, cubstat);
	load_texture(game, cubstat, sys->tex);
	loop_raycast(game, sys, cubstat);
	save_screenshot(game, cubstat, sys);
	image_destroy(sys);
	cubstat_free(&game->cubstat);
	buf_free(sys->buf, cubstat->height);
	free(sys->mlx);
}

void	save_screenshot(t_game *game, t_cub *cubstat, t_system *sys)
{
	int	fd;

	fd = open("capture.bmp", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		cubstat_free(cubstat);
		error_exit("screenshot error", FILE_ERROR);
	}
	save_header(fd, cubstat);
	save_data(fd, cubstat, sys);
	close(fd);
}

void	save_header(int fd, t_cub *cubstat)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 64 + (4 * cubstat->width * cubstat->height);
	ft_memset(header, 0, 54);
	ft_memcpy(header, "BM", 2);
	save_color(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)40;
	save_color(header + 18, cubstat->width);
	save_color(header + 22, cubstat->height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned int)(32);
	write(fd, header, 54);
}

void	save_data(int fd, t_cub *cubstat, t_system *sys)
{
	int				row;
	int				col;
	int				row_size;
	size_t			padding;

	row = cubstat->height - 1;
	row_size = cubstat->width * 4;
	padding = 4 - (row_size % 4);
	if (row_size % 4 == 0)
		padding = 0;
	while (row >= 0)
	{
		col = 0;
		while (col < cubstat->width)
		{
			write(fd, &sys->img.addr[row * cubstat->width + col], 4);
			write(fd, "\0\0\0", padding);
			col++;
		}
		row--;
	}
}

void	save_color(unsigned char *bmp, int color)
{
	bmp[0] = (unsigned char)(color);
	bmp[1] = (unsigned char)(color >> 8);
	bmp[2] = (unsigned char)(color >> 16);
	bmp[3] = (unsigned char)(color >> 24);
}
