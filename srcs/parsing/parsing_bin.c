/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:11:54 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 23:08:19 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quote(char *arg)
{
	int sq;
	int dq;

	sq = 0;
	dq = 0;
	while (*arg)
	{
		if (*arg == '\'')
			sq = sq ? 0 : 1;
		else if (*arg == '\"')
			dq = dq ? 0 : 1;
		arg++;
	}
	if (sq || dq)
		return (false);
	return (true);
}

int		parsing_bin(t_lstcmd *cmd, char **line, char *name)
{
	int		size;
	char	*arg;
	char	*key;

	while (ft_isspace(**line))
		(*line)++;
	size = get_last_char(*line);
	arg = ft_substr(*line, 0, size);
	if (!check_quote(arg))
		return (WRONG_QUOTE);
	(*line) += size;
	while (ft_isspace(**line))
		(*line)++;
	key = ft_strdup(name);
	push_back_normal(cmd, TYPE_NORMAL, key, arg);
	return (0);
}
