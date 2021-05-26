#include "../cub3d.h"

int	save_check_resolution(char *line, t_cub *cubstat)
{
	int	i;

	i = 2;
	if (res_duplicate_check() == 1)
		return (DUPLICATE_ERROR);
	while (line[i] == ' ')
		i++;
	if (!('0' <= line[i] && line[i] <= '9'))
		return (RESOLUTION_ERROR);
	i = save_resolution_input(line, i, &cubstat->width, WIN_WIDTH_MAX);
	if (i == -1)
		input_error_exit("too big savefile", RESOLUTION_ERROR);
	while (line[i] == ' ')
		i++;
	if (!('0' <= line[i] && line[i] <= '9'))
		return (RESOLUTION_ERROR);
	i = save_resolution_input(line, i, &cubstat->height, WIN_HEIGHT_MAX);
	if (i == -1)
		input_error_exit("too big savefile", RESOLUTION_ERROR);
	if (line[i] != '\0')
		return (RESOLUTION_ERROR);
	if (0 == cubstat->width || 0 == cubstat->height)
		return (RESOLUTION_ERROR);
	return (0);
}

int	save_resolution_input(char *line, int i, int *res, int max)
{
	while ('0' <= line[i] && line[i] <= '9')
	{
		*res = *res * 10 + (line[i] - '0');
		if (max < *res)
			return (-1);
		i++;
	}
	return (i);
}
