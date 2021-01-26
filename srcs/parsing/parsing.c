/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:09 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 20:38:37 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_endline_condition(char c)
{
	if (c == 0 || ft_isspace(c) || ft_isseparator(c))
		return (1);
	return (0);
}

int	parsing_cmd1(t_minishell *ms, char **line, int type)
{
	if (type == TYPE_CD && ft_endline_condition(**line))
		return (parsing_cd(ms->cmd, line));
	else if (type == TYPE_PWD && ft_endline_condition(**line))
		return (parsing_pwd(ms->cmd, line));
	else if (type == TYPE_ECHO && ft_endline_condition(**line))
		return (parsing_echo(ms->cmd, line));
	else if (type == TYPE_EXPORT && ft_endline_condition(**line))
		return (parsing_export(ms->cmd, line));
	else if (type == TYPE_ENV && ft_endline_condition(**line))
		return (parsing_env(ms->cmd, line));
	else if (type == TYPE_UNSET && ft_endline_condition(**line))
		return (parsing_unset(ms->cmd, line));
	else if (type == TYPE_EXIT && ft_endline_condition(**line))
		return (parsing_exit(ms->cmd, line));
	else if (!(type == TYPE_REDIRECT_INPUT || type == TYPE_REDIRECT_OUTPUT
		|| type == TYPE_DOUBLE_REDIRECT || type == TYPE_PIPE
		|| type == TYPE_SEMICOLON))
		return (parsing_bin(ms->cmd, line));
	return (0);
}

int	parsing_cmd2(t_minishell *ms, char **line, int type)
{
	int ret;

	ret = 0;
	if (type == TYPE_REDIRECT_OUTPUT && !ft_isseparator(**line))
		ret = parsing_redirect_output(ms->cmd, line);
	else if (type == TYPE_REDIRECT_INPUT && !ft_isseparator(**line))
		ret = parsing_redirect_input(ms->cmd, line);
	else if (type == TYPE_DOUBLE_REDIRECT && !ft_isseparator(**line))
		ret = parsing_double_redirect(ms->cmd, line);
	else if (type == TYPE_PIPE && !ft_isseparator(**line))
		ret = parsing_pipe(ms->cmd);
	else if (type == TYPE_SEMICOLON && !ft_isseparator(**line))
		ret = parsing_semicolon(ms, line);
	return (ret);
}

int	parsing(t_minishell *ms)
{
	int		ret;
	int		type;
	char	**line;

	line = &ms->cmd_line;
	while (**line && !(ret = 0))
	{
		while (ft_isspace(**line))
			(*line)++;
		if ((type = parsing_type(line)) < 0)
		{
			ret = type;
			break ;
		}
		if ((ret = parsing_cmd1(ms, line, type)) < 0)
			break ;
		if ((ret = parsing_cmd2(ms, line, type)) < 0)
			break ;
	}
	return (ret);
}
