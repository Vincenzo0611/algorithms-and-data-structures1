#pragma once
#include "str.h"
#include "define.h"

struct dane_a {
	str* nazwa;
	str* wartosc;
};

struct atrybuty {
	int ile_w_tabeli;
	dane_a data[T];
	atrybuty* next;
	atrybuty* prev;
};

atrybuty* addNew(atrybuty* atr, str* nazwa, str* wartosc);


atrybuty* deleteOne(atrybuty* atr, int wartosc_w_tabeli);

atrybuty* deleteAll(atrybuty* atr);


void deleteNode(atrybuty* atr);

int getLastIndex(atrybuty* atr);



