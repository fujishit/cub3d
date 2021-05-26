/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 06:39:08 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_texture(t_game *game, t_cub *cubstat, t_img *tex)
{
	if ((load_image(&tex[0], game->sys.mlx, cubstat->sprite_tex)) != 0)
		game_error_exit(game, "sprite texture load error", TEXTURE_ERROR);
	else if ((load_image(&tex[1], game->sys.mlx, cubstat->north_tex)) != 0)
		game_error_exit(game, "north texture load error", TEXTURE_ERROR);
	else if ((load_image(&tex[2], game->sys.mlx, cubstat->south_tex)) != 0)
		game_error_exit(game, "south texture load error", TEXTURE_ERROR);
	else if ((load_image(&tex[3], game->sys.mlx, cubstat->west_tex)) != 0)
		game_error_exit(game, "west texture load error", TEXTURE_ERROR);
	else if ((load_image(&tex[4], game->sys.mlx, cubstat->east_tex)) != 0)
		game_error_exit(game, "east texture load error", TEXTURE_ERROR);
}

int	load_image(t_img *tex, void *mlx, char *path)
{
	tex->img = mlx_xpm_file_to_image(\
		mlx, path, &tex->img_width, &tex->img_height);
	if (tex->img == NULL)
		return (1);
	tex->addr = (int *)mlx_get_data_addr(\
		tex->img, &tex->bpp, &tex->size_l, &tex->endian);
	if (tex->addr == NULL)
		return (2);
	return (0);
}
