#include "komendy.h"

bool endOfcss(str* s)
{
	if (s != nullptr)
	{
		if (s->s == '?' && s->next != nullptr)
		{
			if (s->next->s == '?' && s->next->next != nullptr)
			{
				if (s->next->next->s == '?' && s->next->next->next != nullptr)
				{
					if (s->next->next->next->s == '?')
						return true;
				}
			}
		}
	}

	return false;
}

bool startOfcss(str* s)
{
	if (s != nullptr)
	{
		if (s->s == '*' && s->next != nullptr)
		{
			if (s->next->s == '*' && s->next->next != nullptr)
			{
				if (s->next->next->s == '*' && s->next->next->next != nullptr)
				{
					if (s->next->next->next->s == '*')
						return true;
				}
			}
		}
	}

	return false;
}

bool czyZnakzapytania(str* s)
{
	if (s != nullptr)
	{
		if (s->s == '?' && s->next == nullptr)
		{
			return true;
		}
	}

	return false;
}

bool liczba(str* s)
{
	if (s == nullptr)
		return false;
	while (s != nullptr)
	{
		if (s->s == ',')
		{
			return true;
		}
		else if (!(s->s >= '0' && s->s <= '9'))
		{
			return false;
		}
		s = s->next;
	}
	return true;
}

bool zaczynaodLiczby(str* s)
{
	if (s->s >= '0' && s->s <= '9')
		return true;
	return false;
}

bool validkomend(str* s)
{
	if (s == nullptr)
		return false;
	str* tmp = s;
	if (czyZnakzapytania(tmp) && tmp->next == nullptr)
		return true;
	if (startOfcss(tmp))
		return true;
	if (liczba(tmp))
	{
		tmp = usunDoprzecinkatmp(tmp);
		if (czyS(tmp))
		{
			tmp = usunDoprzecinkatmp(tmp);
			if (liczba(tmp))
				return true;
			else if (czyZnakzapytania(tmp))
				return true;
		}
		else if (czyA(tmp))
		{
			tmp = usunDoprzecinkatmp(tmp);
			if (czyZnakzapytania(tmp))
				return true;
			else if (!zaczynaodLiczby(tmp))
				return true;
		}
		else if (czyD(tmp))
		{
			tmp = usunDoprzecinkatmp(tmp);
			if (czyGwiazda(tmp))
				return true;
			else if (!zaczynaodLiczby(tmp))
				return true;
		}
	}
	tmp = s;
	if (!zaczynaodLiczby(tmp))
	{
		tmp = usunDoprzecinkatmp(tmp);
		if (czyA(tmp))
		{
			tmp = usunDoprzecinkatmp(tmp);
			if (czyZnakzapytania(tmp))
				return true;
		}
		else if (czyS(tmp))
		{
			tmp = usunDoprzecinkatmp(tmp);
			if (czyZnakzapytania(tmp))
				return true;
		}
		else if (czyE(tmp))
		{
			tmp = usunDoprzecinkatmp(tmp);
			if (!zaczynaodLiczby(tmp))
				return true;
		}
	}
	
	return false;

}

int get_Liczba(str* s)
{
	int i = 0;
	while (s != nullptr)
	{
		if (s->s == ',')
		{
			return i;
		}
		
		i = i * 10 + s->s - 48;
		s = s->next;
	}
	return i;
}

str* get_Slowo(str* s)
{
	str* tmp = nullptr;

	while(s->s != ',')
	{
		tmp = add(tmp, s->s);
		s = s->next;
		if (s == nullptr)
		{
			del(tmp);
			return nullptr;
		}
	}

	return tmp;

}

str* usunDoprzecinka(str* s)
{
	str* tmp = s;

	while (tmp->s != ',')
	{
		s = tmp;
		tmp = tmp->next;
		delete s;
	}
	s = tmp;
	tmp = tmp->next;
	delete s;

	return tmp;
}

str* usunDoprzecinkatmp(str* s)
{
	str* tmp = s;
	if (tmp == nullptr)
		return nullptr;
	while (tmp->s != ',')
	{
		tmp = tmp->next;
		if (tmp == nullptr)
			return nullptr;
	}
	tmp = tmp->next;

	return tmp;
}
str* usunLiterki(str* s)
{
	str* tmp = s;

	while ((tmp->s >= 'A' && tmp->s <= 'Z') || (tmp->s >= 'a' && tmp->s <= 'z'))
	{
		s = tmp;
		tmp = tmp->next;
		delete s;
	}

	return tmp;
}
str* usunLiczby(str* s)
{
	str* tmp = s;

	while (tmp->s >= '0' && tmp->s <= '9')
	{
		s = tmp;
		tmp = tmp->next;
		delete s;
	}
	return tmp;
}

