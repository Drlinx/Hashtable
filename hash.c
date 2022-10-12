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
        struct linkedlist *bucket;
};

void createtable(int len, struct linkedlist *hash);
long long radix(char *mess);
long long pow(long long base, int power);

int main()
{
        //Hashtab works as an array of linked lists which represent buckets.
        struct hashtab hash[31];


        return 0;
}

/**
 * @brief quickly sets up an array of buckets by setting each pointer to null.
 * 
 * @param hash the hashtable itself.
 * @param len the length of said hashtable. 
 */
void inithas(struct hashtab *hash, int len)
{
        for(int i = 0; i < len; i++){
                hash[i].bucket = NULL;
        }
}


struct linkedlist *initialize(char *mess)
{
        struct linkedlist *new = malloc(sizeof(struct linkedlist));
        if(!new)
                exit(6);
        new->word = mess;
        new->key = radix(mess);
        new->next = NULL;
        return new;
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