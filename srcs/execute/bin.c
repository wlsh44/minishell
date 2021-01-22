/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:08:54 by schang            #+#    #+#             */
/*   Updated: 2021/01/22 17:10:50 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_list(t_minishell *ms)
{
	int			cnt;
	char		*tmp;
	char		**env_list;
	t_env_node	*cur;

	cnt = 0;
	cur = ms->env->head->next;
	while (cur != ms->env->tail) {
		cur = cur->next;
		cnt++;
	}
	if (!(env_list = ft_calloc(sizeof(char *), (cnt + 1))))
		return (NULL);
	cur = ms->env->head->next;
	cnt = 0;
	while (cur != ms->env->tail) {
		tmp = ft_strjoin(cur->name, "=");
		env_list[cnt] = ft_strjoin(tmp, cur->val);
		free(tmp);
		cur = cur->next;
		cnt++;
	}
	return (env_list);
}

void	free_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	free(str);
}
int	ft_file_exists(const char *file)
{
	struct stat	buf;
	int			exists;

	exists = stat(file, &buf);
	if (exists < 0)
		return (0);
	return (1);
}

char	*get_command(char *name)
{
	char	*str;

	if (!(str = ft_strrchr(name, '/')))
		return (name);
	return (str + 1);
}

char	**ft_bin_args(char *cmd, char *arg)
{
	int		i;
	int		cnt;
	int		offset;
	char	**args;

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
		args[cnt] = ft_substr(arg, offset, i);
		cnt++;
	}
	return (args);
}


void	child_sig_int(int code)
{
	if (code == 2)
	{
		write(1, "\n", 1);
		exit(0);
	}
}

void	child_sig_quit(int code)
{
	exit(0);
}

void        override_signal(int signal_no)
{
    if (signal_no == SIGINT)
        ft_putchar_fd('\n', 1);
    else if (signal_no == SIGQUIT)
        ft_putstr_fd("Quit: 3\n", 2);
}

int	ft_execute_bin(t_minishell *ms, char *path, char *arg)
{
	pid_t	pid;
	int		ret;
	char	**env_list;
	char	**args;

	if (!(env_list = get_env_list(ms)))
		return (-1);
	if (!(args = ft_bin_args(get_command(path), arg)))
		return (-1);
	signal(SIGINT, &override_signal);
	signal(SIGQUIT, &override_signal);
	pid = fork();
	ret = 1;
	if (pid > 0)
		waitpid(pid, &ret, 0);
	else
	{
		signal(SIGINT, &child_sig_int);
		signal(SIGQUIT, &child_sig_quit);


		ret = execve(path, args, env_list);
		free(path);
		free_double_char(env_list);
		free_double_char(args);
		exit(ret);
	}
	return (0);
}

char	*ft_check_abs_path(t_minishell *ms, char *name)
{
	char	*path;
	char	**dir;
	char	*tmp;
	char	*abs_path;
	int		ret;

	if (!(path = get_env_value(ms->env, "PATH")))
		return (0);
	if (!(dir = ft_split(path, ':')))
		return (0);
	while (*dir)
	{
		tmp = ft_strjoin(*dir, "/");
		abs_path = ft_strjoin(tmp, name);
		if (ft_file_exists(abs_path))
		{
			free(tmp);
			return (abs_path);
		}
		free(tmp);
		free(abs_path);
		*dir++;
	}
	return (NULL);
}

int	ft_bin(t_minishell *ms, t_node *node)
{
	int		ret;
	char	**env_keys;
	char	**args;

	char	*path;
	char	**bin;

	if (ft_file_exists(node->name))
		return (ft_execute_bin(ms, ft_strdup(node->name), node->arg));
	if (!(path = ft_check_abs_path(ms, node->name)))
		return (-1);
	return (ft_execute_bin(ms, path, node->arg));
}
