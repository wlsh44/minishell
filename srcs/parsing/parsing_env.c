/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:10:51 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:11:05 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_env(t_lstcmd *cmd, char **line)
{
	if (get_arg_num(*line) > 0)
		return (TOO_MANY_ARG);
	while (ft_isspace(**line))
		(*line)++;
	push_back(cmd, TYPE_ENV, NULL);
	return (0);
}
