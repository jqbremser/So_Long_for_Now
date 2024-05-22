/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_an_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:50:12 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/22 13:54:15 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_img	*images_init(t_map	*game)
{
	t_img	*assets;

	assets = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!assets)
		return (NULL);
	load_all_assets(game, assets);
	if (!assets->wall || !assets->floor || !assets->exit_open
		|| !assets->exit_closed)
	{
		error_msg("Error: images_init\n");
		free(assets);
		return (NULL);
	}
	return (assets);
}

t_ani	*p_animes_init(t_map	*game)
{
	t_ani	*ani;

	ani = malloc(sizeof(t_ani));
	ani->ids = malloc(sizeof(int *) * 4);
	ani->animes = malloc(sizeof(mlx_image_t *) * 4);
	ani->pos.y = game->p_position.y;
	ani->pos.x = game->p_position.x;
	ani->len = 4;
	ani->animes[0] = png_to_img(game->mlx, "./assets/anis/priest1_v2_1.png");
	ani->animes[1] = png_to_img(game->mlx, "./assets/anis/priest1_v2_2.png");
	ani->animes[2] = png_to_img(game->mlx, "./assets/anis/priest1_v2_3.png");
	ani->animes[3] = png_to_img(game->mlx, "./assets/anis/priest1_v2_4.png");
	if (!ani)
	{
		error_msg("Error: loading anis\n");
		return (NULL);
	}
	return (ani);
}

t_ani	*t_animes_init(t_map	*game)
{
	t_ani	*ani;

	ani = malloc(sizeof(t_ani));
	ani->ids = malloc(sizeof(int *) * 4);
	ani->animes = malloc(sizeof(mlx_image_t *) * 4);
	ani->len = 4;
	ani->pos.y = game->p_position.y;
	ani->pos.x = game->p_position.x;
	ani->animes[0] = png_to_img(game->mlx, "./assets/anis/skull_v2_1.png");
	ani->animes[1] = png_to_img(game->mlx, "./assets/anis/skull_v2_2.png");
	ani->animes[2] = png_to_img(game->mlx, "./assets/anis/skull_v2_3.png");
	ani->animes[3] = png_to_img(game->mlx, "./assets/anis/skull_v2_4.png");
	if (!ani)
	{
		error_msg("Error: loading anis\n");
		return (NULL);
	}
	return (ani);
}

void	step_counter_init(t_map *game)
{
	char	*s;
	char	*temp;

	game->steps += 1;
	s = ft_itoa(game->steps);
	if (!s)
		return ;
	temp = ft_strjoin("Steps:", s);
	mlx_delete_image(game->mlx, game->step_counter);
	game->step_counter = mlx_put_string(game->mlx,
			temp, game->columns * PIXELS / 2, 8);
	free(s);
	free(temp);
}
