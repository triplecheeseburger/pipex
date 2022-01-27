/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:30:49 by hakim             #+#    #+#             */
/*   Updated: 2022/01/27 14:30:51 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *chunk, char **envp)
{
	char	**cmd_splitted;
	char	*cmd_pathed;

	cmd_splitted = ft_split(chunk, ' ');
	if (cmd_splitted == 0)
		error(ERR);
	cmd_pathed = concat_path(cmd_splitted[0], envp);
	if (cmd_pathed == 0)
		error(ERR);
	if (execve(cmd_pathed, cmd_splitted, envp) == -1)
		error(ERR);
}

void	child_proc(int fd[2], char **av, char **envp)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		error(ERR);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(av[2], envp);
}

void	parent_proc(int fd[2], char **av, char **envp)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		error(ERR);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		error(ARG);
	if (pipe(fd) == -1)
		error(ERR);
	pid = fork();
	if (pid == -1)
		error(ERR);
	else if (pid == 0)
		child_proc(fd, av, envp);
	else
	{
		waitpid(pid, 0, 0);
		parent_proc(fd, av, envp);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}
