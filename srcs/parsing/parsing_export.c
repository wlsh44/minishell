#include "minishell.h"

int get_arg_value(char **line, char **arg)
{
	int ret;

	ret = 0;
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line))
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line)
				*(*arg)++ = *(*line)++;
		}
		else if (ft_isquote(**line) && (ret = get_arg_quote(line, arg)) < 0)
			return (ret);
		else
			*(*arg)++ = *(*line)++;
	}
	**arg = '\0';
	return (0);
}

int get_arg_export(char **line, char *arg)
{
	int ret;

	ret = get_arg_key(line, &arg);
	if (!ret && **line == '=')
	{
		*(arg++) = *(*line)++;
		if ((ret = get_arg_value(line, &arg)) < 0)
			*(arg++) = ret;
	}
	else if (!ret && !(ft_isseparator(**line) || ft_isspace(**line) || !**line))
		ret = NOT_VAILD_IDENTIFIER;
	if (ret < 0)
	{
		*(arg++) = ret;
		while (!(ft_isseparator(**line) || ft_isspace(**line) || !**line))
			(*line)++;
	}
	while (ft_isspace(**line))
			(*line)++;
	*(arg++) = ' ';
	*arg = '\0';
	return (0);
}

int parsing_export(t_lstcmd *cmd, char **line)
{
	int		arg_num;
	char	*arg;
	char	*tmp;
	char	*save;

	while (ft_isspace(**line))
			(*line)++;
	arg_num = get_arg_num(*line);
	arg = ft_strdup("");
	while (arg_num--)
	{
		tmp = malloc(sizeof(char) * (get_arg_size(*line) + 2));
		get_arg_export(line, tmp);
		save = arg;
		arg = ft_strjoin(arg, tmp);
		free(save);
		free(tmp);
	}
	push_back(cmd, TYPE_EXPORT, arg);
	return (0);
}