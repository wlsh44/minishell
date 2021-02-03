/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:13:03 by schang            #+#    #+#             */
/*   Updated: 2021/02/03 20:55:10 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_unset(char **line, char *arg)
{
	int	ret;

	ret = get_arg_key(line, &arg);
	if (!ret && !(ft_isseparator(**line) || ft_isspace(**line) || !**line))
		ret = NOT_VAILD_IDENTIFIER;
	if (ret < 0)
	{
		*(arg++) = ret;
		while (!(ft_isseparator(**line) || ft_isspace(**line) || !**line))
			(*line)++;
	}
	while (ft_isspace(**line))
		(*line)++;
	*(arg++) = ' ';
	*arg = '\0';
	return (0);
}

int	parsing_unset(t_lstcmd *cmd, char **line)
{
	char	*arg;
	int		size;

	while (ft_isspace(**line))
		(*line)++;
	size = get_last_char(*line);
	arg = ft_substr(*line, 0, size);
	(*line) += size;
	while (ft_isspace(**line))
		(*line)++;
	push_back(cmd, TYPE_UNSET, arg);
	return (0);
}
