/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:41:38 by abreuil           #+#    #+#             */
/*   Updated: 2024/11/08 17:45:32 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_and_stash(int fd, t_list **stash, int *readed_ptr)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_new_line(*stash) && *readed_ptr != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		*readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && readed_ptr == 0) || *readed_ptr == -1)
		{
			free(buf);
			return ;
		}
		buf[*readed_ptr] = '\0';
		add_to_stash(stash, buf, readed);
		free(buf);
	}
}

int	found_new_line(t_list *stash)
{
	int		i;
	t_list	*current;

	if (!stash)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current -> content[i])
	{
		if (current -> content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current -> next)
		current = current -> next;
	return (current);
}

void	add_to_stash(t_list **stash, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node -> next = NULL;
	new_node -> content = malloc(sizeof(char) *(readed + 1));
	if (!new_node -> content)
		return ;
	while (buf[i] && i < readed)
	{
		new_node -> content[i] = buf[i];
		i++;
	}
	new_node -> content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last -> next = new_node;
}

char	*get_next_line(int fd)
{
	static t_list		*stash;
	char				*line;
	int					bytes_readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0))
		return (NULL);
	bytes_readed = 1;
	line = NULL;
	read_and_stash(fd, &stash, &bytes_readed);
	if (!stash)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int main()
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}
