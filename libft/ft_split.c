#include "libft.h"

static char	**ft_malloc_free(char **dst)
{
	size_t	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

static int	ft_count(char const *s, char c)
{
	int		count;
	int		i;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static int	ft_words_len(char const *s, char c, int i)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	dst = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!dst || !s)
		return (NULL);
	while (j != ft_count(s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = malloc((ft_words_len(s, c, i) + 1) * sizeof(char));
		if (!dst[j])
			return (ft_malloc_free(dst));
		while (s[i] != c && s[i])
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}
