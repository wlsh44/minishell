/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:12:23 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:30:21 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_pipe(t_lstcmd *cmd)
{
	push_back(cmd, TYPE_PIPE, NULL);
	return (0);
}

int	parsing_redirect_input(t_lstcmd *cmd, char **line)
{
	int		ret;
	char	*arg;

	if ((ret = get_arg(line, &arg)) < 0)
		return (ret);
	if (ft_strcmp(arg, "") == 0)
		return (SYNTAX_ERROR);
	push_back(cmd, TYPE_REDIRECT_INPUT, arg);
	return (0);
}

int	parsing_redirect_output(t_lstcmd *cmd, char **line)
{
	int		ret;
	char	*arg;

	if ((ret = get_arg(line, &arg)) < 0)
		return (ret);
	if (ft_strcmp(arg, "") == 0)
		return (SYNTAX_ERROR);
	push_back(cmd, TYPE_REDIRECT_OUTPUT, arg);
	return (0);
}

int	parsing_double_redirect(t_lstcmd *cmd, char **line)
{
	int		ret;
	char	*arg;

	if ((ret = get_arg(line, &arg)) < 0)
		return (ret);
	if (ft_strcmp(arg, "") == 0)
		return (SYNTAX_ERROR);
	push_back(cmd, TYPE_DOUBLE_REDIRECT, arg);
	return (0);
}
