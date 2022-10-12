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
long long radix(char *mess);
long long pow(long long base, int power);

int main()
{
        struct linkedlist hash[31];


        return 0;
}


struct linkedlist *initialize(char *mess)
{

}


long long radix(char *mess)
{
        long long key;
        for(int i = 0; i < 4; i++){
                key = key + (mess[i] * pow(128, i));
        }
        return key;
}


long long pow(long long base, int power)
{
        if(power == 0){
                base = 1;
        } else{
                for (int i = 0; i < power; i++)
                        base *= base;
        }

        return base;
}