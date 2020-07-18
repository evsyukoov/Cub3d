/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:21:05 by denis             #+#    #+#             */
/*   Updated: 2020/07/12 20:17:02 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB_H
# define CUB3D_CUB_H
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"
# include <math.h>
# include "../GNL/get_next_line.h"
# include "../libft/libft.h"

# define MONITORX 5000
# define MONITORY 1400
# define DEFAULT -1
# define SOUTH 0
# define NORTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4
# define STEP 8
# define ONE_RAY_ANGLE(fov, width) fov * 1.0 / width

typedef struct				s_line
{
	int						bot;
	int						top;
	int						x_pos;
	double					column_height;
}							t_line;

typedef struct				s_ray
{
	float					x;
	float					y;
	float					length;
	float					perp_length;
	int						wall;
	float					wall_x;
	float					delta_x;
	float					delta_y;
	int						map_x;
	int						map_y;
}							t_ray;

typedef struct				s_data
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_data;

typedef struct				s_player {
	int						x;
	int						y;
	float					dir;
}							t_player;

typedef struct				s_sprite_list {
	float					x;
	float					y;
	float					distance;
	struct s_sprite_list	*next;
}							t_sprite_list;

typedef struct				s_texture
{
	void					*img;
	int						text_x;
	int						text_y;
	char					*addr;
	int						width;
	int						height;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_texture;

typedef struct				s_game
{
	int						floor_color;
	int						ceiling_color;
	t_player				*player;
	char					*arr;
	void					*mlx;
	void					*mlx_win;
	t_data					image;
	char					**map;
	int						win_width;
	int						win_height;
	int						map_height;
	int						map_width;
	t_texture				**textures;
	t_sprite_list			*sprites;
	int						sprites_list_size;
	int						(*f)(int, float, float);
}							t_game;

typedef struct				s_screen_sprite
{
	int						screen_size;
	int						h_offset;
	int						v_offset;
	int						delta_rays;
	float					dist;
}							t_spr_screen;

void						my_mlx_pixel_put
(t_data *data, int x, int y, int color);
double						degrees_to_rad(double degrees);
double						rad_to_deg(double rad);
int							action_listener(int key, t_game *game);
int							raycaster(t_game *game);
float						horizontal_tracing
(t_game *game, double deg, t_ray *ray);
float						vertical_tracing
(t_game *game, double deg, t_ray *ray);
int							find_max_width(char **map);
int							find_max_height(char **map);
int							is_looking_up(float deg);
int							is_looking_right(float deg);
float						normalize_deg(float deg);
void						draw_line(t_game *game, t_ray ray, t_line line);
void						load_textures
(t_game *game, char *str, t_texture **text);
int							get_texture_color(t_texture *texture, int x, int y);
t_sprite_list				*mergesort_list(t_sprite_list *lst);
void						init_sprite_list(t_game *game);
int							lstsize(t_sprite_list *head);
void						draw_sprite
(t_game *game, int sprite_index, float *z_buff);
void						init_dist_from_sprite(t_game *game);
void						draw_all_sprites
(t_game *game, float *z_buff);
int							starts_with(char *start, char *string);
int							digit_len(char *string);
int							skip_spaces(char **string);
int							parse_color(char *string);
t_list						*reader(int fd);
char						**read_map(t_list *lst);
int							parse_config(t_list *lst, t_game *game);
int							init_default_config(t_game *game);
char						**aligne_map(char **map);
void						check_map(t_game *game);
int							check_borders
(int i, int j, char **map, t_game *game);
int							check_begin_pos(char c);
void						init_start_pos(t_game *game, char c, int i, int j);
t_game						*init_game(int fd);
void						create_bmp(t_game *game);
int							get_color(t_data *data, int x, int y);
void						error(char *message);
void						int_to_bytes(int num, unsigned char *header);
int							rgb_to_int
(unsigned char r, unsigned char g, unsigned char b);
int							shadow_wall(int color, float distance, float k);
char						*extra_spaces(int len, int max_width);
int							is_full_config(t_game *game);
int							get_texture_index(char *str, char **path);
int							is_starts_with_text(char *str);
int							check_unexpected_symbols(t_game *game);
void						parse_remainder(t_game *game, t_list *lst);
void						north_or_south_wall
(t_ray *result, t_ray ray, float dist, float deg);
void						west_or_east_wall
(t_ray *result, t_ray ray, float dist, float deg);
t_ray						analize_ray(t_game *game, float deg);
t_spr_screen				get_sprite_preferences
(t_game *game, int sprite_index);
int							get_texture_pixel
(t_texture *texture, t_spr_screen spr, int x, int y);
t_sprite_list				*lstget(t_sprite_list *head, int index);
void						draw_sprite_vert_line
(t_game *game, t_spr_screen spr, int i);
int							str_endswith(char *s, char *set);
int							my_exit(void);
int							non_shadow(int color, float distance, float k);

#endif
