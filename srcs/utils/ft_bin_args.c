/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:34:24 by schang            #+#    #+#             */
/*   Updated: 2021/01/29 21:40:56 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_bin_args(char *arg)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i]))
			i++;
		while (arg[i] && !ft_isspace(arg[i]))
			i++;
		cnt++;
	}
	return (cnt);
}

char		**ft_bin_args(char *cmd, char *arg)
{
	int		i;
	int		cnt;
	int		offset;
	char	**args;

	i = 0;
	cnt = count_bin_args(arg);
	if (!(args = ft_calloc(sizeof(char *), cnt + 2)))
		return (NULL);
	args[0] = ft_strdup(cmd);
	i = 0;
	cnt = 1;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i]))
			i++;
		offset = i;
		while (arg[i] && !ft_isspace(arg[i]))
			i++;
		args[cnt] = ft_substr(arg, offset, i - offset);
		cnt++;
	}
	return (args);
}
