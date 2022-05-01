/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:41:09 by dsilveri          #+#    #+#             */
/*   Updated: 2022/05/01 22:11:09 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../ft_printf/ft_printf.h"

# define PROGRAM_NAME "pipex"

//#define malloc(x) NULL

#define NO_TYPE 	0
#define TYPE_CMDS 	1
#define TYPE_FDS 	2
#define TYPE_PATHS 	3

typedef struct s_files
{
	char	*in;
	char	*out;
}	t_files; 

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

typedef struct s_cmds
{
	int		size;
	t_cmd	*cmd;
}	t_cmds;

typedef struct s_fd
{
	int	w;
	int	r;
}	t_fd;

typedef struct s_fds
{
	int		size;
	t_fd	*fd;
}	t_fds;

typedef struct s_paths
{
	char	**paths;
}	t_paths;

typedef struct s_data
{
	t_cmds	*cmds;
	t_fds	*fds;
	t_paths	*paths;
	t_files files;
	char **env;
}	t_data;

typedef struct s_alloc_mem
{
	t_cmds	*cmds;
	t_fds	*fds;
	t_paths	*paths;
}	t_alloc_mem;

/* get_cmds.c */
t_cmds	*get_cmds(int size, char **cmds, char **paths);

/* free_cmds.c */
void	free_cmds(t_cmds *cmds);

/* get_path.c */
t_paths	*get_paths(char **envp);

/* free_path.c */
void	free_paths(t_paths *paths);

/* get_fds.c */
t_fds	*get_fds(int size);

/* close_pipe_fds.c */
void	close_pipe_fds(t_fds *fds);

/* utils.h */
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

/* utils2.h */
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

/* error_handling.c */
int		sys_error(int err);
int		file_error(int err, char *file);
void	cmd_not_found_error(const char *cmd_path, const char *cmd);
void	*oom_guard(void *p);
void	*oom_guard2(void *p);

/* alloc_mem.c */
void	init_alloc_mem(void);
void	save_alloc_mem(void *mem, int type);
void	free_alloc_mem(void);

#endif