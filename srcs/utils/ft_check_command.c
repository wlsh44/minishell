/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 00:03:24 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 18:01:14 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_path(char *path, char *name)
{
	char	*tmp;
	char	*absolute_path;

	tmp = ft_strjoin(path, "/");
	absolute_path = ft_strjoin(tmp, name);
	free(tmp);
	return (absolute_path);
}

static char	**path_list(t_minishell *ms)
{
	char	*path;
	char	**list;

	path = get_env_value(ms->env, "PATH");
	if (!(list = ft_split_path(path)))
		return (NULL);
	return (list);
}

static int	default_command(t_minishell *ms, const char *cmd, char **path)
{
	struct stat	st;
	char		*tmp;

	tmp = ft_strjoin("./", cmd);
	if (stat(tmp, &st) == 0)
	{
		*path = tmp;
		return (command_permission_check(st));
	}
	return (NO_DIRECTORY);
}

static int	custom_command(t_minishell *ms, const char *cmd, char **path)
{
	struct stat	st;
	char		**dir;
	char		*tmp;
	int			i;
	int			cnt;

	dir = path_list(ms);
	i = 0;
	cnt = 0;
	while (dir && dir[i])
	{
		tmp = make_path(dir[i++], (char *)cmd);
		if (stat(tmp, &st) == 0)
		{
			if (S_ISDIR(st.st_mode) && (free_and_null(tmp)))
				continue;
			*path = tmp;
			return (command_permission_check(st));
		}
		free_and_null(tmp);
	}
	if (!dir)
		return (NO_DIRECTORY);
	return (WRONG_CMD);
}

int			ft_check_command(t_minishell *ms, const char *cmd, char **path)
{
	char	*env_path;

	env_path = get_env_value(ms->env, "PATH");
	if (!env_path || ft_strlen(env_path) == 0)
		return (default_command(ms, cmd, path));
	else
		return (custom_command(ms, cmd, path));
}
