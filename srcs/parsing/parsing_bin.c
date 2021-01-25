#include "minishell.h"

int	parsing_bin(t_lstcmd *cmd, char **line)
{
	int		i;
	int		ret;
	char	*str;
	char	*arg;

	i = 0;
	while ((*line)[i] && !ft_isspace((*line)[i]))
		i++;
	str = ft_substr(*line, 0, i);
	*line = *line + i;
	while (ft_isspace(**line))
		(*line)++;
	if ((ret = get_arg_echo(line, &arg)) < 0)
		return (ret);
	push_back_normal(cmd, TYPE_NORMAL, str, arg);
	return (0);
}
