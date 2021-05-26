#include "../cub3d.h"

int	res_duplicate_check(void)
{
	static int	count;

	if (0 < count++)
		return (1);
	return (0);
}

int	tex_duplicate_check(int	tex)
{
	static int	north;
	static int	west;
	static int	east;
	static int	south;
	static int	sprite;

	if (tex == 0 && 0 < north++)
		return (1);
	else if (tex == 1 && 0 < south++)
		return (1);
	else if (tex == 2 && 0 < west++)
		return (1);
	else if (tex == 3 && 0 < east++)
		return (1);
	else if (tex == 4 && 0 < sprite++)
		return (1);
	return (0);
}

int	color_duplicate_check(char CF)
{
	static int	ceiling;
	static int	floor;

	if (CF == 'C')
		if (0 < ceiling++)
			return (1);
	else if (CF == 'F')
		if (0 < floor++)
			return (1);
}
