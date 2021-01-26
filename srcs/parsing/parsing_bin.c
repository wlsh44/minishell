/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:11:54 by schang            #+#    #+#             */
/*   Updated: 2021/01/27 00:40:09 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_bin(t_lstcmd *cmd, char **line)
{
	int		i;
	int		ret;
	char	*str;
	char	*arg;
	char	*tmp;

	i = 0;
	while ((*line)[i] && !ft_isspace((*line)[i]))
		i++;
	str = ft_substr(*line, 0, i);
	*line = *line + i;
	while (ft_isspace(**line))
		(*line)++;
	if ((ret = get_arg_echo(line, &arg)) < 0)
		return (ret);
	/*
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		str[ft_strlen(str) - 1] = 0;
	*/
	push_back_normal(cmd, TYPE_NORMAL, str, arg);
	return (0);
}
