/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:12:09 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:29:39 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_pwd(t_lstcmd *cmd, char **line)
{
	if (get_arg_num(*line) > 0)
		return (TOO_MANY_ARG);
	while (ft_isspace(**line))
		(*line)++;
	push_back(cmd, TYPE_PWD, NULL);
	return (0);
}
