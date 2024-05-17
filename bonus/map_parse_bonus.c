/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:17:35 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/16 13:07:18 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	set_positions(t_map *game, int x, int y)
{
	if (game->map[y][x] == 'P')
	{
		game->p_position.y = y;
		game->p_position.x = x;
		game->player++;
	}
	else if (game->map[y][x] == 'E')
	{
		game->e_position.y = y;
		game->e_position.x = x;
		game->exit++;
	}
	else if (game->map[y][x] == 'C')
		game->tokens++;
}

static int	edge_check(t_map *game, int x, int y)
{
	while (y < game->rows)
	{
		while (x < game->columns)
		{
			if ((y == 0 || y == (game->rows - 1)) && game->map[y][x] != '1')
			{
				error_msg("Error: Top/bottom edge fail\n");
				return (0);
			}
			if ((y > 0 && y < (game->rows - 1)) && (game->map[y][0] != '1'
				|| game->map[y][game->columns - 1] != '1'))
			{
				error_msg("Error: side edge fail\n");
				return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

static int	char_check(t_map *game, int x, int y)
{
	while (y < game->rows)
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1' || game->map[y][x] == '0'
				|| game->map[y][x] == 'P' || game->map[y][x] == 'E'
				|| game->map[y][x] == 'C' || game->map[y][x] == '\n')
			{
				set_positions(game, x, y);
				x++;
			}
			else
			{
				error_msg("Error: char_check fail\n");
				return (0);
			}
		}
		x = 0;
		y++;
	}
	return (1);
}

static int	count_check(t_map *game, int y)
{
	size_t	length;

	y = 0;
	length = ft_strlen_delim(game->map[0], '\n');
	if (game->player != 1 || game->exit != 1 || game->tokens < 1)
	{
		error_msg("Error: player/exit/token count_check\n");
		return (0);
	}
	while (game->map[y])
	{
		if (ft_strlen_delim(game->map[y], '\n') != length)
		{
			error_msg("Error: Row is too long\n");
			return (0);
		}
		y++;
	}
	return (1);
}

int	map_parse(t_map *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (edge_check(game, x, y) == 0 || char_check(game, x, y) == 0
		|| count_check(game, y) == 0 || floodfill(game) == 0)
		return (0);
	return (1);
}
