/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:30:49 by hakim             #+#    #+#             */
/*   Updated: 2022/01/29 21:38:57 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	repeat_proc(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error(ERR);
	pid = fork();
	if (pid == -1)
		error(ERR);
	if (pid == 0)
	{
		close(fd[0]);
		px_dup(fd[1], STDOUT_FILENO);
		execute(cmd, envp);
	}
	else
	{
		close(fd[1]);
		px_dup(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, 0, 0);
	}
}

void	here_doc(int infile, char *limiter, int ac)
{
	char	*line;

	line = 0;
	if (ac < 6)
		error(ARG);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			ft_free_str(line);
			break ;
		}
		write(infile, line, ft_strlen(line));
		ft_free_str(line);
	}
	close(infile);
	infile = open("pipex_temp", O_RDONLY, 0777);
}

int	main(int ac, char **av, char **envp)
{
	int		infile;
	int		outfile;
	int		index;

	if (ac < 5)
		error(ARG);
	index = 2;
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ++index)
	{
		outfile = px_open(av[ac - 1], APPEND);
		infile = px_open("pipex_temp", WRITE);
		here_doc(infile, av[2], ac);
	}
	else
		infile = px_open(av[1], READ);
	px_dup(infile, STDIN_FILENO);
	while (index < ac - 2)
		repeat_proc(av[index++], envp);
	if (ft_strncmp(av[1], "here_doc", 8) != 0)
		outfile = px_open(av[ac - 1], WRITE);
	px_dup(outfile, STDOUT_FILENO);
	if (access("pipex_temp", F_OK) == 0)
		unlink("pipex_temp");
	execute(av[ac - 2], envp);
	return (0);
}
