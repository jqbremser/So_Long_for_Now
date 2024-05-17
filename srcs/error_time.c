/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:35:33 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/17 14:57:10 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	error_msg_exit(char *msg, t_map *game)
{
	error_msg(msg);
	free(game);
	exit(1);
}

void	error_exit_array(char *msg, t_map	*game, char **array)
{
	free_array(array);
	error_msg_exit(msg, game);
}

void	free_array(char **str)
{
	int	y;

	y = 0;
	while (str[y])
		free(str[y++]);
	free(str);
}

void	error_msg(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
}

void	free_animes(mlx_t *mlx, t_ani *ani)
{
	int	y;

	y = 0;
	while (y < ani->len)
		mlx_delete_image(mlx, ani->animes[y++]);
	free(ani->animes);
	free(ani->ids);
	free(ani);
}
