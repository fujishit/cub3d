/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/09 13:25:37 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mlx_setup(t_game *game, t_cub *cub, t_system *sys)
{
	sys->win = mlx_new_window(sys->mlx, cub->width, cub->height, "cub3d");
	if (game->sys.win == NULL)
		game_error_exit(game, "window error", MLX_ERROR);
	sys->img.img = mlx_new_image(sys->mlx, cub->width, cub->height);
	if (sys->img.img == NULL)
		game_error_exit(game, "image error", MLX_ERROR);
	sys->img.addr = (int *)mlx_get_data_addr(\
		sys->img.img, &sys->img.bpp, &sys->img.size_l, &sys->img.endian);
}
