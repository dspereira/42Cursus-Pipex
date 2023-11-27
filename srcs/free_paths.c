/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:14 by dsilveri          #+#    #+#             */
/*   Updated: 2022/03/28 12:37:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_paths(t_paths *paths)
{
	int		i;
	char	**m;

	if (!paths)
		return ;
	m = paths->paths;
	if (m)
	{
		i = 0;
		while (m[i])
		{
			free(m[i]);
			i++;
		}
		free(m);
	}
	free(paths);
}
