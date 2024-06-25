#include <iostream>
#include "str.h"
#include "selektory.h"
#include "atrybuty.h"
#include "sekcje.h"
#include "komendy.h"

using namespace std;

int main()
{
	char s;
	int q = 0;

	str* slowo = nullptr;
	str* slowotail = nullptr;
	str* komenda = nullptr;
	str* atrybut = nullptr;

	sekcje* lista_sekcji = nullptr;
	sekcje* lista_sekcji_tail = nullptr;

	bool sekjca_rozpoczeta = false;
	bool selektory_b = true;
	bool css_b = true;

	while (q == 0)
	{
		q = 1;
		slowo = nullptr;
		slowotail = nullptr;
		lista_sekcji_tail = getLast(lista_sekcji);
		while (css_b == true && cin >> noskipws >> s)
		{
			q = 0;
			if (s == ',')
			{
				if (selektory_b == true)
				{
					if (sekjca_rozpoczeta)
					{
						int index = getIndexSele(lista_sekcji_tail);
						if(slowotail != nullptr && slowotail->s <= SPACJA)
							usunWS(slowotail);
						lista_sekcji_tail->data[index].sele = addNew(lista_sekcji_tail->data[index].sele, slowo);
						slowo = nullptr;
						slowotail = nullptr;
					}
					else
					{
						if (slowotail != nullptr && slowotail->s <= SPACJA)
							usunWS(slowotail);
						if (lista_sekcji == nullptr)
						{
							lista_sekcji = addNew(lista_sekcji, slowo);
							lista_sekcji_tail = lista_sekcji;
						}
						else
						{
							lista_sekcji_tail = addNew(lista_sekcji_tail, slowo);
						}
						slowo = nullptr;
						slowotail = nullptr;
						sekjca_rozpoczeta = true;
					}
				}
				else
				{
					if (slowo == nullptr && s>SPACJA && s<='z')
					{
						slowo = add(slowo, s);
						slowotail = slowo;
					}
					else if(s >= SPACJA && slowotail != nullptr)
					{
						slowotail = addLast(slowotail, s);
					}
				}

			}
			else if (s == '{')
			{
				if (selektory_b == true)
				{
					if (sekjca_rozpoczeta)
					{
						int index = getIndexSele(lista_sekcji_tail);
						if (slowotail != nullptr && slowotail->s <= SPACJA)
							usunWS(slowotail);
						lista_sekcji_tail->data[index].sele = addNew(lista_sekcji_tail->data[index].sele, slowo);
						slowo = nullptr;
						slowotail = nullptr;
					}
					else
					{
						if (slowotail != nullptr && slowotail->s <= SPACJA)
							usunWS(slowotail);
						if (lista_sekcji == nullptr)
						{
							lista_sekcji = addNew(lista_sekcji, slowo);
							lista_sekcji_tail = lista_sekcji;
						}
						else
						{
							lista_sekcji_tail = addNew(lista_sekcji_tail, slowo);
						}
						slowo = nullptr;
						slowotail = nullptr;
						sekjca_rozpoczeta = true;
					}
				}
				selektory_b = false;
			}
			else if (s == ':' && selektory_b == false)
			{
				atrybut = slowo;
				slowo = nullptr;
				slowotail = nullptr;
				cin >>skipws >> s;
				slowo = add(slowo, s);
				slowotail = slowo;
				while (cin >> noskipws >> s)
				{
					if (s == ';')
					{
						int index = getIndexAtr(lista_sekcji_tail);
						if (slowotail != nullptr && slowotail->s <= SPACJA)
							usunWS(slowotail);
						lista_sekcji_tail->data[index].atr = addNew(lista_sekcji_tail->data[index].atr, atrybut, slowo);
						atrybut = nullptr;
						slowo = nullptr;
						slowotail = nullptr;
						break;
					}
					else if (s == '}')
					{
						int index = getIndexAtr(lista_sekcji_tail);
						if (slowotail != nullptr && slowotail->s <= SPACJA)
							usunWS(slowotail);
						lista_sekcji_tail->data[index].atr = addNew(lista_sekcji_tail->data[index].atr, atrybut, slowo);
						atrybut = nullptr;
						slowo = nullptr;
						slowotail = nullptr;
						selektory_b = true;
						sekjca_rozpoczeta = false;
						break;
					}
					else if(slowotail != nullptr)
					{
						if(s >= SPACJA && s <='z')
							slowotail = addLast(slowotail, s);
					}
				}
			}
			else if (s == '}')
			{
				if (atrybut != nullptr)
				{
					int index = getIndexAtr(lista_sekcji_tail);
					if (slowotail != nullptr && slowotail->s <= SPACJA)
						usunWS(slowotail);
					lista_sekcji_tail->data[index].atr = addNew(lista_sekcji_tail->data[index].atr, atrybut, slowo);
					atrybut = nullptr;
					slowo = nullptr;
				}
				selektory_b = true;
				sekjca_rozpoczeta = false;
			}
			else
			{
				if (slowo == nullptr && s > SPACJA && s <= 'z')
				{
					slowo = add(slowo, s);
					slowotail = slowo;
				}
				else if(s >= SPACJA && slowotail != nullptr)
				{
					slowotail = addLast(slowotail, s);
				}
				
			}
			if (endOfcss(slowo))
			{
				css_b = false;
				del(slowo);
				slowo = nullptr;
				break;
			}
		}

		cin >> noskipws >> s;
		while (css_b == false && cin >> noskipws >> s)
		{
				while(s == ENTER && slowo != nullptr)
				{
					if(validkomend(slowo))
					{
						if (startOfcss(slowo))
						{
							css_b = true;
							del(slowo);
							slowo = nullptr;
							break;
						}
						else
						{
							del(komenda);
							komenda = nullptr;
							komenda = copy(slowo);
							if (czyZnakzapytania(slowo))
							{
								print(komenda);
								cout << " == ";
								cout << ileSekcji(lista_sekcji) << endl;
								del(slowo);
								slowo = nullptr;
							}
							else if (liczba(slowo))
							{
								int liczba_i = get_Liczba(slowo);
								slowo = usunDoprzecinka(slowo);
								if (czyS(slowo))
								{
									slowo = usunDoprzecinka(slowo);
									if (czyZnakzapytania(slowo))
									{
										if (jestSekcjanumer(lista_sekcji, liczba_i))
										{
											print(komenda);
											cout << " == ";
											cout << ileSeleDlaiSekcji(lista_sekcji, liczba_i) << endl;
										}
										del(slowo);
										slowo = nullptr;
									}
									else
									{
										int liczba_j = get_Liczba(slowo);
										if (jestSekcjanumer(lista_sekcji, liczba_i))
										{
											selektory* tmp = getSelektoryZSekcjinumer(lista_sekcji, liczba_i);
											if (jestSelenumer(tmp, liczba_j))
											{
												print(komenda);
												cout << " == ";
												print(Selenumer(tmp, liczba_j));
												cout << endl;
												del(slowo);
												slowo = nullptr;
											}
											else
											{
												del(slowo);
												slowo = nullptr;
											}

										}
										else
										{
											del(slowo);
											slowo = nullptr;
										}
									}
								}
								else if (czyA(slowo))
								{
									slowo = usunDoprzecinka(slowo);
									if (czyZnakzapytania(slowo))
									{
										if (jestSekcjanumer(lista_sekcji, liczba_i))
										{
											print(komenda);
											cout << " == ";
											cout << ileAtrDlaiSekcji(lista_sekcji, liczba_i) << endl;
										}
										del(slowo);
										slowo = nullptr;
									}
									else
									{
										if (jestSekcjanumer(lista_sekcji, liczba_i))
										{
											atrybuty* tmp = getAtrybutyZSekcjinumer(lista_sekcji, liczba_i);
											if (jestAtronazwie(tmp, slowo))
											{
												print(komenda);
												cout << " == ";
												print(WartoscAtroNazwie(tmp, slowo));
												cout << endl;
												del(slowo);
												slowo = nullptr;
											}
											else
											{
												del(slowo);
												slowo = nullptr;
											}

										}
										else
										{
											del(slowo);
											slowo = nullptr;
										}
									}
								}
								else if (czyD(slowo))
								{
									slowo = usunDoprzecinka(slowo);
									bool czy_d = false;
									if (czyGwiazda(slowo))
									{
										lista_sekcji = usunSekcje(lista_sekcji, liczba_i, &czy_d);
										if (czy_d)
										{
											print(komenda);
											cout << " == ";
											cout << "deleted\n";
										}
										del(slowo);
										slowo = nullptr;
									}
									else
									{
										lista_sekcji = usunAtrybut(lista_sekcji, liczba_i, slowo, &czy_d);
										if (czy_d)
										{
											print(komenda);
											cout << " == ";
											cout << "deleted\n";
										}
										del(slowo);
										slowo = nullptr;
									}
								}
							}
							else
							{
								str* nazwa = nullptr;
								nazwa = get_Slowo(slowo);
								if (nazwa != nullptr)
								{
									slowo = usunDoprzecinka(slowo);
									if (czyA(slowo))
									{
										slowo = usunDoprzecinka(slowo);
										if (czyZnakzapytania(slowo))
										{
											print(komenda);
											cout << " == ";
											cout << ileAtrAll(lista_sekcji, nazwa);
											cout << endl;
											del(slowo);
											slowo = nullptr;
										}
										else
										{
											del(slowo);
											slowo = nullptr;
										}
									}
									else if (czyS(slowo))
									{
										print(komenda);
										cout << " == ";
										cout << ileSeleAll(lista_sekcji, nazwa);
										cout << endl;
										del(slowo);
										slowo = nullptr;
									}
									else if (czyE(slowo))
									{
										slowo = usunDoprzecinka(slowo);
										str* tmp = WartoscAtrodSele(lista_sekcji, nazwa, slowo);
										if (tmp != nullptr)
										{
											print(komenda);
											cout << " == ";
											print(tmp);
											cout << endl;
										}
										del(slowo);
										slowo = nullptr;
									}
									else
									{
										del(slowo);
										slowo = nullptr;
									}
								}
								else
								{
									del(slowo);
									slowo = nullptr;
								}
							}

						}
						del(slowo);
						slowo = nullptr;
					}
					else
					{
						if (!liczba(slowo))
						{
							if (zaczynaodLiczby(slowo))
							{
								slowo = usunLiczby(slowo);
							}
							else
							{
								slowo = usunLiterki(slowo);
								if (slowo->s == ',')
								{
									del(slowo);
									slowo = nullptr;
								}
							}
						}
						else
						{
							del(slowo);
							slowo = nullptr;

						}
					}
				}
				if (s != ENTER)
				{
					if (slowo == nullptr)
					{
						if (s != '\0' && s != ' ' && s != '\n' && s != '\t' && s != '\r' && s != '\v' && s != '\f')
						{
							if (slowo == nullptr)
							{
								slowo = add(slowo, s);
								slowotail = slowo;
							}
							else
							{
								slowotail = addLast(slowotail, s);
							}
						}
					}
					else
					{
						if (slowo == nullptr)
						{
							slowo = add(slowo, s);
							slowotail = slowo;
						}
						else
						{
							slowotail = addLast(slowotail, s);
						}
					}
				}
		}
		if (cin.eof() && slowo != nullptr)
		{
			if (validkomend(slowo))
			{
				if (startOfcss(slowo))
				{
					css_b = true;
					del(slowo);
					slowo = nullptr;
					break;
				}
				else
				{
					del(komenda);
					komenda = nullptr;
					komenda = copy(slowo);
					if (czyZnakzapytania(slowo))
					{
						print(komenda);
						cout << " == ";
						cout << ileSekcji(lista_sekcji) << endl;
						del(slowo);
						slowo = nullptr;
					}
					else if (liczba(slowo))
					{
						int liczba_i = get_Liczba(slowo);
						slowo = usunDoprzecinka(slowo);
						if (czyS(slowo))
						{
							slowo = usunDoprzecinka(slowo);
							if (czyZnakzapytania(slowo))
							{
								if (jestSekcjanumer(lista_sekcji, liczba_i))
								{
									print(komenda);
									cout << " == ";
									cout << ileSeleDlaiSekcji(lista_sekcji, liczba_i) << endl;
								}
								del(slowo);
								slowo = nullptr;
							}
							else
							{
								int liczba_j = get_Liczba(slowo);
								if (jestSekcjanumer(lista_sekcji, liczba_i))
								{
									selektory* tmp = getSelektoryZSekcjinumer(lista_sekcji, liczba_i);
									if (jestSelenumer(tmp, liczba_j))
									{
										print(komenda);
										cout << " == ";
										print(Selenumer(tmp, liczba_j));
										cout << endl;
										del(slowo);
										slowo = nullptr;
									}
									else
									{
										del(slowo);
										slowo = nullptr;
									}

								}
								else
								{
									del(slowo);
									slowo = nullptr;
								}
							}
						}
						else if (czyA(slowo))
						{
							slowo = usunDoprzecinka(slowo);
							if (czyZnakzapytania(slowo))
							{
								if (jestSekcjanumer(lista_sekcji, liczba_i))
								{
									print(komenda);
									cout << " == ";
									cout << ileAtrDlaiSekcji(lista_sekcji, liczba_i) << endl;
								}
								del(slowo);
								slowo = nullptr;
							}
							else
							{
								if (jestSekcjanumer(lista_sekcji, liczba_i))
								{
									atrybuty* tmp = getAtrybutyZSekcjinumer(lista_sekcji, liczba_i);
									if (jestAtronazwie(tmp, slowo))
									{
										print(komenda);
										cout << " == ";
										print(WartoscAtroNazwie(tmp, slowo));
										cout << endl;
										del(slowo);
										slowo = nullptr;
									}
									else
									{
										del(slowo);
										slowo = nullptr;
									}

								}
								else
								{
									del(slowo);
									slowo = nullptr;
								}
							}
						}
						else if (czyD(slowo))
						{
							slowo = usunDoprzecinka(slowo);
							bool czy_d = false;
							if (czyGwiazda(slowo))
							{
								lista_sekcji = usunSekcje(lista_sekcji, liczba_i, &czy_d);
								if (czy_d)
								{
									print(komenda);
									cout << " == ";
									cout << "deleted\n";
								}
								del(slowo);
								slowo = nullptr;
							}
							else
							{
								lista_sekcji = usunAtrybut(lista_sekcji, liczba_i, slowo, &czy_d);
								if (czy_d)
								{
									print(komenda);
									cout << " == ";
									cout << "deleted\n";
								}
								del(slowo);
								slowo = nullptr;
							}
						}
					}
					else
					{
						str* nazwa = nullptr;
						nazwa = get_Slowo(slowo);
						if (nazwa != nullptr)
						{
							slowo = usunDoprzecinka(slowo);
							if (czyA(slowo))
							{
								slowo = usunDoprzecinka(slowo);
								if (czyZnakzapytania(slowo))
								{
									print(komenda);
									cout << " == ";
									cout << ileAtrAll(lista_sekcji, nazwa);
									cout << endl;
									del(slowo);
									slowo = nullptr;
								}
								else
								{
									del(slowo);
									slowo = nullptr;
								}
							}
							else if (czyS(slowo))
							{
								print(komenda);
								cout << " == ";
								cout << ileSeleAll(lista_sekcji, nazwa);
								cout << endl;
								del(slowo);
								slowo = nullptr;
							}
							else if (czyE(slowo))
							{
								slowo = usunDoprzecinka(slowo);
								str* tmp = WartoscAtrodSele(lista_sekcji, nazwa, slowo);
								if (tmp != nullptr)
								{
									print(komenda);
									cout << " == ";
									print(tmp);
									cout << endl;
								}
								del(slowo);
								slowo = nullptr;
							}
							else
							{
								del(slowo);
								slowo = nullptr;
							}
						}
						else
						{
							del(slowo);
							slowo = nullptr;
						}
					}

				}
				del(slowo);
				slowo = nullptr;
			}
		}
		
	}

	del(slowo);
	del(komenda);
	lista_sekcji = deleteAll(lista_sekcji);


	return 0;

}
