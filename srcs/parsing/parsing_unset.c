/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:13:03 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:13:24 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_unset(t_lstcmd *cmd, char **line)
{
	int arg_num;
	int size;
	char *arg;
	char *tmp;
	char *tmp2;
	int ret;

	tmp = NULL;
	while (ft_isspace(**line))
		(*line)++;
	if ((arg_num = get_arg_num(*line)) == 0)
		return (NOT_ENOUGH_ARG);
	arg = malloc(sizeof(char));
	*arg = '\0';
	while (arg_num--)
	{
		size = get_arg_size(*line);
		tmp = malloc(sizeof(char) * (size + 1));
		if ((ret = get_arg_export_unset(line, tmp)) < 0) {
			free(arg);
			return (ret);
		}
		tmp2 = ft_strjoin(tmp, " ");
		arg = ft_strjoin(arg, tmp2);
		free(tmp);
		free(tmp2);
		while (ft_isspace(**line))
			(*line)++;
	}
	push_back(cmd, TYPE_UNSET, arg);
	return (0);
}
