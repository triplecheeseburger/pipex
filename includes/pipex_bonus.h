/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:31:11 by hakim             #+#    #+#             */
/*   Updated: 2022/01/27 00:31:12 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum e_error
{
	ERR,
	ARG
}	t_error;

typedef enum e_open
{
	READ,
	WRITE,
	APPEND
}	t_open;

void	here_doc(int infile, char *limiter, int ac);
void	repeat_proc(char *cmd, char **envp);
void	execute(char *chunk, char **envp);
void	error(int mode);
void	px_dup(int fd1, int fd2);
int		px_open(char *file, int mode);
char	*concat_path(char *cmd, char **envp);
char	*ft_free_str(char *str);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif