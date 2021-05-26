/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 06:02:04 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc == 2)
	{
		game_setup(&game, argv[1]);
		mlx_loop_hook(game.sys.mlx, game_loop, &game);
		mlx_hook(game.sys.win, 2, 1L << 0, game_key, &game);
		mlx_hook(game.sys.win, 33, 1L << 17, close_window, &game);
		mlx_loop(game.sys.mlx);
	}
	else if (argc == 3)
		game_save(argv, &game, &game.sys, &game.cubstat);
	else
		error_exit(
			"please \"./cub3D *.cub\" or \"./cub3D *.cub --save\"", ARG_ERROR);
	return (0);
}

int	close_window(int keycode, t_game *game)
{
	exit(0);
}
