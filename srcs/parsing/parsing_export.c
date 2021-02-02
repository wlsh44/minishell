/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:04:16 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 22:52:19 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_value(char **line, char **arg)
{
	int	ret;

	ret = 0;
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line))
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line)
				*(*arg)++ = *(*line)++;
		}
		else if (ft_isquote(**line))
		{
			if ((ret = get_arg_quote(line, arg)) < 0)
				return (ret);
		}
		else
			*(*arg)++ = *(*line)++;
	}
	**arg = '\0';
	return (0);
}

int	get_arg_export(char **line, char *arg)
{
	int	ret;

	ret = get_arg_key(line, &arg);
	if (!ret && **line == '=')
	{
		*(arg++) = *(*line)++;
		if ((ret = get_arg_value(line, &arg)) < 0)
			*(arg++) = ret;
	}
	else if (!ret && !(ft_isseparator(**line)
		|| ft_isspace(**line) || !**line))
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

int	parsing_export(t_lstcmd *cmd, char **line)
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
	push_back(cmd, TYPE_EXPORT, arg);
	return (0);
}
