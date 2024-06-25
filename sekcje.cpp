#include <iostream>
#include "sekcje.h"

sekcje* addNew(sekcje* skj, str* nazwa)
{
	if (skj == nullptr)
	{
		skj = new sekcje;
		skj->ile_w_tabeli = 1;
		skj->data[0].sele = nullptr;
		skj->data[0].sele = addNew(skj->data[0].sele, nazwa);
		skj->data[0].atr = nullptr;
		for (int i = 1; i < T; i++)
		{
			skj->data[i].sele = nullptr;
			skj->data[i].atr = nullptr;
		}
		skj->next = nullptr;
		skj->prev = nullptr;
		return skj;
	}
	else
	{
		if (skj->ile_w_tabeli == T || !(skj->data[T-1].sele == nullptr && skj->data[T-1].atr == nullptr))
		{
			sekcje* tmp = new sekcje;
			tmp->ile_w_tabeli = 1;
			tmp->data[0].sele = nullptr;
			tmp->data[0].sele = addNew(tmp->data[0].sele, nazwa);
			tmp->data[0].atr = nullptr;
			for (int i = 1; i < T; i++)
			{
				tmp->data[i].sele = nullptr;
				tmp->data[i].atr = nullptr;
			}
			tmp->next = nullptr;
			tmp->prev = skj;
			skj->next = tmp;
			return tmp;
		}
		else
		{
			int i = T - 1;
			while (skj->data[i].sele == nullptr && skj->data[i].atr == nullptr)
			{
				i--;
			}

			i++;

			skj->data[i].sele = addNew(skj->data[i].sele, nazwa);
			skj->data[i].atr = nullptr;
			skj->ile_w_tabeli++;
			return skj;
		}
	}
}

sekcje* deleteOne(sekcje* skj, int numer_w_tabeli)
{
	if (skj == nullptr)
		return nullptr;
	else
	{
		if (skj->data[numer_w_tabeli].sele == nullptr)
			return skj;
		else
		{	
			skj->data[numer_w_tabeli].sele = deleteAll(skj->data[numer_w_tabeli].sele);
			if(skj->data[numer_w_tabeli].atr != nullptr)
				skj->data[numer_w_tabeli].atr = deleteAll(skj->data[numer_w_tabeli].atr);
			skj->ile_w_tabeli--;
			if (skj->ile_w_tabeli == 0)
			{
				sekcje* tmp = nullptr;
				if (skj->prev != nullptr)
				{
					tmp = skj->prev;
					deleteNode(skj);
					skj = nullptr;
				}
				else
				{
					tmp = skj->next;
					skj = deleteNode(skj);
				}
				return tmp;
			}

			return skj;
		}
	}
}

sekcje* deleteNode(sekcje* skj)
{
	if (skj != nullptr)
	{
		if (skj->next != nullptr)
		{
			skj->next->prev = skj->prev;
		}
		if (skj->prev != nullptr)
		{
			skj->prev->next = skj->next;
		}
		skj->ile_w_tabeli = 0;
		delete skj;
	}
	return nullptr;
}

sekcje* deleteAll(sekcje* skj)
{
	if (skj == nullptr)
		return nullptr;
	while (skj->next != nullptr)
	{
		skj = skj->next;
	}
	while (skj != nullptr)
	{
		for (int i = 0; i < T; i++)
		{
			if (skj != nullptr)
			{
				if (skj->data[i].sele != nullptr)
					skj = deleteOne(skj, i);
			}
		}
		if (skj != nullptr)
		{
			sekcje* tmp = skj->prev;
			deleteNode(skj);
			skj = tmp;
		}
	}
	return skj;
}

sekcje* getLast(sekcje* skj)
{
	if (skj != nullptr && skj->ile_w_tabeli > 0)
	{
		sekcje* tmp = skj;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
	return skj;
}

int ileSekcji(sekcje* skj)
{
	int i = 0; 

	while (skj != nullptr)
	{
		i += skj->ile_w_tabeli;
		skj = skj->next;
	}

	return i;

}

int getIndexSele(sekcje* skj)
{
	int i = T-1;
	while (skj->data[i].sele == nullptr)
	{
		i--;
		if (i < 0)
		{
			i = -1;
			break;
		}
	}
	return i;
}

int getIndexAtr(sekcje* skj)
{
	int i = T-1;
	while (skj->data[i].atr == nullptr && skj->data[i].sele == nullptr)
	{
		i--;
		if (i < 0)
		{
			i++;
			break;
		}
	}
		
	return i;
}