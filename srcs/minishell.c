/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:57:08 by schang            #+#    #+#             */
/*   Updated: 2021/01/06 21:26:16 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

typedef struct	s_token
{
	char	*cmd;
	int		type;
	void	*prev;
	void	*next;
	char	*data;
}				t_token;

char	*skip_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

void	parsing_command(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = skip_space(str);
	while (tmp[i])
	{
		while (tmp[i] && tmp[i] != ' ')
		{
			printf("%c", tmp[i]);
			i++;
		}
		while (tmp[i] && tmp[i] == ' ')
			i++;
		printf("\n");
	}




	// printf("%s|\n", tmp);
}

int	main(void)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		//printf("%s\n", line);
		parsing_command(line);


		free(line);
	}
	free(line);

	return (0);
}
