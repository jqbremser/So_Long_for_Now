/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:02:05 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/20 11:49:54 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	animate(t_map *game, t_ani *ani)
{
	mlx_image_t	*cur;
	mlx_image_t	*next;
	int			c;
	int			n;

	if (!ani->enabled)
		return ;
	c = game->cur_frame % ani->len;
	n = (game->cur_frame + 1) % ani->len;
	cur = ani->animes[c];
	next = ani->animes[n];
	cur->instances[ani->ids[c]].enabled = false;
	next->instances[ani->ids[n]].enabled = true;
}

mlx_image_t	*png_to_img(mlx_t *mlx, char *file)
{
	mlx_texture_t	*tex;
	mlx_image_t		*temp;

	tex = mlx_load_png(file);
	if (!tex)
		error_msg("Error: tex: PNG_to_IMG");
	temp = mlx_texture_to_image(mlx, tex);
	if (!temp)
		error_msg("Error: temp: PNG_to_IMG");
	mlx_delete_texture(tex);
	mlx_resize_image(temp, PIXELS, PIXELS);
	return (temp);
}

void	animation_loop(void *param)
{
	t_map	*game;
	int		i;

	game = param;
	game->emote_time += game->mlx->delta_time;
	if (game->emote_time > 0.166)
	{
		game->cur_frame++;
		animate(game, game->p_ani);
		i = 0;
		while (i < game->tokens)
			animate(game, game->tokens_ani[i++]);
		game->emote_time = 0;
	}
}
