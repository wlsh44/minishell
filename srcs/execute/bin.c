/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:08:54 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 22:15:48 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_command(char *name)
{
	char	*str;

	if (!(str = ft_strrchr(name, '/')))
		return (name);
	return (str + 1);
}

static void	free_data(char **env, char **args, char *path)
{
	free(path);
	free_double_char(env);
	free_double_char(args);
}

int			ft_execute_bin(t_minishell *ms, char *path, char *arg)
{
	pid_t	pid;
	int		status;
	char	**env_list;
	char	**args;

	if (!(env_list = get_env_list(ms))
		|| !(args = ft_bin_args(get_command(path), arg)))
		return (-1);
	signal(SIGINT, &bin_parent_sighandler);
	signal(SIGQUIT, &bin_parent_sighandler);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &bin_child_sighandler);
		signal(SIGQUIT, &bin_child_sighandler);
		status = execve(path, args, env_list);
		free_data(env_list, args, path);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) > 0)
		g_exit_status = WEXITSTATUS(status);
	free_data(env_list, args, path);
	return (g_exit_status);
}

int			ft_bin(t_minishell *ms, t_node *node)
{
	char	*path;
	char	*tmp;

	if (ft_file_exists(node->name))
		return (ft_execute_bin(ms, ft_strdup(node->name), node->arg));
	tmp = ft_strchr(node->name, '/');
	path = ft_check_abs_path(ms, node->name);
	if (!path)
	{
		if (tmp == NULL)
			cmd_error(WRONG_CMD);
		else
			execute_error(NO_DIRECTORY);
		return (ERR_COMMAND_NOT_FOUND);
	}
	else
		return (ft_execute_bin(ms, path, node->arg));
}
