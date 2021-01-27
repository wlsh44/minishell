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

int	parsing_cmd1(t_minishell *ms, char **line, char *arg)
{
	if (!ft_strncmp(arg, "cd", ft_strlen(arg)) && ft_endline_condition(**line))
		return (parsing_cd(ms->cmd, line));
	else if (!ft_strncmp(arg, "pwd", ft_strlen(arg))&& ft_endline_condition(**line))
		return (parsing_pwd(ms->cmd, line));
	else if (!ft_strncmp(arg, "echo", ft_strlen(arg)) && ft_endline_condition(**line))
		return (parsing_echo(ms->cmd, line));
	else if (!ft_strncmp(arg, "export", ft_strlen(arg)) && ft_endline_condition(**line))
		return (parsing_export(ms->cmd, line));
	else if (!ft_strncmp(arg, "env", ft_strlen(arg)) && ft_endline_condition(**line))
		return (parsing_env(ms->cmd, line));
	else if (!ft_strncmp(arg, "unset", ft_strlen(arg)) && ft_endline_condition(**line))
		return (parsing_unset(ms->cmd, line));
	else if (!ft_strncmp(arg, "exit", ft_strlen(arg)) && ft_endline_condition(**line))
		return (parsing_exit(ms->cmd, line));
	return (1);
}

int	parsing_cmd2(t_minishell *ms, char **line, char *arg)
{
	if (!ft_strncmp(arg, ">", ft_strlen(arg)) && !ft_isseparator(**line))
		return (parsing_redirect_output(ms->cmd, line));
	else if (!ft_strncmp(arg, "<", ft_strlen(arg)) && !ft_isseparator(**line))
		return (parsing_redirect_input(ms->cmd, line));
	else if (!ft_strncmp(arg, ">>", ft_strlen(arg)) && !ft_isseparator(**line))
		return (parsing_double_redirect(ms->cmd, line));
	else if (!ft_strncmp(arg, "|", ft_strlen(arg)) && !ft_isseparator(**line))
		return (parsing_pipe(ms->cmd));
	else if (!ft_strncmp(arg, ";", ft_strlen(arg)) && !ft_isseparator(**line))
		return (parsing_semicolon(ms, line));
	else 
		return (parsing_bin(ms->cmd, line, arg));
	return (0);
}

int	parsing_cmd(t_minishell *ms, char **line)
{
	char	*arg;
	int		size;
	int		ret;

	size = get_arg_size(*line);
	arg = malloc(sizeof(char) * (size + 1));
	ret = get_arg_char_basic(line, arg, ft_endline_condition);
	if (!(ret < 0))
		ret = parsing_cmd1(ms, line, arg);
	if (ret)
		ret = parsing_cmd2(ms, line, arg);
	free(arg);
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
		if ((ret = parsing_cmd(ms, line)) < 0)
			return (ret);
	}
	return (ret);
}
