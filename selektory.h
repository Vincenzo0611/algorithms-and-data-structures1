#pragma once
#include "str.h"
#include "define.h"

struct dane {
	str* nazwa;
};

struct selektory {
	int ile_w_tabeli;
	dane data[T];
	selektory* next;
	selektory* prev;
};

selektory* addNew(selektory* sele, str* nazwa);


selektory* deleteOne(selektory* sele, int numer_w_tabeli);

selektory* deleteAll(selektory* sele);

void deleteNode(selektory* sele);

selektory* getLast(selektory* sele);

