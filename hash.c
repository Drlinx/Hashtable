#include <stdio.h>

struct linkedlist
{
        long long key;
        char *word;
        struct linkedlist *next;
};


struct hashtab
{
        long long key;
        struct linkedlist *val;
        struct hashtab *next;
};


int main()
{



        return 0;
}