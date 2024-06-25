#include "selektory.h"

selektory* addNew(selektory* sele, str* nazwa)
{
	if (sele == nullptr && nazwa == nullptr)
	{
		sele = new selektory;
		sele->ile_w_tabeli = 0;
		sele->data[0].nazwa = nazwa;
		for (int i = 1; i < T; i++)
		{
			sele->data[i].nazwa = nullptr;
		}
		sele->next = nullptr;
		sele->prev = nullptr;
		return sele;
	}
	if (sele == nullptr)
	{
		sele = new selektory;
		sele->ile_w_tabeli = 1;
		sele->data[0].nazwa = nazwa;
		for (int i = 1; i < T; i++)
		{
			sele->data[i].nazwa = nullptr;
		}
		sele->next = nullptr;
		sele->prev = nullptr;
		return sele;
	}
	else
	{
		selektory* last = getLast(sele);
		if (last->ile_w_tabeli == T)
		{
			selektory* tmp = new selektory;
			tmp->ile_w_tabeli = 1;
			tmp->data[0].nazwa = nazwa;
			for (int i = 1; i < T; i++)
			{
				tmp->data[i].nazwa = nullptr;
			}
			tmp->next = nullptr;
			tmp->prev = last;
			last->next = tmp;
			return sele;
		}
		else
		{
			last->data[last->ile_w_tabeli].nazwa = nazwa;
			last->ile_w_tabeli++;
			return sele;
		}
	}
}

selektory* deleteOne(selektory* sele, int numer_w_tabeli)
{
	if (sele == nullptr)
		return nullptr;
	else
	{
		if (sele->data[numer_w_tabeli].nazwa == nullptr)
			return sele;
		else
		{
			del(sele->data[numer_w_tabeli].nazwa);
			sele->ile_w_tabeli--;
			if (sele->ile_w_tabeli == 0)
			{
				selektory* tmp = nullptr;
				if (sele->prev != nullptr)
				{
					 tmp = sele->prev;
					deleteNode(sele);
				}
				else
				{
					tmp = sele->next;
					deleteNode(sele);
				}
				return tmp;
			}
			
			return sele;
		}
	}
}

void deleteNode(selektory* sele)
{
	if (sele != nullptr)
	{
		if (sele->next != nullptr)
		{
			sele->next->prev = sele->prev;
		}
		if (sele->prev != nullptr)
		{
			sele->prev->next = sele->next;
		}
		delete sele;
	}
}

selektory* deleteAll(selektory* sele)
{
	while (sele->next != nullptr)
	{
		sele = sele->next;
	}
	while (sele != nullptr)
	{
		for (int i = 0; i < T; i++)
		{
			if (sele != nullptr)
			{
				if (sele->data[i].nazwa != nullptr)
					sele = deleteOne(sele, i);
			}
		}
		if (sele != nullptr)
		{
			selektory* tmp = sele->prev;
			deleteNode(sele);
			sele = tmp;
		}
	}
	return sele;
}

selektory* getLast(selektory* sele)
{
	if (sele != nullptr)
	{
		selektory* tmp = sele;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
	return sele;
}