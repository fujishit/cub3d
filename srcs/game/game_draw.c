/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/05 12:27:40 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_draw(t_game *game, t_system *sys, t_cub *cubstat)
{
	int	y;
	int	x;

	y = 0;
	while (y < cubstat->height)
	{
		x = 0;
		while (x < cubstat->width)
		{
			sys->img.addr[y * (sys->img.size_l / 4) + x] = sys->buf[y][x];
			x++;
		}
		y++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
