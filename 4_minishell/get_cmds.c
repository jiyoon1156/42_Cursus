/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:53:04 by hpark             #+#    #+#             */
/*   Updated: 2020/07/23 13:53:05 by hpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quote_check(int *quote, char c)
{
	if (*quote == 0 && c == '"')
	{
		*quote = c;
		g_dq_flag = 1;
	}
	else if (*quote == 0 && c == '\'')
	{
		*quote = c;
		g_dq_flag = 2;
	}
	else if (*quote != 0 && *quote == c)
		*quote = 0;
	else
		return (0);
	return (1);
}

int		count_char(char *line, int c)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}

char	**cmds_free(int i, char **cmds)
{
	while (i > 0)
	{
		i--;
		free(cmds[i]);
		cmds[i] = 0;
	}
	free(cmds);
	cmds = 0;
	ft_putstr_fd("parse error\n", 2);
	g_ret = 258;
	return (0);
}

char	**get_cmds(char *line, char sep)
{
	char	**cmds;
	char	*tmp;
	int		quote;
	int		i;

	cmds = malloc(sizeof(char *) * (count_char(line, sep) + 2));
	i = 0;
	quote = 0;
	tmp = line;
	while (*line)
	{
		quote_check(&quote, *line);
		if (*line == sep && quote == 0)
		{
			cmds[i++] = ft_substr(tmp, 0, (line++ - tmp));
			while (*line && *line == ' ')
				line++;
			if (*(tmp = line) && *tmp == sep)
				return (cmds_free(i, cmds));
		}
		line++;
	}
	cmds[i++] = ft_substr(tmp, 0, (line - tmp));
	cmds[i] = 0;
	return (cmds);
}
