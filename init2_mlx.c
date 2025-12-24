/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:03:24 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/23 23:05:07 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	normalize_angle(double angle)
{
	const double	two_pi = 2.0 * M_PI;

	while (angle < 0.0)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}

int	check_collision_fast(t_cub *cub, double x, double y)
{
	if (is_wall(cub, x, y))
		return (1);
	if (is_wall(cub, x + COLLISION_BUFFER, y)
		|| is_wall(cub, x - COLLISION_BUFFER, y)
		|| is_wall(cub, x, y + COLLISION_BUFFER)
		|| is_wall(cub, x, y - COLLISION_BUFFER))
		return (1);
	return (0);
}

void	move_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cos(cub->player.angle) * MOVE_SPEED;
	new_y = cub->player.pos_y + sin(cub->player.angle) * MOVE_SPEED;
	if (!check_collision_fast(cub, new_x, new_y))
	{
		cub->player.pos_x = new_x;
		cub->player.pos_y = new_y;
	}
}

void	move_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cos(cub->player.angle) * MOVE_SPEED;
	new_y = cub->player.pos_y - sin(cub->player.angle) * MOVE_SPEED;
	if (!check_collision_fast(cub, new_x, new_y))
	{
		cub->player.pos_x = new_x;
		cub->player.pos_y = new_y;
	}
}

void	move_left(t_cub *cub)
{
	double	new_x;
	double	new_y;
	double	side_angle;

	side_angle = cub->player.angle - M_PI_2;
	new_x = cub->player.pos_x + cos(side_angle) * MOVE_SPEED;
	new_y = cub->player.pos_y + sin(side_angle) * MOVE_SPEED;
	if (!check_collision_fast(cub, new_x, new_y))
	{
		cub->player.pos_x = new_x;
		cub->player.pos_y = new_y;
	}
}
