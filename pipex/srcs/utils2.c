#include "../includes/pipex.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strcat(char *dst, const char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

int	isfound(const char *s1, const char *s2, size_t n, size_t n_max)
{
	size_t	i;

	i = 0;
	while (s2[i] != '\0')
	{
		if (s2[i] != s1[i] || n >= n_max)
			return (0);
		i++;
		n++;
	}
	return (1);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] == s2[0])
			if (isfound(&s1[i], s2, i, n))
				return ((char *)&s1[i]);
		i++;
	}
	return (0);
}
