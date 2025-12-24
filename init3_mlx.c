/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:04:34 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/23 23:48:11 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_right(t_cub *cub)
{
	double	new_x;
	double	new_y;
	double	side_angle;

	side_angle = cub->player.angle + M_PI_2;
	new_x = cub->player.pos_x + cos(side_angle) * MOVE_SPEED;
	new_y = cub->player.pos_y + sin(side_angle) * MOVE_SPEED;
	if (!check_collision_fast(cub, new_x, new_y))
	{
		cub->player.pos_x = new_x;
		cub->player.pos_y = new_y;
	}
}

void	rotate_left(t_cub *cub)
{
	cub->player.angle = normalize_angle(cub->player.angle - ROT_SPEED);
}

void	rotate_right(t_cub *cub)
{
	cub->player.angle = normalize_angle(cub->player.angle + ROT_SPEED);
}

int	render_frame(t_cub *cub)
{
	if (cub->keys.w)
		move_forward(cub);
	if (cub->keys.s)
		move_backward(cub);
	if (cub->keys.a)
		move_left(cub);
	if (cub->keys.d)
		move_right(cub);
	if (cub->keys.left)
		rotate_left(cub);
	if (cub->keys.right)
		rotate_right(cub);
	draw_frame(cub);
	return (0);
}

int	close_window(t_cub *cub)
{
	if (cub->tex_north.img)
		mlx_destroy_image(cub->mlx, cub->tex_north.img);
	if (cub->tex_south.img)
		mlx_destroy_image(cub->mlx, cub->tex_south.img);
	if (cub->tex_east.img)
		mlx_destroy_image(cub->mlx, cub->tex_east.img);
	if (cub->tex_west.img)
		mlx_destroy_image(cub->mlx, cub->tex_west.img);
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	exit(0);
	return (0);
}
