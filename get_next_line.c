/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sendo <sendo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:55:29 by sendo             #+#    #+#             */
/*   Updated: 2023/07/20 17:28:11 by sendo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (NULL);
}

// char	*save_join(char *save, char *buf)
// {
// 	save = ft_strjoin(save, buf);
// 	return (save);
// }

char	*get_next_line(int fd)
{
	static char	*save;
	char		buf[BUFFER_SIZE + 1];
	int			read_num;
	char		*line;
	char		*tmp;

	while (1)
	{
		read_num = read(fd, buf, BUFFER_SIZE);
		if (read_num == -1)
			return (NULL);
		buf[read_num] = '\0';
		tmp = save;
		save = ft_strjoin(tmp, buf);
		if (save == NULL)
			return (NULL);
		free(tmp);
		if (ft_strchr(save, '\n'))
		{
			tmp = save;
			line = ft_substr(tmp, 0, ft_strchr(tmp, '\n') + 1 - tmp);
			save = ft_substr(ft_strchr(tmp, '\n') + 1, 0, ft_strchr(tmp, '\0')
					- ft_strchr(tmp, '\n') + 1);
			free(tmp);
			return (line);
		}
		else if (read_num == 0 && *save == '\0')
			break ;
		else if (read_num < BUFFER_SIZE)
		{
			tmp = save;
			line = ft_strdup(tmp);
			save = ft_substr(tmp, ft_strchr(tmp, '\0') - tmp, 0);
			free(tmp);
			return (line);
		}
	}
	return (NULL);
}

/*
読み取りたい文字列に改行がなく終端文字で終わるとき、
read_numが読み取りたいバッファ数を下回ったとき、saveの中身を返したい。
*/

// __attribute__((destructor)) void destructor(void)
// {
// 	int		status;
// 	char	buf[50];

// 	snprintf(buf, 50, "leaks %d &> leaksout", getpid());
// 	status = system(buf);
// 	if (status)
// 	{
// 		write(2, "leak!!!\n", 8);
// 		system("cat leaksout >/dev/stderr");
// 		exit(1);
// 	}
// }

// int	main(void)
// {
// 	int		fd1;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	fd1 = open("a.txt", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		printf("ファイルオープンエラー\n");
// 		return (1);
// 	}
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd1);
// 		printf("\n");
// 		printf("line:[%s]\n_________\n", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }

// char	*buf_to_save(char *save, char *buf)
// {
//     char	*new_save;

//     if (save == NULL)
//         save = ft_strdup("");
//     new_save = ft_strjoin(save, buf);
//     return (new_save);
// }

// char	*get_line(char *save)
// {
// 	char	*line;
// 	char	*tmp;

// 	line = ft_substr(save, 0, ft_strchr(save, '\n') - save);
// 	tmp = save;
// 	save = ft_substr(ft_strchr(tmp, '\n'), 1, ft_strchr(tmp, '\0')
// 			- ft_strchr(tmp, '\n'));
// 	printf("save:%s\n",save);
// 	free(tmp);
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*save;
// 	char		buf[BUFFER_SIZE + 1];
// 	char		*line;
// 	int			read_num;

// 	while (1)
// 	{
// 		read_num = read(fd, buf, BUFFER_SIZE);
// 		if (read_num == -1)
// 			return (NULL);
// 		buf[read_num] = '\0';
// 		printf("buf :%s\n", buf);
// 		printf("save:%s\n", save);
// 		save = buf_to_save(save, buf);
// 		printf("save:%s\n", save);
// 		if (ft_strchr(save, '\n'))
// 		{
// 			line = get_line(save);
// 			return (line);
// 		}
// 		else if (read_num < BUFFER_SIZE)
// 		{
// 			line = ft_strdup(save);
// 			return (line);
// 		}
// 	}
// 	return (NULL);
// }

// char	*get_next_line(int fd)
// {
// 	static char *save = NULL;
// 	char *tmp;
// 	int read_num;
// 	char buf[BUFFER_SIZE + 1];
// 	char *line;

// 	while (1)
// 	{
// 		read_num = read(fd, buf, BUFFER_SIZE);
// 		buf[read_num] = '\0';
// 			// printf("Asave:%s\nread_num:%d\n",save,read_num);
// 		if (read_num == -1 || (read_num == 0 && save == '\0'))
// 			break ;
// 		if (!ft_strchr(save, '\n'))
// 		{
// 			tmp = save;
// 			save = ft_strjoin(tmp, buf);
// 			free(tmp);
// 		}
// 		else
// 		else if(read_num == 0)
// 		{
// 			return (NULL);
// 		}
// 		{
// 			if(save)
// 			tmp = save;
// 			save = ft_strjoin(tmp, buf);
// 			free(tmp);
// 			line = ft_substr(save, 0, ft_strchr(save, '\n') + 1 - save);
// 			// printf("Aline:%s\n",line);
// 			tmp = save;
// 			// printf("Asave:%s\n",tmp);
// 			save = ft_substr(ft_strchr(tmp, '\n') + 1, 0, ft_strchr(tmp,
// 						'\0') - ft_strchr(tmp, '\n'));
// 			free(tmp);
// 			return (line);
// 		}
// 	}
// 	return (NULL);
// }