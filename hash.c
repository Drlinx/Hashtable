/**
 * @file queuesandstacks.c
 * 
 * @author Kassidy Maberry
 * 
 * @date 2022/08/28
 * 
 * Assignment: Queues and Stacks
 * 
 * @brief A program that works with either a queue or stack data structure.
 * 
 * @detail A program that works with either a queue or stack. Does various 
 * operations for each. Adding an element, removing an element, or checking
 * if it is an empty. The 3 major operations all work within queue and stack
 * limitations.
 * 
 * @bugs none
 * 
 * @todo none
 */

#include <stdio.h>
#include <stdlib.h>


//linked list which will represent the elements in the bucket.
struct linkedlist
{
        long long key;
        char *word;
        struct linkedlist *next;
};


//Hashtable itself which will be an array and each one has a bucket(linkedlist)
struct hashtab
{
        struct linkedlist *bucket;
};

void createtable(int len, struct linkedlist *hash);
long long radix(char *mess);
long long pow(long long base, int power);
struct linkedlist *init_bucket(char *mess);


int main()
{
        //Hashtab works as an array of linked lists which represent buckets.
        struct hashtab hash[31];
        inithas(hash, 31);


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


/**
 * @brief creates an element for us to put into a bucket. The bucket will be
 * determined upon insertion.
 * 
 * @param mess the message we are adding into the bucket.
 * @return the pointer to the newly created bucket. 
 */
struct linkedlist *init_bucket(char *mess)
{
        struct linkedlist *new = malloc(sizeof(struct linkedlist));
        if(!new)
                exit(6);
        new->word = mess;
        new->key = radix(mess);
        new->next = NULL;
        return new;
}


/**
 * @brief A funtion that will gather the radix of a given message.
 * @remark uses the first for characters.
 * @param mess the messsage we are adding.
 * 
 */
long long radix(char *mess)
{
        long long key;
        for(int i = 0; i < 4; i++){
                if(mess[i] == '\0'){
                        break;
                }
                key = key + (mess[i] * pow(128, i));
        }
        return key;
}


/**
 * @brief a function that will get the power of something
 * 
 * @param base the base we are putting to the power of something 
 * @param power the degree of said power
 * @return the new base.
 */
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


/**
 * @brief removes a new line from a provided message 
 * 
 * @param mess the message we are modifying
 */
void nl_remove(char *mess)
{
        for(int i = 0; mess[i] !=' \0'; i++){
                if (mess[i] == '\n'){
                        mess[i] = '\0';
                        break;
                }
        }
}


/**
 * @brief gets an input for a characterized message.
 * 
 * @return the message with the new line removed.
 */
char *get_input(void)
{
        char z[128];
        printf("What message are we storing: ");
        fgets(z, 128, stdin);
        nl_remove(z);
        return z;
}


/**
 * @brief prints out the entire hash table.
 * 
 * @param hash the hash table itself.
 * @param len the length of the table.
*/
void printhash(struct hashtab *hash, int len)
{
        for(int i = 0; i < len; i++){   
                printf("Bucket %d: ", i + 1);
                printbucket(hash[i].bucket);
        }
}


void printbucket(struct linkedlist *bucket)
{
        if(bucket != NULL){
                printf("%s ", bucket->word);
                printbucket(bucket->next);
        }
}


void insert(struct hashtab *has, struct linkedlist *bucket)
{
        long long key = bucket->key % 31;
        if (has[key].bucket == NULL)
                has[key].bucket = bucket;
        else{
                collision(has[key].bucket, bucket);
        }
}


void collision(struct linkedlist *cur, struct linkedlist *addon)
{
        while(cur->next != NULL){
                cur = cur->next;
        }
        cur->next = addon;
}


void delete(struct hashtab *has, long long key)
{
        struct linkedlist *bucket, *prev;
        bucket = has[key % 31];
        while(bucket != NULL && bucket->key != key){
                prev = bucket;
                bucket = bucket->next;
        }
        if(prev != NULL){
                prev->next = bucket->next;
                free(bucket);
        } else {
                has[key % 31].bucket = NULL;
                free(bucket);
        }
}