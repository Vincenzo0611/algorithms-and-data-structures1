#include "atrybuty.h"

atrybuty* addNew(atrybuty* atr, str* nazwa, str* wartosc)
{
	if (nazwa == nullptr || wartosc == nullptr) {
		return atr;
	}

	if (atr == nullptr) {
		atr = new atrybuty;
		atr->ile_w_tabeli = 1;
		atr->data[0].nazwa = new str(*nazwa);
		atr->data[0].wartosc = new str(*wartosc);
		for (int i = 1; i < T; i++) {
			atr->data[i].nazwa = nullptr;
			atr->data[i].wartosc = nullptr;
		}
		atr->next = nullptr;
		atr->prev = nullptr;
		return atr;
	}

	atrybuty* tmp = atr;
	int x = T - 1;
	while (tmp != nullptr &&  tmp->ile_w_tabeli > 0 && tmp->ile_w_tabeli <= T) 
	{
		if (tmp->data[x].nazwa != nullptr && same(tmp->data[x].nazwa, nazwa)) {
			delete tmp->data[x].wartosc;
			tmp->data[x].wartosc = new str(*wartosc);
			return atr;
		}
		x--;
		if (x < 0) {
			tmp = tmp->prev;
			if (tmp != nullptr) {
				x = T - 1;
			}
		}
	}

	if (atr->data[T - 1].nazwa != nullptr) {
		atrybuty* tmp2 = new atrybuty;
		tmp2->ile_w_tabeli = 1;
		tmp2->data[0].nazwa = new str(*nazwa);
		tmp2->data[0].wartosc = new str(*wartosc);
		for (int i = 1; i < T; i++) {
			tmp2->data[i].nazwa = nullptr;
			tmp2->data[i].wartosc = nullptr;
		}
		tmp2->next = nullptr;
		tmp2->prev = atr;
		atr->next = tmp2;
		return tmp2;
	}
	else {
		int index = getLastIndex(atr);
		atr->data[index].nazwa = new str(*nazwa);
		atr->data[index].wartosc = new str(*wartosc);
		atr->ile_w_tabeli++;
		return atr;
	}
}

atrybuty* deleteOne(atrybuty* atr, int wartosc_w_tabeli)
{
	if (atr == nullptr)
		return nullptr;
	else
	{
		if (atr->data[wartosc_w_tabeli].wartosc == nullptr)
			return atr;
		else
		{
			del(atr->data[wartosc_w_tabeli].nazwa);
			atr->data[wartosc_w_tabeli].nazwa = nullptr;
			del(atr->data[wartosc_w_tabeli].wartosc);
			atr->data[wartosc_w_tabeli].wartosc = nullptr;
			atr->ile_w_tabeli--;
			if (atr->ile_w_tabeli == 0)
			{
				atrybuty* tmp = nullptr;
				if (atr->next != nullptr)
				{
					tmp = atr->next;
					deleteNode(atr);
				}
				else
				{
					tmp = atr->prev;
					deleteNode(atr);
				}
				return tmp;
			}

			return atr;
		}
	}
}

void deleteNode(atrybuty* atr)
{
	if (atr != nullptr)
	{
		if (atr->next != nullptr)
		{
			atr->next->prev = atr->prev;
		}
		if (atr->prev != nullptr)
		{
			atr->prev->next = atr->next;
		}
		delete atr;
	}
}

atrybuty* deleteAll(atrybuty* atr)
{
	if (atr != nullptr)
	{
		while (atr->next != nullptr)
		{
			atr = atr->next;
		}
		while (atr != nullptr)
		{
			for (int i = 0; i < T; i++)
			{
				if (atr != nullptr)
				{
					if (atr->data[i].nazwa != nullptr)
						atr = deleteOne(atr, i);
				}
			}
			if (atr != nullptr)
			{
				atrybuty* tmp = atr->prev;
				deleteNode(atr);
				atr = tmp;
			}
		}
	}
	return atr;
}

int getLastIndex(atrybuty* atr)
{
	int i = T - 1;
	while (atr->data[i].nazwa == nullptr)
	{
		i--;
		if (i < 0)
		{
			i = -1;
			break;
		}
	}
	i++;
	return i;
}