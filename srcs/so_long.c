/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:58:36 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 14:59:03 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	struct_zero(t_map *game)
{
	game->copy = NULL;
	game->columns = 0;
	game->rows = 0;
	game->tokens = 0;
	game->exit = 0;
	game->player = 0;
	game->steps = -1;
	game->collected = 0;
	game->p_position.y = 0;
	game->p_position.x = 0;
	game->e_position.y = 0;
	game->e_position.x = 0;
	game->images = NULL;
	game->p_ani = NULL;
	game->tokens_ani = NULL;
	game->emote_time = 0;
	game->cur_frame = 0;
	game->token_index = 0;
}

static void	the_big_free(t_map *game)
{
	free_array(game->map);
	free(game->images);
	free(game->tokens_ani);
	free(game);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	if (argc != 2)
	{
		error_msg("Arg count wrong\n");
		return (1);
	}
	game = malloc(sizeof(t_map));
	if (!game)
		error_msg_exit("Game malloc error\n", game);
	else
	{
		struct_zero(game);
		map_init(game, argv[1]);
		mlx_starter(game);
	}
	the_big_free(game);
	return (0);
}
