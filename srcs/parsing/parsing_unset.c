#include "minishell.h"

int get_arg_unset(char **line, char *arg)
{
	char ret;

	if ((ret = get_arg_key(line, &arg)) < 0)
		return (ret);
	if (!(ft_isseparator(**line) || ft_isspace(**line) || !**line))
		return (NOT_VAILD_ARG);
	while (ft_isspace(**line))
			(*line)++;
	*(arg++) = ' ';
	*arg = '\0';
	return (0);
}

int parsing_unset(t_lstcmd *cmd, char **line)
{
	int		arg_num;
	char	*arg;
	char	*tmp;
	char	*save;
	int		ret;

	while (ft_isspace(**line))
			(*line)++;
	arg_num = get_arg_num(*line);
	arg = ft_strdup("");
	while (arg_num--)
	{
		tmp = malloc(sizeof(char) * (get_arg_size(*line) + 2));
		if ((ret = get_arg_unset(line, tmp)) < 0)
		{
			free(tmp);
			return (ret);
		}
		save = arg;
		arg = ft_strjoin(arg, tmp);
		free(save);
		free(tmp);
	}
	push_back(cmd, TYPE_UNSET, arg);
	return (0);
}