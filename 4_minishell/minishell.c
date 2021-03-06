/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:57:33 by jhur              #+#    #+#             */
/*   Updated: 2020/07/23 13:57:35 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_ret = 0;
char	**g_env = 0;
int		g_dq_flag = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\nminish% ", 2);
		g_ret = 1;
	}
}

char	**ft_cpenv(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}

int		execute_cmds(char *cmds)
{
	char	**info;
	int		i;

	i = 0;
	if (ft_strchr(cmds, '|'))
		ft_pipe(cmds);
	else
	{
		info = get_info(cmds);
		if (*info != 0)
			ft_cmd(info);
		ft_free(info);
		info = 0;
	}
	return (0);
}

void	minishell(void)
{
	char	*line;
	char	**cmds;
	int		i;

	ft_putstr_fd("minish% ", 2);
	while (get_next_line(1, &line) > 0)
	{
		g_dq_flag = 0;
		if (*line != '\0')
		{
			if ((ft_quote_cnt(line, -1)) != 0)
				line = ft_quote(line);
			if ((cmds = get_cmds(line, ';')))
			{
				i = 0;
				while (cmds[i] && *cmds[i])
					execute_cmds(cmds[i++]);
				ft_free(cmds);
			}
		}
		free(line);
		ft_putstr_fd("minish% ", 2);
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_env = ft_cpenv(envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	minishell();
	return (0);
}
