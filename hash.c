/**
 * 
 * @remark radix found by
 * char1 *128^0 + char2 * 128^1 + char 3 * 128^2 * 128^3 + char 4
*/

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