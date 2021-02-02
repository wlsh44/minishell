/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:46:07 by schang            #+#    #+#             */
/*   Updated: 2021/02/03 00:18:34 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(char *arg, int *i)
{
	int	quote;
	int	o;

	quote = 0;
	o = *i;
	if (ft_isquote(arg[o]))
	{
		quote = arg[o++];
		while (arg[o])
		{
			if (arg[o++] == quote)
			{
				*i = o;
				break ;
			}
		}
	}
	*i = o;
}

int		count_args(char *arg)
{
	int	i;
	int	cnt;
	int	offset;

	i = 0;
	cnt = 0;
	offset = 0;
	while (arg[i])
	{
		if (ft_isquote(arg[i]))
			skip_quote(arg, &i);
		else if (i != 0 && arg[i - 1] != '\\' && ft_isspace(arg[i]))
		{
			cnt++;
			while (arg[i] && ft_isspace(arg[i]))
				i++;
			offset = i;
		}
		else
			i++;
	}
	if (offset < i)
		cnt++;
	return (cnt);
}

int		check_key(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || arg[i] == '=' || ft_isdigit(arg[i]))
		return (NOT_VAILD_IDENTIFIER);
	while (is_key_char(arg[i]))
		i++;
	if (arg[i] && arg[i] != '=')
		return (NOT_VAILD_IDENTIFIER);
	return (0);
}
