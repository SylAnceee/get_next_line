/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:41:44 by abreuil           #+#    #+#             */
/*   Updated: 2024/11/08 17:46:23 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	extract_line(t_list *stash, char **line)
{
	int		i;
	int		j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		while (stash -> content[i])
		{
			if (stash -> content[i] == '\n')
			{
				line[0][j++] = stash -> content[i];
				break ;
			}
			line[0][j++] = stash -> content[i++];
		}
		stash = stash -> next;
	}
	line[0][j] = '\0';
}

void	generate_line(char **line, t_list *stash)
{
	int		i;
	int		len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash -> content[i])
		{
			if (stash -> content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash -> next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!stash || !clean_node)
		return ;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last -> content[i] && last -> content[i] != '\n')
		i++;
	if (last -> content[i] == '\n')
		i++;
	clean_node -> content = malloc(sizeof(char)
			+ (ft_strlen(last -> content) - i) + 1);
	if (!clean_node)
		return ;
	j = 0;
	while (last -> content[i])
		clean_node -> content[j++] = last -> content[i++];
	clean_node -> content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current -> content);
		next = current -> next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
