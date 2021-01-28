/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:31:09 by schang            #+#    #+#             */
/*   Updated: 2021/01/29 00:17:57 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_cmd2(t_minishell *ms, char **line, char *arg)
{
	if (!ft_strncmp(arg, "cd", 2) && ft_endline_condition(**line))
		return (parsing_cd(ms->cmd, line));
	else if (!ft_strncmp(arg, "pwd", 3)&& ft_endline_condition(**line))
		return (parsing_pwd(ms->cmd, line));
	else if (!ft_strncmp(arg, "echo", 4) && ft_endline_condition(**line))
		return (parsing_echo(ms->cmd, line));
	else if (!ft_strncmp(arg, "export", 6) && ft_endline_condition(**line))
		return (parsing_export(ms->cmd, line));
	else if (!ft_strncmp(arg, "env", 3) && ft_endline_condition(**line))
		return (parsing_env(ms->cmd, line));
	else if (!ft_strncmp(arg, "unset", 5) && ft_endline_condition(**line))
		return (parsing_unset(ms->cmd, line));
	else if (!ft_strncmp(arg, "exit", 4) && ft_endline_condition(**line))
		return (parsing_exit(ms->cmd, line));
	else
		return (parsing_bin(ms->cmd, line, arg));
	return (0);
}

int	parsing_cmd1(t_minishell *ms, char **line)
{
	if (!ft_strncmp(*line, ">", 1) && !ft_isseparator((*line)[1]))
		return (parsing_redirect_output(ms->cmd, line));
	else if (!ft_strncmp(*line, "<", 1) && !ft_isseparator((*line)[1]))
		return (parsing_redirect_input(ms->cmd, line));
	else if (!ft_strncmp(*line, ">>", 2) && !ft_isseparator((*line)[2]))
		return (parsing_double_redirect(ms->cmd, line));
	else if (!ft_strncmp(*line, "|", 1) && !ft_isseparator((*line)[1]))
		return (parsing_pipe(ms->cmd, line));
	else if (!ft_strncmp(*line, ";", 1) && !ft_isseparator((*line)[1]))
		return (parsing_semicolon(ms, line));
	return (0);
}

int	parsing_cmd(t_minishell *ms, char **line)
{
	char	*arg;
	int		size;
	int		ret;

	size = get_arg_size(*line);
	arg = malloc(sizeof(char) * (size + 1));
	if (ft_isseparator(**line))
		ret = parsing_cmd1(ms, line);
	else
	{
		ret = get_arg_char_basic(line, arg, ft_endline_condition);
		if (ret < 0)
		{
			free(arg);
			return (ret);
		}
		if ((ret = parsing_cmd2(ms, line, arg)) < 0)
			return (ret);
	}
	free(arg);
	return (ret);
}


int	parsing(t_minishell *ms)
{
	int		ret;
	int		type;
	char	*line;
	char	*test;
	char	*tmp;

	line = parsing_env_val(ms->env, ms->cmd_line);
	tmp = line;
	while (*line && !(ret = 0))
	{
		while (ft_isspace(*line))
			line++;
		if ((ret = parsing_cmd(ms, &line)) < 0)
			return (ret);
		while (ft_isspace(*line))
			line++;
	}
	free(tmp);
	return (ret);
}
