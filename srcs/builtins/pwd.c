/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:06:03 by schang            #+#    #+#             */
/*   Updated: 2021/01/12 22:11:18 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_node *node)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, 1);
		return (1);
	}
	else
		return (0);
}
