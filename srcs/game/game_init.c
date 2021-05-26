/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/11 17:43:43 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cubstat_init(t_cub *cubstat, void *mlx)
{
	mlx_get_screen_size(mlx, &cubstat->max_win_width, &cubstat->max_win_height);
	cubstat->width = 0;
	cubstat->height = 0;
	cubstat->map_width = 0;
	cubstat->map_height = 0;
	cubstat->north_tex = NULL;
	cubstat->south_tex = NULL;
	cubstat->west_tex = NULL;
	cubstat->east_tex = NULL;
	cubstat->sprite_tex = NULL;
	cubstat->f_color.r = 0;
	cubstat->f_color.g = 0;
	cubstat->f_color.b = 0;
	cubstat->c_color.r = 0;
	cubstat->c_color.g = 0;
	cubstat->c_color.b = 0;
	cubstat->start_x = 0;
	cubstat->start_y = 0;
	cubstat->start_dir = 0;
	cubstat->num_sprites = 0;
	cubstat->sprite->x = 0;
	cubstat->sprite->y = 0;
}

void	map_init(char map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX])
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_HEIGHT_MAX)
	{
		x = 0;
		while (x < MAP_WIDTH_MAX)
		{
			map[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	system_init(t_system *sys, t_cub *cubstat)
{
	int	i;

	sys->pos_x = cubstat->start_x + 0.5;
	sys->pos_y = cubstat->start_y + 0.5;
	player_dir(sys, cubstat);
	if (sys->dir_x != 0.0)
		sys->plane_x = 0;
	else
		sys->plane_x = sys->dir_y * -0.66;
	if (sys->dir_y != 0.0)
		sys->plane_y = 0;
	else
		sys->plane_y = sys->dir_x * 0.66;
	sys->move_speed = 0.05;
	sys->rot_speed = 0.05;
	sys->buf = (int **)ft_calloc(cubstat->height, sizeof(int *));
	i = 0;
	while (i < cubstat->height)
	{
		sys->buf[i] = (int *)ft_calloc(cubstat->width, sizeof(int));
		i++;
	}
	i = 0;
	while (i < WIN_WIDTH_MAX)
		sys->z_buffer[i++] = 0.0;
}

void	player_dir(t_system *sys, t_cub *cubstat)
{
	if (cubstat->start_dir == 'N' || cubstat->start_dir == 'S')
		sys->dir_x = 0.0;
	else
	{
		if (cubstat->start_dir == 'E')
			sys->dir_x = 1.0;
		else
			sys->dir_x = -1.0;
	}
	if (cubstat->start_dir == 'W' || cubstat->start_dir == 'E')
		sys->dir_y = 0.0;
	else
	{
		if (cubstat->start_dir == 'N')
			sys->dir_y = -1.0;
		else
			sys->dir_y = 1.0;
	}
}
