/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/09 09:55:56 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_check(t_cub *cub, char map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX])
{
	int		y;
	int		x;

	y = 0;
	while (y < cub->map_height)
	{
		x = 0;
		while (map[y][x] == ' ')
			x++;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || \
				map[y][x] == 'W' || map[y][x] == 'E')
				map_player(cub, y, x, map[y][x]);
			else if (map[y][x] == '2')
				map_sprite(cub, y, x);
			else if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ')
				input_error_exit("invalid character", MAP_ERROR);
			x++;
		}
		y++;
	}
	map_fill(cub, cub->start_y, cub->start_x);
	if (map_isvalid(cub) == 1)
		input_error_exit("invalid map", MAP_ERROR);
}

void	map_player(t_cub *cubstat, int y, int x, char c)
{
	if (cubstat->start_dir != 0)
	{
		cubstat_free(cubstat);
		input_error_exit("multiple player", MAP_ERROR);
	}
	cubstat->start_y = y;
	cubstat->start_x = x;
	cubstat->start_dir = c;
}

void	map_sprite(t_cub *cubstat, int y, int x)
{
	if (SP_NUM_MAX < cubstat->num_sprites)
	{
		cubstat_free(cubstat);
		input_error_exit("many sprites", MAP_ERROR);
	}
	cubstat->sprite[cubstat->num_sprites].y = y + 0.5;
	cubstat->sprite[cubstat->num_sprites].x = x + 0.5;
	cubstat->num_sprites++;
}

int	map_fill(t_cub *cubstat, int y, int x)
{
	if (y == cubstat->map_height || y < 0)
		return (1);
	else if (x == cubstat->map_width || x < 0)
		return (1);
	cubstat->map[y][x] = '3';
	if (cubstat->map[y - 1][x] != '1' && cubstat->map[y - 1][x] != '3')
		map_fill(cubstat, y - 1, x);
	if (cubstat->map[y + 1][x] != '1' && cubstat->map[y + 1][x] != '3')
		map_fill(cubstat, y + 1, x);
	if (cubstat->map[y][x + 1] != '1' && cubstat->map[y][x + 1] != '3')
		map_fill(cubstat, y, x + 1);
	if (cubstat->map[y][x - 1] != '1' && cubstat->map[y][x - 1] != '3')
		map_fill(cubstat, y, x - 1);
}

int	map_isvalid(t_cub *cubstat)
{
	int	y;
	int	x;

	y = 0;
	while (y < cubstat->map_height)
	{
		x = 0;
		while (x < cubstat->map_width)
		{
			if (cubstat->map[y][x] == '3')
			{
				if (y == 0 || y == (cubstat->map_height - 1))
					return (1);
				else if (x == 0 || x == (cubstat->map_width - 1))
					return (1);
				else
					cubstat->map[y][x] = '0';
			}
			x++;
		}
		if (cubstat->map[y][x] == '3')
			return (MAP_ERROR);
		y++;
	}
}
