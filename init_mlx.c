/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:17:27 by omaezzem          #+#    #+#             */
/*   Updated: 2025/12/23 23:04:48 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handling_keys(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == KEY_W)
		cub->keys.w = 1;
	else if (keycode == KEY_S)
		cub->keys.s = 1;
	else if (keycode == KEY_A)
		cub->keys.a = 1;
	else if (keycode == KEY_D)
		cub->keys.d = 1;
	else if (keycode == KEY_LEFT)
		cub->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		cub->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->keys.w = 0;
	else if (keycode == KEY_S)
		cub->keys.s = 0;
	else if (keycode == KEY_A)
		cub->keys.a = 0;
	else if (keycode == KEY_D)
		cub->keys.d = 0;
	else if (keycode == KEY_LEFT)
		cub->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		cub->keys.right = 0;
	return (0);
}

void	failed_mlx(void)
{
	ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
	exit(EXIT_FAILURE);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	static int		last_x;
	int				delta_x;
	double			rotation;
	const double	sensitivity = 0.002;

	last_x = -1;
	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	if (delta_x != 0)
	{
		rotation = delta_x * sensitivity;
		cub->player.angle = normalize_angle(cub->player.angle + rotation);
	}
	last_x = x;
	return (0);
}

void	mlx_initcub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		failed_mlx();
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!cub->window)
		failed_w();
	cub->keys.w = 0;
	cub->keys.s = 0;
	cub->keys.a = 0;
	cub->keys.d = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
	load_textures(cub);
	mlx_hook(cub->window, 2, 1L << 0, handling_keys, cub);
	mlx_hook(cub->window, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->window, 17, 0, close_window, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
	mlx_loop(cub->mlx);
}
