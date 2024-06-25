#pragma once
#include <iostream>

struct str {
    char s;
    str* next; 
    str* prev;
};

str* add(str* head, char n);

str* addLast(str* tail, char n);

void del(str* s);

void print(str* str);

bool same(str* s1, str* s2);

str* copy(str* s);

void usunWS(str* s);