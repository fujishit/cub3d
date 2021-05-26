/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 06:04:27 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_place(t_sprite *sp, t_game *game, t_cub *cubstat, t_system *sys)
{
	int	i;

	i = 0;
	while (i < cubstat->num_sprites)
	{
		game->sprite_order[i] = i;
		game->sprite_distance[i] = (\
			(sys->pos_x - cubstat->sprite[i].x) * \
			(sys->pos_x - cubstat->sprite[i].x) + \
			(sys->pos_y - cubstat->sprite[i].y) * \
			(sys->pos_y - cubstat->sprite[i].y));
		i++;
	}
	sprite_sort(
		game->sprite_order, game->sprite_distance, cubstat->num_sprites);
	i = 0;
	while (i < cubstat->num_sprites)
	{
		init_sprite(sp, game->sprite_order[i], cubstat, sys);
		sprite_draw(sp, game, cubstat, sys);
		i++;
	}
}

void	sprite_sort(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sprite_draw(t_sprite *sp, t_game *g, t_cub *cubstat, t_system *sys)
{
	int	color;
	int	y;

	sp->stripe = sp->draw_start_x;
	while (sp->stripe < sp->draw_end_x)
	{
		sp->tex_x = calc_tex_x(sp, sys->tex[0].size_l);
		if (sp->trans_y >= 0 && sp->stripe >= 0 && sp->stripe <\
			cubstat->width && sp->trans_y < sys->z_buffer[sp->stripe])
		{
			y = sp->draw_start_y;
			while (y < sp->draw_end_y)
			{
				sp->tex_y = calc_tex_y(y, sp, cubstat, sys->tex[0].img_height);
				color = sys->tex[0].addr[(sys->tex[0].size_l / 4) *\
					sp->tex_y + sp->tex_x];
				if ((color & 0x00FFFFFF) != 0)
					sys->buf[y][sp->stripe] = color;
				y++;
			}
		}
		sp->stripe++;
	}
}

void	init_sprite(t_sprite *sp, int sprite_order, t_cub *c, t_system *s)
{
	sp->sp_x = c->sprite[sprite_order].x - s->pos_x;
	sp->sp_y = c->sprite[sprite_order].y - s->pos_y;
	sp->inv_det = 1.0 / (s->plane_x * s->dir_y - s->dir_x * s->plane_y);
	sp->trans_x = sp->inv_det * (s->dir_y * sp->sp_x - s->dir_x * sp->sp_y);
	sp->trans_y =\
		 sp->inv_det * (-s->plane_y * sp->sp_x + s->plane_x * sp->sp_y);
	sp->sprite_screen_x = (int)(c->width / 2) *(1 + sp->trans_x / sp->trans_y);
	sp->v_move_screen = (int)(0.0 / sp->trans_y);
	sp->sp_height = (int)fabs((c->height / sp->trans_y) / 1);
	sp->draw_start_y = -sp->sp_height / 2 + c->height / 2 + sp->v_move_screen;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sp_height / 2 + c->height / 2 + sp->v_move_screen;
	if (sp->draw_end_y >= c->height)
		sp->draw_end_y = c->height;
	sp->sp_width = (int)fabs((c->height / sp->trans_y) / 1);
	sp->draw_start_x = -sp->sp_width / 2 + sp->sprite_screen_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->sp_width / 2 + sp->sprite_screen_x;
	if (sp->draw_end_x >= c->width)
		sp->draw_end_x = c->width;
}
