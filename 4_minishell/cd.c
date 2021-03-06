/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:54:00 by jhur              #+#    #+#             */
/*   Updated: 2020/07/23 13:54:07 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_find_home(void)
{
	int		i;
	char	**path;

	i = 0;
	while (g_env[i])
	{
		if ((ft_strncmp(g_env[i], "HOME=", 5) == 0))
		{
			path = ft_split(g_env[i], '=');
		}
		i++;
	}
	return (path);
}

int			ft_cd(char **info)
{
	int		res;
	char	**home;

	home = ft_find_home();
	if (info[1])
		res = chdir(info[1]);
	else
		res = chdir(home[1]);
	if (res != 0)
	{
		res = 1;
		ft_puts("cd: no such file or directory\n");
	}
	ft_free(home);
	return (res);
}
