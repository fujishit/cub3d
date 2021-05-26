/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/13 06:05:45 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_setup(t_game *game, char *filepath)
{
	int	fd;
	int	i;

	i = 0;
	if (extension_check(filepath, ".cub") == 1)
		input_error_exit("please '*.cub' file", FILE_ERROR);
	game->sys.mlx = mlx_init();
	if (game->sys.mlx == NULL)
		game_error_exit(game, "init error", MLX_ERROR);
	cubstat_init(&game->cubstat, game->sys.mlx);
	map_init(game->cubstat.map);
	fd = open(filepath, O_RDONLY);
	cubstat_input(&game->cubstat, fd, 0);
	close(fd);
	map_check(&game->cubstat, game->cubstat.map);
	mlx_setup(game, &game->cubstat, &game->sys);
	system_init(&game->sys, &game->cubstat);
	load_texture(game, &game->cubstat, game->sys.tex);
}

int	extension_check(char *filepath, char *extension)
{
	size_t	file_len;
	size_t	ext_len;

	file_len = ft_strlen(filepath);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (1);
	while (extension[ext_len] == filepath[file_len])
	{
		if (ext_len == 0)
			return (0);
		ext_len--;
		file_len--;
	}
	return (1);
}
