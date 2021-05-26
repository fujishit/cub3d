/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubstat_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/14 09:11:17 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_resolution(char *line, t_cub *cubstat)
{
	int	i;

	i = 2;
	if (res_duplicate_check() == 1)
		return (DUPLICATE_ERROR);
	while (line[i] == ' ')
		i++;
	if (!('0' <= line[i] && line[i] <= '9'))
		return (RESOLUTION_ERROR);
	i = resolution_input(line, i, &cubstat->width, cubstat->max_win_width);
	while (line[i] == ' ')
		i++;
	if (!('0' <= line[i] && line[i] <= '9'))
		return (RESOLUTION_ERROR);
	i = resolution_input(line, i, &cubstat->height, cubstat->max_win_height);
	if (line[i] != '\0')
		return (RESOLUTION_ERROR);
	if (0 == cubstat->width || 0 == cubstat->height)
		return (RESOLUTION_ERROR);
	return (0);
}

int	resolution_input(char *line, int i, int *res, int max)
{
	while ('0' <= line[i] && line[i] <= '9')
	{
		*res = *res * 10 + (line[i++] - '0');
		if (max < *res)
		{
			*res = max;
			while ('0' <= line[i] && line[i] <= '9')
				i++;
			break ;
		}
	}
	return (i);
}

int	check_texture(char *line, char **texture_path, int tex)
{
	char	*tmp;
	int		i;

	i = 2;
	if (tex_duplicate_check(tex) == 1)
		return (DUPLICATE_ERROR);
	if (extension_check(line, ".xpm") == 1)
		return (TEX_EXTENSION_ERROR);
	while (line[i] == ' ')
		i++;
	tmp = ft_strdup(line + i);
	if (tmp == NULL)
		return (MALLOC_ERROR);
	*texture_path = tmp;
	return (0);
}

int	check_color(char *line, t_rgb *color)
{
	int	i;

	i = 2;
	if (color_duplicate_check(line[0]) == 1)
		return (DUPLICATE_ERROR);
	while (line[i] == ' ')
		i++;
	i = color_input(line, i, &color->r);
	if (i == -1)
		return (COLOR_ERROR);
	else if (line[i++] != ',')
		return (COLOR_ERROR);
	i = color_input(line, i, &color->g);
	if (i == -1)
		return (COLOR_ERROR);
	else if (line[i++] != ',')
		return (COLOR_ERROR);
	i = color_input(line, i, &color->b);
	if (i == -1)
		return (COLOR_ERROR);
	else if (line[i] != '\0')
		return (COLOR_ERROR);
}

int	color_input(char *line, int i, int *color)
{
	if (!('0' <= line[i] && line[i] <= '9'))
		return (-1);
	while ('0' <= line[i] && line[i] <= '9')
	{
		*color = *color * 10 + (line[i++] - '0');
		if (255 < *color)
			return (-1);
	}
	return (i);
}
