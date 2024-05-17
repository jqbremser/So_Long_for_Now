/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:22:55 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/16 15:17:57 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	map_rows(t_map *game, char *arg)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	line = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		error_msg_exit("Error: Where Map? FD failed\n", game);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			if (line[0] == '\n')
				error_msg_exit("Error: Extra line at bottom\n", game);
		}
		i++;
	}
	free (line);
	close (fd);
	return (i);
}

static char	**map_to_str(t_map *game, char *arg)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	game->map = (char **)ft_calloc((size_t)game->rows + 1, sizeof(char *));
	if (!game->map)
		error_exit_array("Error: Calloc fail\n", game, game->map);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		error_exit_array("Error: FD open fail\n", game, game->map);
	while (game->rows > i)
	{
		game->map[i] = get_next_line(fd);
		i++;
	}
	close (fd);
	return (game->map);
}

void	map_init(t_map *game, char *arg)
{
	if (!arg)
		error_msg_exit("Error: No Map\n", game);
	if ((ft_strlen(arg) <= 4) || (arg[ft_strlen(arg) - 5] == '/')
		|| (ft_strncmp(arg + (ft_strlen(arg) - 4), ".ber", 4) != 0))
		error_msg_exit("Bad Map. Must end with .ber\n", game);
	game->rows = map_rows(game, arg);
	game->map = map_to_str(game, arg);
	if (!game->map || !game->map[0])
		error_msg_exit("Error: Empty Map!", game);
	game->columns = (ft_strlen(game->map[0]) - 1);
	if ((map_parse(game)) == 0)
		error_exit_array("Error: Invalid Map!\n", game, game->map);
	if (!game->map || !game->map[0])
		error_msg_exit("Error: Empty Map!\n", game);
}
