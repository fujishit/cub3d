/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 06:09:07 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game_key(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game_key_wd(
			&game->cubstat, &game->sys, game->sys.dir_x, game->sys.dir_y);
	else if (keycode == KEY_A)
		game_key_as(
			&game->cubstat, &game->sys, game->sys.plane_x, game->sys.plane_y);
	else if (keycode == KEY_S)
		game_key_as(
			&game->cubstat, &game->sys, game->sys.dir_x, game->sys.dir_y);
	else if (keycode == KEY_D)
		game_key_wd(
			&game->cubstat, &game->sys, game->sys.plane_x, game->sys.plane_y);
	else if (keycode == KEY_RIGHT)
		game_key_rotate(
			&game->cubstat, &game->sys, -1);
	else if (keycode == KEY_LEFT)
		game_key_rotate(
			&game->cubstat, &game->sys, 1);
	else if (keycode == KEY_ESC)
		exit(0);
}

void	game_key_wd(t_cub *cubstat, t_system *sys, double x, double y)
{
	if (cubstat->map \
			[(int)(sys->pos_y)][(int)(sys->pos_x + x * sys->move_speed)] != '1')
		sys->pos_x += x * sys->move_speed;
	if (cubstat->map \
			[(int)(sys->pos_y + y * sys->move_speed)][(int)(sys->pos_x)] != '1')
		sys->pos_y += y * sys->move_speed;
}

void	game_key_as(t_cub *cubstat, t_system *sys, double x, double y)
{
	if (cubstat->map \
		[(int)(sys->pos_y)][(int)(sys->pos_x - x * sys->move_speed)] != '1')
		sys->pos_x -= x * sys->move_speed;
	if (cubstat->map \
		[(int)(sys->pos_y - y * sys->move_speed)][(int)(sys->pos_x)] != '1')
		sys->pos_y -= y * sys->move_speed;
}

void	game_key_rotate(t_cub *cubstat, t_system *sys, int dir)
{
	double	dir_x;
	double	plane_x;

	dir_x = sys->dir_x;
	plane_x = sys->plane_x;
	sys->dir_x = sys->dir_x * cos(dir * -sys->rot_speed) - \
									sys->dir_y * sin(dir * -sys->rot_speed);
	sys->dir_y = dir_x * sin(dir * -sys->rot_speed) + \
									sys->dir_y * cos(dir * -sys->rot_speed);
	sys->plane_x = sys->plane_x * cos(dir * -sys->rot_speed) - \
									sys->plane_y * sin(dir * -sys->rot_speed);
	sys->plane_y = plane_x * sin(dir * -sys->rot_speed) + \
									sys->plane_y * cos(dir * -sys->rot_speed);
}
