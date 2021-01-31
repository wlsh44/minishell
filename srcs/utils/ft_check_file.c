/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 00:24:51 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 20:14:19 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_file(const char *file)
{
	struct stat	st;
	int			ret;

	ret = stat(file, &st);
	if (ret == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (IS_A_DIRECTORY);
		else
			return (file_permission_check(st));
	}
	return (NO_DIRECTORY);
}

int		ft_check_file2(const char *file)
{
	struct stat	st;
	int			ret;

	ret = stat(file, &st);
	if (ret == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (IS_A_DIRECTORY);
		else
			return (fileread_permission_check(st));
	}
	return (NO_DIRECTORY);
}
