#pragma once
#include "str.h"
#include "define.h"
#include "selektory.h"
#include "atrybuty.h"

struct dane_s {
	selektory* sele;
	atrybuty* atr;
};

struct sekcje {
	int ile_w_tabeli;
	dane_s data[T];
	sekcje* next;
	sekcje* prev;
};

sekcje* addNew(sekcje* skj, str* nazwa);

sekcje* deleteOne(sekcje* skj, int numer_w_tabeli);

sekcje* deleteAll(sekcje* skj);

sekcje* deleteNode(sekcje* skj);

sekcje* getLast(sekcje* skj);
int getIndexSele(sekcje* skj);
int getIndexAtr(sekcje* skj);

int ileSekcji(sekcje* skj);



