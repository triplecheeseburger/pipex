/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:25:32 by hakim             #+#    #+#             */
/*   Updated: 2022/01/28 01:25:34 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		write(2, "Example: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 46);
		exit(EXIT_FAILURE);
	}
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
