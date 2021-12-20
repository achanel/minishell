#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*elem;

	if (!lst || !f)
		return (NULL);
	dst = NULL;
	while (lst)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&elem, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&dst, elem);
	}
	return (dst);
}
