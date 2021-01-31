/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:03:29 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 22:40:25 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_data(char **env, char **args, char *path)
{
	free(path);
	free_double_char(env);
	free_double_char(args);
}

int			ft_exec_file(t_minishell *ms, t_node *node, char *path)
{
	pid_t	pid;
	int		status;
	char	**env;
	char	**args;

	if (!(env = get_env_list(ms))
		|| !(args = ft_bin_args(node->name, node->arg)))
		return (-1);
	signal(SIGINT, &bin_parent_sighandler);
	signal(SIGQUIT, &bin_parent_sighandler);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &bin_child_sighandler);
		signal(SIGQUIT, &bin_child_sighandler);
		status = execve(path, args, env);
		free_data(env, args, path);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) > 0)
		g_exit_status = WEXITSTATUS(status);
	free_data(env, args, path);
	return (1);
}

int			ft_exec_command(t_minishell *ms, t_node *node, char *path)
{
	pid_t	pid;
	int		status;
	char	**env;
	char	**args;

	if (!(env = get_env_list(ms))
		|| !(args = ft_bin_args(node->name, node->arg)))
		return (-1);
	signal(SIGINT, &bin_parent_sighandler);
	signal(SIGQUIT, &bin_parent_sighandler);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &bin_child_sighandler);
		signal(SIGQUIT, &bin_child_sighandler);
		status = execve(path, args, env);
		free_data(env, args, path);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	free_data(env, args, path);
	if (status == 256 && errno == 2)
		return (NO_DIRECTORY);
	return (1);
}