bool czyS(str* s)
{
	if (s->s == 'S')
		return true;
	return false;
}
bool czyA(str* s)
{
	if (s->s == 'A')
		return true;
	return false;
}
bool czyE(str* s)
{
	if (s->s == 'E')
		return true;
	return false;
}
bool czyD(str* s)
{
	if (s->s == 'D')
		return true;
	return false;
}
bool czyGwiazda(str* s)
{
	if (s->s == '*')
		return true;
	return false;
}


bool jestSekcjanumer(sekcje* skj, int numer)
{
	if (skj == nullptr)
		return false;
	while (numer > skj->ile_w_tabeli)
	{
		numer = numer - skj->ile_w_tabeli;
		skj = skj->next;
		if (skj == nullptr)
			return false;
	}
	return true;
}
bool jestSelenumer(selektory* sele, int numer)
{
	while (numer > sele->ile_w_tabeli)
	{
		numer = numer - sele->ile_w_tabeli;
		sele = sele->next;
		if (sele == nullptr)
			return false;
	}
	return true;
}

bool jestAtronazwie(atrybuty* atr, str* nazwa)
{
	int i = 0;
	while (atr != nullptr)
	{
		if (atr->data[i].nazwa != nullptr)
		{
			if (same(atr->data[i].nazwa, nazwa))
				return true;
		}
		i++;
		if (i == T)
		{
			atr = atr->prev;
			i = 0;
		}
	}
	return false;
}

selektory* getSelektoryZSekcjinumer(sekcje* skj, int numer)
{
	while (numer > skj->ile_w_tabeli)
	{
		numer = numer - skj->ile_w_tabeli;
		skj = skj->next;
	}
	int i = -1;

	while (numer > 0)
	{
		i++;
		if (i == T)
		{
			skj = skj->next;
			i = 0;
		}
		if (skj->data[i].sele != nullptr)
		{
			numer--;
		}
	}

	return skj->data[i].sele;
}

atrybuty* getAtrybutyZSekcjinumer(sekcje* skj, int numer)
{
	while (numer > skj->ile_w_tabeli)
	{
		numer = numer - skj->ile_w_tabeli;
		skj = skj->next;
	}
	int i = -1;

	while (numer > 0)
	{
		i++;
		if (i == T)
		{
			skj = skj->next;
			i = 0;
		}
		if (skj->data[i].atr != nullptr)
		{
			numer--;
		}
	}

	return skj->data[i].atr;
}

int ileSeleDlaiSekcji(sekcje* skj, int numer)
{
	selektory* tmp = getSelektoryZSekcjinumer(skj, numer);

	int result = 0;

	while (tmp != nullptr)
	{
		result += tmp->ile_w_tabeli;
		tmp = tmp->next;
	}

	return result;
}

int ileAtrDlaiSekcji(sekcje* skj, int numer)
{
	atrybuty* tmp = getAtrybutyZSekcjinumer(skj, numer);

	int result = 0;

	while (tmp != nullptr)
	{
		result += tmp->ile_w_tabeli;
		tmp = tmp->prev;
	}

	return result;
}

str* Selenumer(selektory* sele, int numer)
{
	while (numer > sele->ile_w_tabeli)
	{
		numer = numer - sele->ile_w_tabeli;
		sele = sele->next;
	}
	int i = -1;

	while (numer > 0)
	{
		i++;
		if (i == T)
		{
			sele = sele->next;
			i = 0;
		}
		if (sele->data[i].nazwa != nullptr)
		{
			numer--;
		}
	}

	return sele->data[i].nazwa;

}

str* WartoscAtroNazwie(atrybuty* atr, str* nazwa)
{
	int i = 0;
	while (atr != nullptr)
	{
		if (atr->data[i].nazwa != nullptr)
		{
			if (same(atr->data[i].nazwa, nazwa))
				return atr->data[i].wartosc;
		}
		i++;
		if (i == T)
		{
			atr = atr->prev;
			i = 0;
		}
	}
	return nullptr;
}

int ileAtrAll(sekcje* skj, str* nazwa)
{
	int result = 0;
	while (skj != nullptr)
	{
		int i = 0, j = 0;
		while (j < skj->ile_w_tabeli)
		{
			if (skj->data[i].atr != nullptr)
			{
				j++;
				atrybuty* tmp = skj->data[i].atr;
				while (tmp != nullptr)
				{
					int ai = 0, aj = 0;
					while (aj < tmp->ile_w_tabeli)
					{
						if (tmp->data[ai].nazwa != nullptr)
						{
							aj++;
							if (same(tmp->data[ai].nazwa, nazwa))
							{
								result++;
								tmp = nullptr;
								break;
							}
						}
						ai++;
					}
					if (tmp != nullptr)
					{
						tmp = tmp->prev;
					}
				}

			}
			i++;
		}
		skj = skj->next;
	}


	return result;
}

