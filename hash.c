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
        struct linkedlist bucket[31];
};

void createtable(int len, struct linkedlist *hash);

int main()
{
        struct linkedlist hash[31];
        for(int i = 0; i < 31; i++)
                printf("%c", hash[i].real);


        return 0;
}


void createtable(int len, struct linkedlist *hash)
{
        for (int i = 0; i < len; i++){
                hash[i].real = 'F';
                hash[i].next = NULL;
        }

}


struct linkedlist *initialize(char *mess)
{

}


int radix(char *mess)
{
        int key;


        return key;
}


int pow(int base, int power)
{
        if(power == 0){
                base = 0;
        } else{
                for (int i = 0; i < power; i++)
                        base *= base;
        }

        return base;
}