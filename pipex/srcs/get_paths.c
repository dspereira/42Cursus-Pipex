/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:38 by dsilveri          #+#    #+#             */
/*   Updated: 2022/03/28 12:37:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_paths	*get_paths(char **envp)
{
	t_paths	*p;
	char	*path_str;
	char	*word;
	int		word_size;
	int		i;

	word = "PATH=";
	word_size = ft_strlen(word);
	p = oom_guard(malloc(sizeof(t_paths)));
	i = 0;
	while (envp[i])
	{
		path_str = ft_strnstr(envp[i], word, word_size);
		if (path_str)
		{
			p->paths = ft_split(&path_str[word_size], ':');
			break ;
		}
		i++;
	}
	save_alloc_paths(p);
	oom_guard(p->paths);
	return (p);
}
