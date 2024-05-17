/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:11:58 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 14:57:45 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	check_copy(t_map *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->copy[y])
	{
		while (game->copy[y][x])
		{
			if (game->copy[y][x] == 'E'
				|| game->copy[y][x] == 'C' || game->copy[y][x] == 'P')
				return (0);
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

static char	**map_copy(t_map *game)
{
	int	y;

	y = 0;
	game->copy = malloc(sizeof(char *) * (game->rows + 1));
	if (!game->copy)
		error_exit_array("Error: game->copy malloc\n", game, game->copy);
	while (game->map[y])
	{
		game->copy[y] = ft_strdup(game->map[y]);
		y++;
	}
	game->copy[y] = NULL;
	return (game->copy);
}

static void	fill(t_map *game, int y, int x)
{
	if (game->copy[y][x] == '1' || game->copy[y][x] == 'F')
		return ;
	else
		game->copy[y][x] = 'F';
	fill(game, y + 1, x);
	fill(game, y - 1, x);
	fill(game, y, x + 1);
	fill(game, y, x - 1);
}

int	floodfill(t_map *game)
{
	game->copy = map_copy(game);
	if (!game->copy)
		return (0);
	fill(game, game->p_position.y, game->p_position.x);
	if (check_copy(game) == 0)
	{
		error_msg("Error: Floodfill fail\n");
		free_array(game->copy);
		return (0);
	}
	free_array(game->copy);
	return (1);
}
