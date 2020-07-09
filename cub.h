//
// Created by Денис on 04/06/2020.
//

#ifndef CUB3D_CUB_H
# define CUB3D_CUB_H
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include <math.h>
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include <limits.h>
#include <sys/resource.h>
#include <sys/times.h>

# define DEFAULT -1
# define SOUTH 0
# define NORTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4
# define step 8
# define one_ray_angle(fov, width) fov * 1.0 / width

typedef struct 	s_line {
	int 		bot;
	int			top;
	int 		x_pos;
	double 		column_height;
}				t_line;

typedef struct	s_ray {
	float 		start_x;
	float 		start_y;
	float 		x;
	float 		y;
	float 		length;
	float 		perp_length;
	int 		wall;
	float 		wall_x;
	float 		delta_x;
	float 		delta_y;
	int 		map_x;
	int 		map_y;
}				t_ray;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct 		s_player	{
	int		x;
	int		y;
	float	dir;
}				t_player;

typedef struct 				s_sprite_list {
	float 					x;
	float 					y;
	float 					distance;
	struct s_sprite_list	*next;
}							t_sprite_list;

typedef struct 		s_texture	{
	void			*img;
	int 			text_x;
	int 			text_y;
	char			*addr;
	int 			width;
	int 			height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct 		s_game {
	int			floor_color;
	int			ceiling_color;
	t_player	*player;
	char		*arr;
	void 		*mlx;
	void 		*mlx_win;
	t_data		image;
	char 		**map;
	int 		win_width;
	int 		win_height;
	int 		map_height;
	int 		map_width;
	t_texture	**textures;
	t_sprite_list *sprites;
	int 		sprites_list_size;

}					t_game;

typedef struct		s_screen_sprite
{
	int		screen_size;
	int 	h_offset;
	int 	v_offset;
	int 	delta_rays;
	float 	dist;
}					t_spr_screen;

typedef struct 		s_input {
	char 			**map;
	int 			floor_color;
	int 			ceiling_color;
	int 			fd_south;
	int 			fd_north;
	int 			fd_west;
	int 			fd_east;
}					t_input;

typedef struct  s_image
{
	int 		width;
	int 		height;
	int 		x_start;
	int 		y_start;
}               t_image;

void            put_rectangle(t_data *img, t_image *format, int color);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
//int    rgb_to_int(unsigned char r, unsigned char g, unsigned char b);
t_player 		*init_start_position(char **map);
double			degrees_to_rad(double degrees);
double 			rad_to_deg(double rad);
int				key_events(int key, t_game *game);
void 			draw_player_pos(t_data *img, t_player *player, int color);
int 	render_next(t_game *game);
int 			my_round(double a);
int 		raycaster(t_game *game, t_texture *texture[]);
int 			find_cos_sign(float deg);
double			cast_next_ray_faster(t_game *game, double deg);
int 			find_sin_sign(float deg);
float 			tan_period(float deg);
float 			get_accute_angle(float deg);
float			negative_cast(float a);
double			cast_next_ray(t_game *game, double deg);
//float 			horizontal_tracing(t_game *game, double deg);
int 			find_x_sign(float deg);
int 			find_y_sign(float deg);
//float 			vertical_tracing(t_game *game, double deg);
int 			check_sect(float coord);
float 		horizontal_tracing(t_game *game, double deg, t_ray *ray);
float 		vertical_tracing(t_game *game, double deg, t_ray *ray);
float 		tracing(t_game *game, double deg);
int 	find_max_width(char **map);
int 	find_max_height(char **map);
char 	*to_array(char **map);
int 	is_looking_up(float deg);
int 	is_looking_right(float deg);
float 	check_deg_round(float player_deg, float deg_to_add);
float 	normalize_deg(float deg);
t_ray 	raytracing(t_game *game, float deg);
void 	draw_line(t_game *game, t_ray ray, t_line line, t_texture **texture);
t_ray 	raycast(t_game *game, double deg);
void 	load_textures(t_game *game, char *str, t_texture **text);
int 		get_texture_color(t_texture *texture, int x, int y);
//t_sprite_list 	*add_to_sprite_list(t_game *game, t_ray ray);
t_sprite_list			*mergesort_list(t_sprite_list *lst);
int		add_to_sprite_list(t_game *game, t_ray ray);
void	init_sprite_list(t_game *game);
int 		lstsize(t_sprite_list *head);
void 	draw_sprite(t_game *game, int sprite_index, float *z_buff, t_ray ray);
void 	init_dist_from_sprite(t_game *game);
t_ray 	bad_raycast(t_game *game, double deg);
void 	draw_all_sprites(t_game *game, float *z_buff, t_ray ray);
int 	starts_with(char *start, char *string);
int 	digit_len(char *string);
int 	skip_spaces(char **string);
int 	parse_color(char *string);
t_list *reader(int fd);
char 	**read_map(t_list *lst);
int 	parse_config(t_list *lst, t_game *game);
int 	init_default_config(t_game *game);
char 	**aligne_map(char **map);
void 	check_map(t_game *game);
int 	check_borders(int i, int j, char **map, t_game *game);
int 	check_begin_pos(char c);
void 		init_start_pos(t_game *game, char c, int i, int j);
t_game		*init_game(int fd);
void 	create_bmp(t_game *game);
int 		get_color(t_data *data, int x, int y);
void 	error(char *message);
void	int_to_bytes(int num, unsigned char *header);
int    rgb_to_int(unsigned char r, unsigned char g, unsigned char b);
int 	shadow_wall(int color, float distance, float k);
double getCPUTime();



#endif //CUB3D_CUB_H
