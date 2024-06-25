#pragma once
#include "str.h"
#include "sekcje.h"
#include "selektory.h"

bool endOfcss(str* s);
bool startOfcss(str* s);
bool czyZnakzapytania(str* s);
bool liczba(str* s);
bool validkomend(str* s);
bool zaczynaodLiczby(str* s);
bool czyS(str* s);
bool czyA(str* s);
bool czyE(str* s);
bool czyD(str* s);
bool czyGwiazda(str* s);
bool jestSekcjanumer(sekcje* skj, int numer);
bool jestSelenumer(selektory* sele, int numer);
bool jestAtronazwie(atrybuty* atr, str* nazwa);

int get_Liczba(str* s);
str* get_Slowo(str* s);

selektory* getSelektoryZSekcjinumer(sekcje* skj, int numer);
atrybuty* getAtrybutyZSekcjinumer(sekcje* skj, int numer);

str* usunDoprzecinka(str* s);
str* usunDoprzecinkatmp(str* s);
str* usunLiterki(str* s);
str* usunLiczby(str* s);

int ileSeleDlaiSekcji(sekcje* skj, int numer);
int ileAtrDlaiSekcji(sekcje* skj, int numer);

int ileAtrAll(sekcje* skj, str* nazwa);
int ileSeleAll(sekcje* skj, str* nazwa);

str* Selenumer(selektory* sele, int numer);
str* WartoscAtroNazwie(atrybuty* atr, str* nazwa);
str* WartoscAtrodSele(sekcje* skj, str* nazwa_sele, str* nazwa_atr);

sekcje* usunSekcje(sekcje* skj, int numer, bool* d);
sekcje* usunAtrybut(sekcje* skj, int numer, str* nazwa_atr, bool* d);