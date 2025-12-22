/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:47:27 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/20 16:03:08 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <stdbool.h>
# include "get_next_line/get_next_line.h"

# define HEIGHT 980
# define WIDTH 1580
# define FOV (M_PI / 3.0)   /* 60 degrees */
# define T_SIZE 50
# define MOVE_SPEED 10
# define ROT_SPEED 0.07
#define COLLISION_BUFFER 30.0

#define KEY_W        119  // 'w'
#define KEY_A        97   // 'a'
#define KEY_S        115  // 's'
#define KEY_D        100  // 'd'

#define KEY_LEFT     65361 // Left Arrow
#define KEY_RIGHT    65363 // Right Arrow

#define KEY_ESC      65307 // Escapewwww


typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;

typedef struct s_ceil_floor
{
    t_texture   *texture;
    int	y;
    int color;
    int x_ceil;
    int y_ceil;
    int step;
    double tex_pos;
    int height_ceil;
}     t_ceil_floor;

typedef struct s_wall_tex
{
	int				original_wall_top;
	int				wall_top;
	int				wall_bottom;
	int				height_wall;
	int				is_vertical;
	double			ray_angle;
	t_texture		*texture;
	double			wall_hit_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;
	int				color;
}	t_wall_tex;

typedef struct s_render
{
    int     i;
    double  ray_angle;
    double  distance;
    double  corrected_distance;
    double  wall_height;
    double  wall_top;
    double  projection_distance;
    int     is_vertical;
}   t_render;

typedef struct s_hcheck
{
    double intersection_x;
	double intersection_y;
	double check_y;
	double step_x;
	double step_y;
    int f_up;
    int f_down;
    int iterations;
}   t_hcheck;

typedef struct s_vcheck
{
    double intersection_x;
	double intersection_y;
	double check_x;
	double step_x;
	double step_y;
    int f_left;
    int f_right;
    int iterations;
}   t_vcheck;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}   t_keys;

typedef struct s_vector
{
    int x;
    int y;
    int *_x;
    int *_y;
}               t_vector;

typedef struct s_casting
{
    double h_hitx;
    double h_hity;
    double v_hitx;
    double v_hity;

    int     tex_x;     // <-- ADDED for textures
}   t_casting;

typedef struct s_player
{
    double  pos_x;      // Player position (world coords)
    double  pos_y;
    bool    f_down;
    bool    f_left;
    bool    f_right;
    bool    f_up;
    bool    stp_x;
    bool    stp_y;
    double  intersection_x;
    double  intersection_y;
    double  closer_dst_x;
    double  closer_dst_y;
    double  v_ok;
    double  h_ok;
    double  angle;      // Player viewing angle in radians (0 = east, PI/2 = south, etc.)
}   t_player;

typedef struct s_ray
{
    double  s_angle;
    double  camera_x;      // X-coordinate in camera space ([-1,1])
    int     map_x;       // Current square of the map
    int     map_y;
    double  o_angle;
    double  distance_r;
    double  feye_distance;
    double  update_angle;
    double  distance_projection_plan;
    double  h_wall_projection;
    double  wall_top;
    double  corrected_distance;
    t_player player;
}   t_ray;

typedef struct s_weapon
{
    t_texture frames[8];  // NOT void **, but an array of t_texture structs
    int frame_count;
    int current;
    int animating;
}   t_weapon;


typedef struct s_cub
{
    char *north_texture;
    char *south_texture;
    char *east_texture;
    char *west_texture;
    char *ceil_texture;
    char *floor_texture;
    char *nopath;
    char *sopath;
    char *espath;
    char *wepath;
    /* MLX related */
    void        *mlx;
    void        *window;
    void        *img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
    double      size_x;
    double      size_y;
    double      y_colom;
    double      x_row;

    /* Map related */
    char        *map;
    char        **map_lines;

    /* Texture paths (strings) */
    char        *texture;
    char        *_NO;
    char        *_SO;
    char        *_WE;
    char        *_EA;
    char        *_F;
    char        *_C;

    /* Texture flags (int) */
    int         NO;
    int         SO;
    int         WE;
    int         EA;
    int         F;
    int         C;

    /* Player */
    t_vector    player_pos;
    t_player    player;

    /* Raycasting textures */
    t_texture   tex_north;
    t_texture   tex_south;
    t_texture   tex_east;
    t_texture   tex_west;
    t_texture   tex_ceil;
    t_texture   tex_floor;
    t_weapon    weapon;

    /* Colors */
    int         floor_color;
    int         ceil_color;

    /* Keys */
    t_keys      keys;
    t_ray       ray;
    t_casting cast;
    t_render r;
}   t_cub;


char    *creat_text(int fd, char *str);
char    *get_current_line(char *line);
char    *next_list(char *text);
char    *get_next_line(int fd);
size_t	ft_strlen(char *s);
char    *ft_substr(char *s, unsigned int start, size_t len);
char    *ft_strdup(char *s1);
char    *ft_strjoin(char *s1, char *s2);
size_t  ft_strlen(char *s);
char    **ft_split(char *s, char c);
int     is_empty_line(char *line);
void    init_cub(t_cub *cub);
int     pars_av(int ac, char **av);
void    init_texture(char *path, t_cub *cub);
int     check_path(char *path);
int     is_path(char **split, t_cub *cub, char *line);
void    join(t_cub *cub, char **path);
int     read_map(char *av, t_cub *cub);
int     handle_colors_F(t_cub *cub);
int     handle_colors_C(t_cub *cub);
int     number_of_char(t_cub *cub);
int     pars_map(t_cub *cub);
void    change_space(t_cub *cub);
int     handle_map(t_cub *cub);
void    find_p(t_cub *game);
int	ft_strcmp(char *s1, char *s2);
void	ft_free_split(char **split);
int	ft_atoi(const char *str);
int	ft_split_len(char **split);
int     len_h(char **line);
void    mlx_initcub(t_cub *cub);
void    failed_w(void);
void    ft_putstr_fd(char *s, int fd);
void    ft_putchar_fd(char c, int fd);
void    init_player_raycasting(t_cub *cub);
void    load_textures(t_cub *cub);
void    load_texture(t_cub *cub, t_texture *tex, char *path);
void    draw_frame(t_cub *cub);
void    init_ray(t_cub *cub, t_ray *ray, int x);
void    perform_dda(t_cub *cub, t_ray *ray);
void    calculate_wall_distance(t_cub *cub, t_ray *ray);
void    draw_wall(t_cub *cub, t_ray *ray, int x);
int get_texture_color(t_texture *tex, int tex_x, int tex_y);
void    my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void    draw_ceiling(t_cub *cub);
void    draw_floor(t_cub *cub);
int     key_press(int keycode, t_cub *cub);
int     key_release(int keycode, t_cub *cub);
void    handle_keys(t_cub *cub);
void    update_player(t_cub *cub);
void    move_player(t_cub *cub, double dir);
void    strafe_player(t_cub *cub, double dir);
void    rotate_player(t_cub *cub, double dir);
int is_wall(t_cub *cub, double x, double y);
double h_check(t_cub *cub, double *hit_x, double *hit_y, double angle);
double v_check(t_cub *cub, double *hit_x, double *hit_y, double angle);
void my_mlx_pixel_put(t_cub *data, int x, int y, int color);
int is_wall(t_cub *cub, double x, double y);
void	checker_ray_angle(t_render *r);
int ft_error(char *str);
void draw_ceiling_floor_column(t_cub *cub, int x, int wall_top, int wall_bottom);
void	load_textures(t_cub *cub);
void	load_texture(t_cub *cub, t_texture *tex, char *path);
t_texture *get_wall_texture(t_cub *cub, double ray_angle, int is_vertical);
int get_texture_color(t_texture *tex, int tex_x, int tex_y);
void	ft_loop_tex(t_wall_tex *wt, t_render *r, t_cub *cub);
void	render(t_cub *cub);
void	update_weapon(t_cub *cub);
void	draw_weapon(t_cub *cub);
void	load_weapon(t_cub *cub);
#endif