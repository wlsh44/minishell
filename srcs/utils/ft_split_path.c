/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:50:23 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 17:15:53 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_count(char *path)
{
	int		i;
	int		cnt;
	int		pos;

	i = 0;
	cnt = 0;
	while (path && path[i])
	{
		if (path[i] == ':')
		{
			cnt++;
			if (path[i + 1] == '\0')
				cnt++;
			pos = i + 1;
		}
		i++;
	}
	if (i > 0 && cnt == 0)
		cnt = 1;
	else if (pos < i)
		cnt++;
	return (cnt);
}

static char	*set_path(char *path, int i, int *pos)
{
	int		p;
	char	*tmp;

	p = *pos;
	if (i == 0 || (path[i + 1] == '\0'))
		tmp = ft_strdup("./");
	else
		tmp = ft_substr(path, p, (i - p));
	p = i + 1;
	*pos = p;
	return (tmp);
}

static char	**default_path(void)
{
	char	**path;

	if (!(path = ft_calloc(sizeof(char *), 1)))
		return (NULL);
	return (path);
}

char	**ft_split_path(char *path)
{
	char	**tabs;
	int		i;
	int		cnt;
	int		pos;

	if (!path || ft_strlen(path) == 0)
		return (default_path());
	if (!(tabs = ft_calloc(sizeof(char *), (get_path_count(path) + 1))))
		return (NULL);
	i = 0;
	cnt = 0;
	pos = 0;
	while (path && path[i])
	{
		if (path[i] == ':')
			tabs[cnt++] = set_path(path, i, &pos);
		i++;
	}
	if (i > 0 && path[i] == '\0' && cnt == 0)
		tabs[cnt] = ft_substr(path, 0, i);
	else if (pos < i)
		tabs[cnt++] = ft_substr(path, pos, i - pos);
	return (tabs);
}
