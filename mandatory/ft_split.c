/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:45:39 by hakim             #+#    #+#             */
/*   Updated: 2021/11/11 22:38:41 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	wordcount(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}	
	return (count);
}

static int	get_si(int *i, char const *s, char c)
{
	int	size;

	size = 0;
	while (s[*i] != '\0' && s[*i] == c)
		*i += 1;
	if (s[*i] == '\'')
	{
		while (s[*i] != '\0')
		{
			size += 1;
			*i += 1;
			if (s[*i] == '\'')
			{
				size += 1;
				*i += 1;
				return (size);
			}
		}
	}
	while (s[*i] != '\0' && s[*i] != c)
	{
		size += 1;
		*i += 1;
	}
	return (size);
}

void	ft_free_split(char **big, int bigdex)
{
	int	index;

	index = bigdex - 1;
	while (index >= 0)
	{
		free(big[index]);
		big[index] = 0;
		--index;
	}
	free(big);
	big = 0;
}

static void	go_split(char **big, char const *s, char c, int bigdex)
{
	int	i;
	int	size;
	int	sindex;

	i = 0;
	while (s[i] != '\0')
	{
		size = get_si(&i, s, c);
		if (size == 0)
			continue ;
		big[bigdex] = (char *)malloc(sizeof(char) * (size + 1));
		if (big[bigdex] == 0)
			return (ft_free_split(big, bigdex));
		sindex = 0;
		i -= size;
		while (sindex < size)
		{
			if (s[i] == '\'' && ++i)
				--size;
			else
				big[bigdex][sindex++] = s[i++];
		}
		big[bigdex++][sindex] = '\0';
	}
	big[bigdex] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**big;
	int		size;
	int		bigdex;

	if (s == 0)
		return (0);
	size = wordcount(s, c);
	big = (char **)malloc(sizeof(char *) * (size + 1));
	if (big == 0)
		return (0);
	bigdex = 0;
	go_split(big, s, c, bigdex);
	return (big);
}	
