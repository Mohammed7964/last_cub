/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:47:27 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/25 15:42:32 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"
# define HEIGHT 980
# define WIDTH 1580
# define FOV 1.0471975512
# define T_SIZE 50
# define MOVE_SPEED 10
# define ROT_SPEED 0.05
# define COLLISION_BUFFER 15.0
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_ceil_floor
{
	t_texture	*texture;
	int			y;
	int			color;
	int			x_ceil;
	int			y_ceil;
	int			step;
	double		tex_pos;
	int			height_ceil;
}	t_ceil_floor;

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
	int		i;
	double	ray_angle;
	double	distance;
	double	corrected_distance;
	double	wall_height;
	double	wall_top;
	double	projection_distance;
	int		is_vertical;
}	t_render;

typedef struct s_hcheck
{
	double	intersection_x;
	double	intersection_y;
	double	check_y;
	double	step_x;
	double	step_y;
	int		f_up;
	int		f_down;
	int		iterations;
}	t_hcheck;

typedef struct s_vcheck
{
	double	intersection_x;
	double	intersection_y;
	double	check_x;
	double	step_x;
	double	step_y;
	int		f_left;
	int		f_right;
	int		iterations;
}	t_vcheck;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_vector
{
	int	x;
	int	y;
	int	*_x;
	int	*_y;
}	t_vector;

typedef struct s_casting
{
	double	h_hitx;
	double	h_hity;
	double	v_hitx;
	double	v_hity;
	int		tex_x;
}	t_casting;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	bool	f_down;
	bool	f_left;
	bool	f_right;
	bool	f_up;
	bool	stp_x;
	bool	stp_y;
	double	intersection_x;
	double	intersection_y;
	double	closer_dst_x;
	double	closer_dst_y;
	double	v_ok;
	double	h_ok;
	double	angle;
}	t_player;

typedef struct s_ray
{
	double		s_angle;
	double		camera_x;
	int			map_x;
	int			map_y;
	double		o_angle;
	double		distance_r;
	double		feye_distance;
	double		update_angle;
	double		distance_projection_plan;
	double		h_wall_projection;
	double		wall_top;
	double		corrected_distance;
	t_player	player;
}	t_ray;

typedef struct s_weapon
{
	t_texture	frames[8];
	int			frame_count;
	int			current;
	int			animating;
}	t_weapon;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	value_c;
	int	value_f;
}	t_color;

typedef struct s_cub
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	char		*ceil_texture;
	char		*floor_texture;
	char		*nopath;
	char		*sopath;
	char		*espath;
	char		*wepath;
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bpp;
	int			map_started;
	int			map_ended;
	int			line_len;
	int			endian;
	double		size_x;
	double		size_y;
	double		y_colom;
	double		x_row;
	char		*map;
	char		**map_lines;
	char		*texture;
	char		*_no;
	char		*_so;
	char		*_we;
	char		*_ea;
	char		*_f;
	char		*_c;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	t_vector	player_pos;
	t_player	player;
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_east;
	t_texture	tex_west;
	t_texture	tex_ceil;
	t_texture	tex_floor;
	t_weapon	weapon;
	int			floor_color;
	int			ceil_color;
	t_keys		keys;
	t_ray		ray;
	t_color		color;
	t_casting	cast;
	t_render	r;
}	t_cub;

size_t		ft_strlen(char *str);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		init_cub(t_cub *cub);
void		pad_map(char **map);
int			pars_av(int ac, char **av);
int			ft_isdigit(int c);
void		init_texture(char *path, t_cub *cub);
int			check_path(char *path);
int			is_path(char **split, t_cub *cub, char *line);
int			is_empty_line(char *line);
void		move_right(t_cub *cub);
void		join(t_cub *cub, char **path);
int			read_map(char *av, t_cub *cub);
int			handle_colors_str(char *color);
int			number_of_char(t_cub *cub);
int			parse_color_c(char *line, t_color *color);
void		rotate_left(t_cub *cub);
int			parse_color_f(char *line, t_color *color);
int			pars_av(int ac, char **av);
void		init_texture(char *path, t_cub *cub);
int			check_collision_fast(t_cub *cub, double x, double y);
int			handle_colors_str(char *color);
int			ft_split_len(char **split);
int			read_map(char *av, t_cub *cub);
void		move_forward(t_cub *cub);
int			render_frame(t_cub *cub);
void		rotate_right(t_cub *cub);
double		normalize_angle(double angle);
void		move_left(t_cub *cub);
void		join(t_cub *cub, char **path);
void		cleanup(t_cub *cub);
int			close_window(t_cub *cub);
int			ft_split_len(char **split);
int			pars_map(t_cub *cub);
int			handle_empty_line(t_cub *cub, char *line);
int			check_maps(char **map);
void		move_backward(t_cub *cub);
int			is_map_line(char *line);
int			number_of_char(t_cub *cub);
int			handle_spaces_textures(char *line);
int			check_maps(char **map);
int			check_ziro(t_cub *cub);
int			new_lines_map(t_cub *cub);
void		ft_free_split(char **split);
void		free_map_lines(t_cub *cub);
void		find_p(t_cub *cub);
void		change_space(t_cub *cub);
void		clean_newline(char *str);
int			is_path(char **split, t_cub *cub, char *line);
int			pars_map(t_cub *cub);
int			handle_colors2(char **split, t_cub *cub);
void		change_space(t_cub *cub);
int			can_start_map(t_cub *cub);
int			handle_textures2(char **split, t_cub *cub);
int			check_path(char *path);
void		find_p(t_cub *game);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
void		ft_free_split(char **split);
int			ft_atoi(const char *str);
int			ft_split_len(char **split);
int			len_h(char **line);
void		mlx_initcub(t_cub *cub);
void		failed_w(void);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		init_player_raycasting(t_cub *cub);
void		load_textures(t_cub *cub);
void		load_texture(t_cub *cub, t_texture *tex, char *path);
void		draw_frame(t_cub *cub);
int			get_texture_color(t_texture *tex, int tex_x, int tex_y);
void		my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
int			is_wall(t_cub *cub, double x, double y);
double		h_check(t_cub *cub, double *hit_x, double *hit_y, double angle);
double		v_check(t_cub *cub, double *hit_x, double *hit_y, double angle);
void		my_mlx_pixel_put(t_cub *data, int x, int y, int color);
int			is_wall(t_cub *cub, double x, double y);
void		checker_ray_angle(t_render *r);
int			ft_error(char *str);
void		draw_ceiling_floor_column(t_cub *cub, int x,
				int wall_top, int wall_bottom);
void		load_textures(t_cub *cub);
void		load_texture(t_cub *cub, t_texture *tex, char *path);
t_texture	*get_wall_texture(t_cub *cub, double ray_angle, int is_vertical);
int			get_texture_color(t_texture *tex, int tex_x, int tex_y);
void		ft_loop_tex(t_wall_tex *wt, t_render *r, t_cub *cub);
char		*ft_strtrim(char *s1, char *set);
#endif
