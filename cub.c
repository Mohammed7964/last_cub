/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:47:10 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/23 21:10:26 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	init_map(t_cub *cub, char *file)
{
	if (!read_map(file, cub))
		return (0);
	if (!new_lines_map(cub))
		return (0);
	if (!handle_colors_str(cub->_F) || !handle_colors_str(cub->_C))
		return (0);
	if (!pars_map(cub))
		return (0);
	if (cub->map_lines)
	{
		ft_free_split(cub->map_lines);
		cub->map_lines = NULL;
	}
	cub->map_lines = ft_split(cub->map, '\n');
	if (!cub->map_lines)
		return (0);
	find_p(cub);
	if (!check_maps(cub->map_lines))
		return (0);
	if (!check_ziro(cub))
		return (0);
	change_space(cub);
	pad_map(cub->map_lines);
	return (1);
}

static char	*append_line(char *map, char *line)
{
	char	*tmp;
	char	*new_map;

	if (!map || !line)
		return (NULL);
	tmp = map;
	new_map = ft_strjoin(tmp, line);
	free(tmp);
	return (new_map);
}

static char	*append_newline(char *map)
{
	char	*tmp;
	char	*new_map;

	if (!map)
		return (NULL);
	tmp = map;
	new_map = ft_strjoin(tmp, "\n");
	free(tmp);
	return (new_map);
}

static int	build_map_string(t_cub *cub)
{
	int		i;

	if (!cub)
		return (0);
	free(cub->map);
	cub->map = ft_strdup("");
	if (!cub->map)
		return (0);
	i = 0;
	while (cub->map_lines[i])
	{
		cub->map = append_line(cub->map, cub->map_lines[i]);
		if (!cub->map)
			return (0);
		cub->map = append_newline(cub->map);
		if (!cub->map)
			return (0);
		i++;
	}
	return (1);
}

void	f(){system("leaks cub3D");}
int parse_color(char *line, t_color *color)
{
    char **rgb;
    int i;

    rgb = ft_split(line, ',');
    if (!rgb)
        return (1);

    i = 0;
    while (rgb[i])
        i++;
    if (i != 3)
        return (1);

    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);

    if (color->r < 0 || color->r > 255 ||
        color->g < 0 || color->g > 255 ||
        color->b < 0 || color->b > 255)
        return (1);

    color->value = (color->r << 16) | (color->g << 8) | color->b;

    ft_free_split(rgb);
    return (0);
}
int	main(int ac, char **av)
{
	t_cub	cub;
	t_color color;

	atexit(f);
	init_cub(&cub, &color);
	if (!pars_av(ac, av))
	{
		cleanup(&cub);
		return (printf("Error: Invalid arguments\n"), EXIT_FAILURE);
	}
	if (!init_map(&cub, av[1]))
	{
		cleanup(&cub);
		return (printf("Error: Failed to init map\n"), EXIT_FAILURE);
	}
	build_map_string(&cub);
	if (parse_color(cub._F, &color) || parse_color(cub._C, &color))
	{
		cleanup(&cub);
		return (printf("Error: Invalid color format\n"), EXIT_FAILURE);
	}
	init_player_raycasting(&cub);
	mlx_initcub(&cub);
	cleanup(&cub);
	return (0);
}
