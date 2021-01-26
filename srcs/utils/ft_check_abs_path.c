/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_abs_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:37:50 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 21:41:56 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_abs_path(t_minishell *ms, char *name)
{
	char	*path;
	char	**dir;
	char	*tmp;
	char	*abs_path;
	int		i;

	if (!(path = get_env_value(ms->env, "PATH"))
		|| !(dir = ft_split(path, ':')))
		return (0);
	i = 0;
	while (dir[i])
	{
		tmp = ft_strjoin(dir[i], "/");
		abs_path = ft_strjoin(tmp, name);
		free(tmp);
		if (ft_file_exists(abs_path))
		{
			free_double_char(dir);
			return (abs_path);
		}
		free(abs_path);
		i++;
	}
	free_double_char(dir);
	return (NULL);
}
