/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_exists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:53:46 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 20:53:57 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_file_exists(const char *file)
{
	struct stat	buf;
	int			exists;

	exists = stat(file, &buf);
	if (exists < 0)
		return (0);
	return (1);
}
