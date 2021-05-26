/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/09 14:53:35 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cubstat_free(t_cub *cubstat)
{
	free(cubstat->north_tex);
	free(cubstat->south_tex);
	free(cubstat->west_tex);
	free(cubstat->east_tex);
	free(cubstat->sprite_tex);
}

void	image_free(t_system *sys, t_img *tex)
{
	mlx_destroy_image(sys->mlx, sys->img.img);
	mlx_destroy_image(sys->mlx, tex->img);
}

void	buf_free(int **buf, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}

void	image_destroy(t_system *sys)
{
	mlx_destroy_image(sys->mlx, sys->img.img);
	mlx_destroy_image(sys->mlx, sys->tex[0].img);
	mlx_destroy_image(sys->mlx, sys->tex[1].img);
	mlx_destroy_image(sys->mlx, sys->tex[2].img);
	mlx_destroy_image(sys->mlx, sys->tex[3].img);
	mlx_destroy_image(sys->mlx, sys->tex[4].img);
}
