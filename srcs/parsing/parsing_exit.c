/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:11:11 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 23:11:18 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_exit(t_lstcmd *cmd, char **line)
{
	while (**line && !ft_isseparator(**line))
		(*line)++;
	push_back(cmd, TYPE_EXIT, NULL);
	return (0);
}
