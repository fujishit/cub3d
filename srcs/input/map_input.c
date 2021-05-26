#include "../cub3d.h"

int	map_input(t_cub *cubstat, int fd, int ret, int i)
{
	char	*line;

	i = 0;
	while (0 < get_next_line(fd, &line) && line[0] == '\0')
		free(line);
	if ((mapline_input(cubstat, cubstat->map[i++], line)) == MAP_ERROR)
		return (MAP_ERROR);
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (!(0 < ret && line[0] != '\0'))
			break ;
		if ((mapline_input(cubstat, cubstat->map[i++], line)) == MAP_ERROR)
			return (MAP_ERROR);
	}
	if (line[0] != '\0')
	{
		if ((mapline_input(cubstat, cubstat->map[i++], line)) == MAP_ERROR)
			return (MAP_ERROR);
	}
	else
		free (line);
	if (ret == 0)
		return (0);
	return (MAP_ERROR);
}

int	mapline_input(t_cub *cubstat, char *mapline, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (MAP_WIDTH_MAX < len)
	{
		free(line);
		return (MAP_ERROR);
	}
	ft_strlcpy(mapline, line, MAP_WIDTH_MAX);
	cubstat->map_height++;
	if (cubstat->map_width < len)
		cubstat->map_width = len;
	else if (MAP_HEIGHT_MAX < cubstat->map_height)
	{
		free(line);
		return (MAP_ERROR);
	}
	free(line);
	return (0);
}
