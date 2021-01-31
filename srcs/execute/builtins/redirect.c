/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:48:12 by schang            #+#    #+#             */
/*   Updated: 2021/01/29 20:53:25 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		read_line(int fd, char **line)
{
	char	*buf;
	char	*tmp;

	buf = ft_strdup(" ");
	while (read(fd, buf, 1) > 0)
	{
		tmp = *line;
		*line = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (0);
}

void	get_oldpath(t_lstenv *env, t_node *cur)
{
	char	*tmp;
	char	*arg;

	tmp = dup_env_value(env, "OLDPWD", 6);
	arg = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = cur->arg;
	cur->arg = ft_strjoin(arg, cur->arg);
	free(arg);
	free(tmp);
}

int		ft_redirect_output(t_minishell *ms, t_node *cur)
{
	char	*line;
	int		fd;
	int		ret;
	int		option;

	ret = 0;
	if (cur->prev->type == TYPE_CD)
		get_oldpath(ms->env, cur);
	option = cur->type == TYPE_REDIRECT_OUTPUT ? O_TRUNC : O_APPEND;
	fd = open(cur->arg, O_CREAT | O_WRONLY | option, 0644);
	line = ft_strdup("");
	if (ms->oldfd[0] != -1)
		read_line(STDIN_FILENO, &line);
	if ((cur->next->type == TYPE_REDIRECT_OUTPUT ||
		cur->next->type == TYPE_DOUBLE_REDIRECT || cur->prev->type == HEAD))
		write(1, line, ft_strlen(line));
	else
		write(fd, line, ft_strlen(line));
	free(line);
	close(fd);
	return (ret);
}

int		ft_redirect_input(t_node *cur)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 0;
	line = ft_strdup("");
	fd = open(cur->arg, O_RDONLY);
	read_line(fd, &line);
	write(1, line, ft_strlen(line));
	free(line);
	close(fd);
	return (ret);
}
