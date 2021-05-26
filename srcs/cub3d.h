/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:53:11 by mfujishi          #+#    #+#             */
/*   Updated: 2021/04/14 11:56:25 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
/*
# ifdef MAC
#  include "../minilibx_mms_20200219/mlx.h"
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
*/
# include "../minilibx-linux/mlx.h"
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
//# endif

# define MAP_WIDTH_MAX 1024
# define MAP_HEIGHT_MAX 1024
# define WIN_WIDTH_MAX 10000
# define WIN_HEIGHT_MAX 10000
# define SP_NUM_MAX 10000

# define SUCCESS 0
# define READ_ERROR 1
# define FILE_ERROR 2
# define ARG_ERROR 3
# define MLX_ERROR 5
# define MALLOC_ERROR 9
# define FORMAT_ERROR 10
# define RESOLUTION_ERROR 11
# define EXTENSION_ERROR 12
# define MAP_ERROR 13
# define NO_CLOSE_MAP_ERROR 14
# define TEXTURE_ERROR 15
# define COLOR_ERROR 16
# define DUPLICATE_ERROR 17
# define TEX_EXTENSION_ERROR 18
# define ELEMENT_ERROR 19

# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include "./input/get_next_line/get_next_line.h"

typedef struct s_key
{
	int			a;
	int			d;
	int			s;
	int			w;
	int			esc;
}	t_key;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}	t_rgb;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}	t_img;

typedef struct s_wall
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			color;
}	t_wall;

typedef struct s_s
{
	double		x;
	double		y;
}	t_s;

typedef struct s_sprite
{
	double		sp_x;
	double		sp_y;
	double		inv_det;
	double		trans_x;
	double		trans_y;
	int			sprite_screen_x;
	int			v_move_screen;
	int			sp_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sp_width;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			tex_x;
	int			tex_y;
}	t_sprite;

typedef struct s_pair
{
	double		first;
	int			second;
}	t_pair;

typedef struct s_cub
{
	int			width;
	int			height;
	int			map_width;
	int			map_height;
	int			flag;
	char		*north_tex;
	char		*south_tex;
	char		*west_tex;
	char		*east_tex;
	char		*sprite_tex;
	t_rgb		f_color;
	t_rgb		c_color;
	int			start_x;
	int			start_y;
	char		start_dir;
	char		map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
	int			max_win_height;
	int			max_win_width;
	int			num_sprites;
	t_s			sprite[SP_NUM_MAX];
}	t_cub;

typedef struct s_system
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	t_img		img;
	t_key		key;
	t_img		tex[5];
	int			**buf;
	double		z_buffer[WIN_WIDTH_MAX];
	int			north_with;
	double		move_speed;
	double		rot_speed;
}	t_system;

typedef struct s_game
{
	t_cub		cubstat;
	t_system	sys;
	int			sprite_order[SP_NUM_MAX];
	double		sprite_distance[SP_NUM_MAX];
}	t_game;

void	error_exit(char *s, int errornum);
void	input_error_exit(char *s, int errornum);
void	cubstat_free(t_cub *cubstat);
void	buf_free(int **buf, int height);
void	image_destroy(t_system *sys);
void	game_error_exit(t_game *game, char *s, int errornum);
void	image_free(t_system *sys, t_img *tex);
void	game_end(t_game *game);
void	gnl_free(char *line);
void	game_init(t_game *game);
int		extension_check(char *filepath, char *extension);
void	cubstat_init(t_cub *cubstat, void *mlx);
void	map_init(char map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX]);
void	system_init(t_system *sys, t_cub *cubstat);
void	player_dir(t_system *sys, t_cub *cubstat);
void	cubstat_input(t_cub *cubstat, int fd, int flag);
int		element_input(t_cub *cubstat, int fd, int flag);
void	input_check(t_cub *cubstat);
int		check_element(char *line, t_cub *cubstat, int flag);
int		check_resolution(char *line, t_cub *cubstat);
int		resolution_input(char *line, int i, int *res, int max);
int		res_duplicate_check(void);
int		check_texture(char *line, char **texture_path, int tex);
int		tex_duplicate_check(int tex);
int		check_advtex(t_game *game, t_img *tex);
int		check_color(char *line, t_rgb *color);
int		color_duplicate_check(char CF);
int		color_input(char *line, int i, int *color);
int		map_input(t_cub *cubstat, int fd, int ret, int i);
int		mapline_input(t_cub *cubstat, char *mapline, char *line);
void	map_check(t_cub *cubstat, char map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX]);
void	map_player(t_cub *cubstat, int y, int x, char c);
void	map_sprite(t_cub *cubstat, int y, int x);
int		map_fill(t_cub *cubstat, int y, int x);
int		map_isvalid(t_cub *cubstat);
void	mlx_setup(t_game *game, t_cub *cub, t_system *sys);
void	load_texture(t_game *game, t_cub *cubstat, t_img *tex);
int		load_image(t_img *tex, void *mlx, char *path);
void	game_setup(t_game *game, char *filepath);
int		game_loop(t_game *game);
void	loop_wall(int x, t_wall *wall, t_game *game);
void	loop_raycast(t_game *game, t_system *sys, t_cub *cubstat);
void	wall_init(int x, t_wall *wall, t_game *game, t_system *sys);
void	wall_raycast(int x, t_wall *wall, t_game *game, t_cub *cubstat);
void	wall_texture(t_wall *wall, t_game *game, t_system *sys, t_cub *cubstat);
void	wall_pattern(t_wall *wall, t_system *sys, t_cub *cubstat);
void	wall_color(int x, t_wall *wall, t_game *game, t_cub *cubstat);
void	sprite_place(t_sprite *sp, t_game *game, t_cub *cubstat, t_system *sys);
void	sprite_sort(int *order, double *dist, int amount);
void	sort_order(t_pair *orders, int amount);
void	sprite_draw(t_sprite *sp, t_game *g, t_cub *cubstat, t_system *sys);
int		calc_tex_x(t_sprite *sp, int size_l);
int		calc_tex_y(int y, t_sprite *sp, t_cub *cubstat, int img_height);
void	init_sprite(t_sprite *sp, int sprite_order, t_cub *cub, t_system *sys);
void	game_draw(t_game *game, t_system *sys, t_cub *cubstat);
int		create_trgb(int t, int r, int g, int b);
int		game_key(int keycode, t_game *game);
void	game_key_wd(t_cub *cubstat, t_system *sys, double x, double y);
void	game_key_as(t_cub *cubstat, t_system *sys, double x, double y);
void	game_key_rotate(t_cub *cubstat, t_system *sys, int dir);
int		close_window(int keycode, t_game *game);
void	game_save(char **arg, t_game *game, t_system *sys, t_cub *cubstat);
int		save_check_resolution(char *line, t_cub *cubstat);
int		save_resolution_input(char *line, int i, int *res, int max);
void	save_screenshot(t_game *game, t_cub *cubstat, t_system *sys);
void	save_header(int fd, t_cub *cubstat);
void	save_data(int fd, t_cub *cubstat, t_system *sys);
void	save_color(unsigned char *bmp, int color);

#endif
