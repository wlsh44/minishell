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

int	parsing_bin(t_lstcmd *cmd, char **line, char *name)
{
	int		ret;
	char	*arg;
	char	*key;

	arg = NULL;
	while (ft_isspace(**line))
		(*line)++;
	if (**line && (ret = get_arg_echo(line, &arg)) < 0)
		return (ret);
	key = ft_strdup(name);
	push_back_normal(cmd, TYPE_NORMAL, key, arg);
	return (0);
}
