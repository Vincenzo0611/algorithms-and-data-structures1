#include <iostream>
#include "str.h"
#include "define.h"

str* add(str* head, char n)
{
    str* newS = new str;
    newS->s = n;
    newS->next = nullptr;
    newS->prev = nullptr;

    if (head == nullptr) {
        head = newS;
    }
    else {
        str* tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = newS;
        newS->prev = tmp;
    }

    return head;
}

str* addLast(str* tail, char n)
{
    str* newS = new str;
    newS->s = n;
    newS->next = nullptr;
    newS->prev = tail;

    if (tail == nullptr) {
        return newS;
    }

    tail->next = newS;

    return newS;
}


void del(str* s)
{
    if (s != nullptr)
    {
        str* tmp = s->next;
        while (tmp != nullptr)
        {
            delete s;
            s = tmp;
            tmp = tmp->next;
        }
        delete s;
    }
}
void print(str* str)
{
    while (str != nullptr)
    {
        std::cout << str->s;
        str = str->next;
    }
}

bool same(str* s1, str* s2)
{
    if (s1 == nullptr || s2 == nullptr)
        return false;

    while (s1 != nullptr && s2 != nullptr)
    {
        if (s1->s != s2->s)
            return false;
        s1 = s1->next;
        s2 = s2->next;
    }

    if (s1 == nullptr && s2 == nullptr)
        return true;
    return false;
}

str* copy(str* s)
{
    str* copy = nullptr;
    while (s != nullptr)
    {
        copy = add(copy,s->s);
        s = s->next;
    }

    return copy;
}

void usunWS(str* s)
{
    if (s == nullptr)
        return;
    while (s->prev->s <= SPACJA)
    {
        s = s->prev;
    }
    if (s->s <= SPACJA)
    {
        s->prev->next = nullptr;
        del(s);
    }
}
