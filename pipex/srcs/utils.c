#include "../includes/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_size;

	if (!s)
		return (0);
	s_size = ft_strlen(s);
	if (start >= s_size)
		len = 0;
	else if (len > s_size - start)
		len = s_size - start;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	get_size(char const *s, char c)
{
	size_t	size;
	int		flag;

	flag = 0;
	size = 0;
	while (*s != '\0')
	{
		if (*s != c && !flag)
		{
			size++;
			flag = 1;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (size + 1);
}

char	*get_str(char const *s, char c, size_t offset)
{
	size_t	init;

	init = offset;
	while (s[offset] != c && s[offset] != '\0')
		offset++;
	return (ft_substr(s, init, (offset - init)));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	arr = malloc(get_size(s, c) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			arr[j] = get_str(s, c, i);
			i += ft_strlen(arr[j]) - 1;
			j++;
		}
		i++;
	}
	arr[j] = 0;
	return (arr);
}
