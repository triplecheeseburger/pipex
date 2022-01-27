/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:22:02 by hakim             #+#    #+#             */
/*   Updated: 2022/01/28 01:22:03 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_free_str(char *str)
{
	free(str);
	str = 0;
	return (0);
}

void	error(int mode)
{
	if (mode == ERR)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (mode == ARG)
	{
		write(2, "Error: Bad Arguments\n", 21);
		write(2, "Example: ./pipex infile \"cmd1\" \"cmd2\" ... ", 42);
		write(2, "\"cmdX\" outfile\n", 15);
		write(2, "     OR: ./pipex here_doc LIMITER \"cmd1\" \"", 42);
		write(2, "cmd2\" ... \"cmdX\" outfile\n", 25);
		exit(EXIT_FAILURE);
	}
}

void	px_dup(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error(ERR);
	close(fd1);
}

int	px_open(char *file, int mode)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			error(ERR);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			error(ERR);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			error(ERR);
	}
	return (fd);
}

char	*concat_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		++i;
	paths = ft_split(envp[i] + 5, ':');
	if (paths == 0)
		error(ERR);
	i = 0;
	while (paths[i] != 0)
	{
		temp = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		++i;
		ft_free_str(path);
	}
	return (0);
}
