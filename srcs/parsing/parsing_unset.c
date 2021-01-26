/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:13:03 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 20:37:42 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_arg_unset(char **line, char *arg)
{
	int ret;

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

int parsing_unset(t_lstcmd *cmd, char **line)
{
	int		arg_num;
	char	*arg;
	char	*tmp;
	char	*save;

	while (ft_isspace(**line))
			(*line)++;
	arg_num = get_arg_num(*line);
	arg = ft_strdup("");
	while (arg_num--)
	{
		tmp = malloc(sizeof(char) * (get_arg_size(*line) + 2));
		get_arg_unset(line, tmp);
		save = arg;
		arg = ft_strjoin(arg, tmp);
		free(save);
		free(tmp);
	}
	push_back(cmd, TYPE_UNSET, arg);
	return (0);
}
