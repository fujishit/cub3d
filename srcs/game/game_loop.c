/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/05 10:48:45 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game_loop(t_game *game)
{
	loop_raycast(game, &game->sys, &game->cubstat);
	mlx_put_image_to_window(
		game->sys.mlx, game->sys.win, game->sys.img.img, 0, 0);
	return (0);
}

void	loop_raycast(t_game *game, t_system *sys, t_cub *cubstat)
{
	int			x;
	t_wall		wall;
	t_sprite	sprite;

	x = 0;
	while (x < cubstat->width)
	{
		loop_wall(x, &wall, game);
		x++;
	}
	sprite_place(&sprite, game, cubstat, sys);
	game_draw(game, sys, cubstat);
}

void	loop_wall(int x, t_wall *wall, t_game *game)
{
	wall_init(x, wall, game, &game->sys);
	wall_raycast(x, wall, game, &game->cubstat);
	wall_texture(wall, game, &game->sys, &game->cubstat);
	wall_pattern(wall, &game->sys, &game->cubstat);
	wall_color(x, wall, game, &game->cubstat);
}
