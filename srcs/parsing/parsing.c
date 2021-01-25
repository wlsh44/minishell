#include "minishell.h"

int parsing_cmd1(t_minishell *ms, char **line, int type)
{
	if (type == TYPE_CD && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_cd(ms->cmd, line));
	else if (type == TYPE_PWD && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_pwd(ms->cmd, line));
	else if (type == TYPE_ECHO && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_echo(ms->cmd, line));
	else if (type == TYPE_EXPORT && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_export(ms->cmd, line));
	else if (type == TYPE_ENV && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_env(ms->cmd, line));
	else if (type == TYPE_UNSET && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_unset(ms->cmd, line));
	else if (type == TYPE_EXIT && (!**line || ft_isspace((**line)) || ft_isseparator((**line))))
		return (parsing_exit(ms->cmd, line));
	else if (!(type == TYPE_REDIRECT_INPUT || type == TYPE_REDIRECT_OUTPUT || type == TYPE_DOUBLE_REDIRECT || type == TYPE_PIPE || type == TYPE_SEMICOLON))
		return (parsing_bin(ms->cmd, line));
	return (0);
}

int parsing_cmd2(t_minishell *ms, char **line, int type)
{
	if (!**line && (type == TYPE_REDIRECT_OUTPUT || type == TYPE_REDIRECT_INPUT || type == TYPE_DOUBLE_REDIRECT || type == TYPE_PIPE || type == TYPE_SEMICOLON))
		return (SYNTAX_ERROR);
	if (type == TYPE_REDIRECT_OUTPUT && !ft_isseparator(**line))
		return (parsing_redirect_output(ms->cmd, line));
	else if (type == TYPE_REDIRECT_INPUT && !ft_isseparator(**line))
		return (parsing_redirect_input(ms->cmd, line));
	else if (type == TYPE_DOUBLE_REDIRECT && !ft_isseparator(**line))
		return (parsing_double_redirect(ms->cmd, line));
	else if (type == TYPE_PIPE && !ft_isseparator(**line))
		return (parsing_pipe(ms->cmd));
	else if (type == TYPE_SEMICOLON && !ft_isseparator(**line))
		(*line)++;
	return (0);
}

int parsing(t_minishell *ms) {
	int ret;
	int type;
	char **line;

	line = &ms->cmd_line;
	while (**line && !(ret = 0)) {
		while (ft_isspace(**line))
			(*line)++;
		if ((type = parsing_type(line)) < 0)
		{
			ret = type;
			break;
		}
		if ((ret = parsing_cmd1(ms, line, type)) < 0)
			break ;
		if ((ret = parsing_cmd2(ms, line, type)) < 0)
			break;
	}
	return (ret);
}