int ileSeleAll(sekcje* skj, str* nazwa)
{
	int result = 0;
	while (skj != nullptr)
	{
		int i = 0, j = 0;
		while (j != skj->ile_w_tabeli)
		{
			if (skj->data[i].sele != nullptr)
			{
				j++;
				selektory* tmp = skj->data[i].sele;
				while (tmp != nullptr)
				{
					int ai = 0, aj = 0;
					while (aj != tmp->ile_w_tabeli)
					{
						if (tmp->data[ai].nazwa != nullptr)
						{
							aj++;
							if (same(tmp->data[ai].nazwa, nazwa))
							{
								result++;
								tmp = nullptr;
								break;
							}
						}
						ai++;
					}
					if (tmp != nullptr)
					{
						tmp = tmp->next;
					}
				}

			}
			i++;
		}
		skj = skj->next;
	}

	return result;
}

str* WartoscAtrodSele(sekcje* skj, str* nazwa_sele, str* nazwa_atr)
{
	if (skj == nullptr)
	{
		return nullptr;
	}

	skj = getLast(skj);
	while (skj != nullptr)
	{
		int i = T - 1, j = skj->ile_w_tabeli;
		while (j != 0)
		{
			if (skj->data[i].sele != nullptr)
			{
				j--;
				selektory* tmp = skj->data[i].sele;
				atrybuty* tmp_atr = skj->data[i].atr;
				
				while (tmp != nullptr)
				{
					int ai = 0, aj = 0;
					while (aj != tmp->ile_w_tabeli)
					{
						if (tmp->data[ai].nazwa != nullptr)
						{
							aj++;
							if (same(tmp->data[ai].nazwa, nazwa_sele))
							{
								while (tmp_atr != nullptr)
								{
									int a2i = 0, a2j = 0;
									while (a2j != tmp_atr->ile_w_tabeli)
									{
										if (tmp_atr->data[a2i].nazwa != nullptr)
										{
											a2j++;
											if (same(tmp_atr->data[a2i].nazwa, nazwa_atr))
											{
												return tmp_atr->data[a2i].wartosc;
											}
										}
										a2i++;
									}
									if (tmp_atr != nullptr)
									{
										tmp_atr = tmp_atr->prev;
									}
								}
								tmp = nullptr;
								break;
							}
						}
						ai++;
					}
					if (tmp != nullptr)
					{
						tmp = tmp->next;
					}
				}

			}
			i--;
		}
		skj = skj->prev;
	}
	return nullptr;
}

sekcje* usunSekcje(sekcje* skj, int numer, bool* d)
{

	if (skj == nullptr)
		return nullptr;
	sekcje* tmp = skj;

	while (numer > tmp->ile_w_tabeli)
	{
		numer = numer - tmp->ile_w_tabeli;
		tmp = tmp->next;
		if (tmp == nullptr)
			return skj;
	}
	int i = -1;

	while (numer > 0 && tmp != nullptr)
	{
		i++;
		if (i == T)
		{
			tmp = tmp->next;
			i = 0;
		}
		if (tmp->data[i].sele != nullptr)
		{
			numer--;
		}
	}
	if (tmp != nullptr)
	{
		tmp = deleteOne(tmp, i);
		*d = true;
	}
	if(skj->ile_w_tabeli > 0)
		return skj;
	return tmp;
}

sekcje* usunAtrybut(sekcje* skj, int numer, str* nazwa_atr, bool* d)
{
	sekcje* tmp = skj;

	if (tmp == nullptr)
	{
		return skj;
	}

	while (numer > tmp->ile_w_tabeli)
	{
		numer = numer - tmp->ile_w_tabeli;
		tmp = tmp->next;
		if (tmp == nullptr)
			return skj;
	}
	int i = -1;

	while (numer > 0)
	{
		i++;
		if (i == T)
		{
			tmp = tmp->next;
			i = 0;
			if (tmp == nullptr)
				return skj;
		}
		if (tmp->data[i].atr != nullptr)
		{
			numer--;
		}
	}
	atrybuty* atr = nullptr;
	if (i < 0)
	{
		return skj;
	}
	else
	{
		atr = tmp->data[i].atr;
	}
	int ai = 0;
	while (atr != nullptr)
	{
		if (atr->data[ai].nazwa != nullptr)
		{
			if (same(atr->data[ai].nazwa, nazwa_atr))
			{
				atr = deleteOne(atr, ai);
				if (atr == nullptr)
				{
					tmp->data[i].atr = nullptr;
					tmp = deleteOne(tmp, i);
					*d = true;
					while (tmp->prev != nullptr)
					{
						tmp = tmp->prev;
					}
					return tmp;
				}
				*d = true;
				tmp->data[i].atr = atr;
				break;
			}
		}
		ai++;
		if (ai == T)
		{
			atr = atr->prev;
			ai = 0;
		}
	}

	if (skj->ile_w_tabeli == 0)
		return nullptr;

	return skj;
}