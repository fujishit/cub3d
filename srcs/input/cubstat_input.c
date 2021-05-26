/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubstat_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/14 12:15:23 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cubstat_input(t_cub *cubstat, int fd, int flag)
{
	int	ret;

	ret = element_input(cubstat, fd, flag);
	if (ret != 0)
	{
		close(fd);
		cubstat_free(cubstat);
		if (ret == DUPLICATE_ERROR)
			input_error_exit("duplicate element", ret);
		else if (ret == TEX_EXTENSION_ERROR)
			input_error_exit("extension error", TEXTURE_ERROR);
		else if (FORMAT_ERROR <= ret)
			input_error_exit("unexpected element", ret);
		else if (ret == READ_ERROR)
			input_error_exit("can't find file", READ_ERROR);
		else if (ret == FILE_ERROR)
			input_error_exit("not enough elements", FORMAT_ERROR);
	}
	if (map_input(cubstat, fd, 0, 0) != 0)
	{
		cubstat_free(cubstat);
		input_error_exit("unexpected map", MAP_ERROR);
	}
}

int	element_input(t_cub *cubstat, int fd, int flag)
{
	char	*line;
	int		ret;
	int		input_count;

	ret = -1;
	input_count = 0;
	line = NULL;
	while (0 < get_next_line(fd, &line))
	{
		ret = check_element(line, cubstat, flag);
		free(line);
		line = NULL;
		if (ret == 0)
			input_count += 1;
		else if (FORMAT_ERROR <= ret)
			return (ret);
		if (input_count == 8)
			return (0);
	}
	if (ret == -1)
		return (READ_ERROR);
	free(line);
	return (FILE_ERROR);
}

int	check_element(char *line, t_cub *cubstat, int flag)
{
	if (line[0] == 'R' && line[1] == ' ')
	{
		if (flag == 0)
			return (check_resolution(line, cubstat));
		else if (flag == 1)
			return (save_check_resolution(line, cubstat));
	}
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (check_texture(line, &cubstat->north_tex, 0));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (check_texture(line, &cubstat->south_tex, 1));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (check_texture(line, &cubstat->west_tex, 2));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (check_texture(line, &cubstat->east_tex, 3));
	else if (line[0] == 'S' && line[1] == ' ')
		return (check_texture(line, &cubstat->sprite_tex, 4));
	else if (line[0] == 'F' && line[1] == ' ')
		return (check_color(line, &cubstat->f_color));
	else if (line[0] == 'C' && line[1] == ' ')
		return (check_color(line, &cubstat->c_color));
	else if (line[0] == '\0')
		return (1);
	return (ELEMENT_ERROR);
}
