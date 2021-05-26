/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/09 13:18:19 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_init(int x, t_wall *wall, t_game *game, t_system *sys)
{
	wall->camera_x = 2 * x / (double)game->cubstat.width - 1;
	wall->ray_dir_x = sys->dir_x + sys->plane_x * wall->camera_x;
	wall->ray_dir_y = sys->dir_y + sys->plane_y * wall->camera_x;
	wall->map_x = (int)sys->pos_x;
	wall->map_y = (int)sys->pos_y;
	wall->delta_dist_x = fabs(1 / wall->ray_dir_x);
	wall->delta_dist_y = fabs(1 / wall->ray_dir_y);
	wall->step_x = -1;
	wall->step_y = -1;
	if (wall->ray_dir_x < 0)
		wall->side_dist_x = (sys->pos_x - wall->map_x) * wall->delta_dist_x;
	else
	{
		wall->step_x = 1;
		wall->side_dist_x = \
			(wall->map_x + 1.0 - sys->pos_x) * wall->delta_dist_x;
	}
	if (wall->ray_dir_y < 0)
		wall->side_dist_y = (sys->pos_y - wall->map_y) * wall->delta_dist_y;
	else
	{
		wall->step_y = 1;
		wall->side_dist_y = \
			(wall->map_y + 1.0 - sys->pos_y) * wall->delta_dist_y;
	}
}

void	wall_raycast(int x, t_wall *wall, t_game *game, t_cub *cubstat)
{
	wall->hit = 0;
	while (wall->hit == 0)
	{
		if (wall->side_dist_x < wall->side_dist_y)
		{
			wall->side_dist_x += wall->delta_dist_x;
			wall->map_x += wall->step_x;
			wall->side = 0;
		}
		else
		{
			wall->side_dist_y += wall->delta_dist_y;
			wall->map_y += wall->step_y;
			wall->side = 1;
		}
		if (cubstat->map[wall->map_y][wall->map_x] == '1')
			wall->hit = 1;
	}
	if (wall->side == 0)
		wall->perp_wall_dist = (wall->map_x - game->sys.pos_x +\
								(1 - wall->step_x) / 2) / wall->ray_dir_x;
	else
		wall->perp_wall_dist = (wall->map_y - game->sys.pos_y +\
								(1 - wall->step_y) / 2) / wall->ray_dir_y;
}

void	wall_texture(t_wall *wall, t_game *game, t_system *sys, t_cub *cubstat)
{
	wall->line_height = (int)(cubstat->height / wall->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + cubstat->height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + cubstat->height / 2;
	if (wall->draw_end >= cubstat->height)
		wall->draw_end = cubstat->height - 1;
	wall->tex_num = 0;
	if (cubstat->map[wall->map_y][wall->map_x] != '0')
		wall->tex_num = 1;
	if (wall->tex_num != 0)
		if (wall->side == 1 && wall->ray_dir_y < 0)
			wall->tex_num = 1;
	else if (wall->side == 1 && wall->ray_dir_y > 0)
		wall->tex_num = 2;
	else if (wall->side == 0 && wall->ray_dir_x < 0)
		wall->tex_num = 3;
	else if (wall->side == 0 && wall->ray_dir_x > 0)
		wall->tex_num = 4;
	if (wall->side == 0)
		wall->wall_x = sys->pos_y + wall->perp_wall_dist * wall->ray_dir_y;
	else
		wall->wall_x = game->sys.pos_x + wall->perp_wall_dist * wall->ray_dir_x;
}

void	wall_pattern(t_wall *wall, t_system *sys, t_cub *cubstat)
{
	wall->wall_x -= (int)wall->wall_x;
	wall->tex_x = \
		(int)(wall->wall_x * (double)(sys->tex[wall->tex_num].size_l / 4));
	if (wall->side == 0 && wall->ray_dir_x > 0)
		wall->tex_x = (sys->tex[wall->tex_num].size_l / 4) - wall->tex_x - 1;
	if (wall->side == 1 && wall->ray_dir_y > 0)
		wall->tex_x = (sys->tex[wall->tex_num].size_l / 4) - wall->tex_x - 1;
	if (wall->tex_num == 3 || wall->tex_num == 4)
		wall->tex_x = (sys->tex[wall->tex_num].size_l / 4) - wall->tex_x - 1;
	wall->step = 1.0 * sys->tex[wall->tex_num].img_height / wall->line_height;
	wall->tex_pos = (wall->draw_start - \
		cubstat->height / 2 + wall->line_height / 2) * wall->step;
}

void	wall_color(int x, t_wall *wall, t_game *game, t_cub *cubstat)
{
	int	y;

	y = -1;
	while (++y <= wall->draw_start - 1 && y <= cubstat->width)
	{
		game->sys.buf[y][x] = create_trgb(\
			0, cubstat->c_color.r, cubstat->c_color.g, cubstat->c_color.b);
	}
	while (y < wall->draw_end + 1 && y <= cubstat->height)
	{
		wall->tex_y = fmin(\
			wall->tex_pos, (game->sys.tex[wall->tex_num].img_height));
		wall->tex_pos += wall->step;
		wall->color = game->sys.tex[wall->tex_num].addr[(game->sys.tex[\
			wall->tex_num].size_l / 4) *wall->tex_y + wall->tex_x];
		game->sys.buf[y][x] = wall->color;
		y++;
	}
	while (y < cubstat->height)
	{
		game->sys.buf[y][x] = create_trgb(\
			0, cubstat->f_color.r, cubstat->f_color.g, cubstat->f_color.b);
		y++;
	}
	game->sys.z_buffer[x] = wall->perp_wall_dist;
}
