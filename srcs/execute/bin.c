/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:08:54 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 22:43:04 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_shell_error(char *str, int err)
{
	if (err == WRONG_CMD)
		shell_cmd_error(str, err);
	else if (err == PERMISSION_DENIED)
		shell_exec_error(str, PERMISSION_DENIED);
	else if (err == NO_DIRECTORY)
		shell_exec_error(str, NO_DIRECTORY);
	else if (err == IS_A_DIRECTORY)
		shell_exec_error(str, IS_A_DIRECTORY);
}

static int	ft_bin_file(t_minishell *ms, t_node *node)
{
	int	ret;

	if ((ret = ft_check_file(node->name)) > 0)
	{
		if ((ret = ft_exec_file(ms, node, ft_strdup(node->name))) > 0)
			return (1);
		else
			return (0);
	}
	else
	{
		print_shell_error(ft_strdup(node->name), ret);
		return (0);
	}
	return (0);
}

static int	ft_bin_command(t_minishell *ms, t_node *node)
{
	char	*path;
	int		ret;

	path = NULL;
	if ((ret = ft_check_command(ms, node->name, &path)) > 0)
	{
		if ((ret = ft_exec_command(ms, node, path)) > 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (!path)
			path = ft_strdup(node->name);
		print_shell_error(path, ret);
		return (0);
	}
	return (0);
}

int			ft_bin(t_minishell *ms, t_node *node)
{
	char	*tmp;

	if (ms->cmd->head->next->type == TYPE_PIPE)
	{
		cmd_error(SYNTAX_ERROR);
		return (g_exit_status = 2);
	}
	tmp = ft_strchr(node->name, '/');
	if (tmp)
		return (ft_bin_file(ms, node));
	else
		return (ft_bin_command(ms, node));
}
