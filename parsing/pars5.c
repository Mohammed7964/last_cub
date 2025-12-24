/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:27:03 by mel-badd          #+#    #+#             */
/*   Updated: 2025/12/24 15:43:09 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	open_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	return (fd);
}

static int	process_line(t_cub *cub, char *line)
{
	char	**split;

	if (!handle_spaces_textures(line))
		return (0);
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	if (!is_path(split, cub, line))
	{
		ft_free_split(split);
		return (0);
	}
	join(cub, split);
	ft_free_split(split);
	return (1);
}

static int	check_textures(t_cub *cub)
{
	if (cub->no != 1 || cub->so != 1 || cub->we != 1 || cub->ea != 1
		|| cub->f != 1 || cub->c != 1)
	{
		printf("Error:\n Missing textures or colors \
		(NO=%d SO=%d WE=%d EA=%d F=%d C=%d)\n",
			cub->no, cub->so, cub->we, cub->ea, cub->f, cub->c);
		return (0);
	}
	if (!cub->north_texture || !cub->south_texture
		|| !cub->west_texture || !cub->east_texture)
	{
		printf("Error:\n Failed to store texture paths\n");
		return (0);
	}
	return (1);
}

int	read_map(char *av, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = open_file(av);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(cub, line))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!check_textures(cub))
		return (0);
	return (1);
}

int	handle_spaces_textures(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i - 1] == ' ')
		return (0);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i - 1] == ' ')
		return (0);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i - 1] == ' ')
		return (0);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i - 1] == ' ')
		return (0);
	if (line[i] == 'F' && line[i - 1] == ' ')
		return (0);
	if (line[i] == 'C' && line[i - 1] == ' ')
		return (0);
	return (1);
}
