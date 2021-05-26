#include "../cub3d.h"

int	calc_tex_x(t_sprite *sp, int size_l)
{
	int	ret;

	ret = (int)((sp->stripe - (-sp->sp_width / 2 + sp->sprite_screen_x)) * \
		size_l / 4 / sp->sp_width);
	if (ret < 0)
		return (0);
	return (ret);
}

int	calc_tex_y(int y, t_sprite *sp, t_cub *cubstat, int img_height)
{
	int	ret;

	ret = ((((y - sp->v_move_screen) * 256 - cubstat->height * \
		128 + sp->sp_height * 128) * img_height) / sp->sp_height) / 256;
	if (ret < 0)
		return (0);
	return (ret);
}
