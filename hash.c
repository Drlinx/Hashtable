/**
 * @file hash.c
 * 
 * @author Kassidy Maberry
 * 
 * @date 2022/10/23
 * 
 * Assignment: hash table
 * 
 * @brief Working hash table.
 * 
 * @detail A program that show cases a hash table with a few basic
 * functions such as insert delete and a file import function.
 * 
 * @bugs none
 * 
 * @todo Menus, debugging, y see what else is left.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//linked list which will represent the elements in the bucket.
struct linkedlist
{
        long int key;
        char *word;
        struct linkedlist *next;
};


//Hashtable itself which will be an array and each one has a bucket(linkedlist)
struct hashtab
{
        struct linkedlist *bucket;
};

void createtable(int len, struct linkedlist *hash);
long int radix(char *mess);
long int power(long int base, int pow);
struct linkedlist *init_bucket(char *mess);
void inithas(struct hashtab *has, int len);
struct linkedlist *init_bucket(char *mess);
void nl_remove(char *mess);
char *get_input(void);
void printhash(struct hashtab *hash, int len);
void printbucket(struct linkedlist *bucket);
void insert(struct hashtab *has, struct linkedlist *bucket);
void collision(struct linkedlist *cur, struct linkedlist *addon);
void delete(struct hashtab *has, long int key);
FILE *grabfile(void);
void mass_insert(struct hashtab *has);



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
long int radix(char *mess)
{
        long int key;
        for(int i = 0; i < 4; i++){
                if(mess[i] == '\0'){
                        break;
                }
                key = key + (mess[i] * power(128, i));
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
long int power(long int base, int pow)
{
        if(pow == 0){
                base = 1;
        } else{
                for (int i = 0; i < pow; i++)
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


/**
 * @brief prints out all the elements in a given bucket
 * 
 * @param bucket the bucket we are currently looking at
*/
void printbucket(struct linkedlist *bucket)
{
        if(bucket != NULL){
                printf("%s ", bucket->word);
                printbucket(bucket->next);
        }
}


/**
 * @brief inserts a given element into the linked list
 * 
 * @param has the has table
 * @param bucket the bucket we are adding
*/
void insert(struct hashtab *has, struct linkedlist *bucket)
{
        long int key = bucket->key % 31;
        if (has[key].bucket == NULL)
                has[key].bucket = bucket;
        else{
                collision(has[key].bucket, bucket);
        }
}


/**
 * @brief deals with collisions when adding to the linked list
 * 
 * @param cur the first bucket in the has table.
 * @param addon the bucket we are adding.
*/
void collision(struct linkedlist *cur, struct linkedlist *addon)
{
        while(cur->next != NULL){
                cur = cur->next;
        }
        cur->next = addon;
}


/**
 * @brief deletes a given key from the function key is gotten from the
 * radix of the user input.
 * @remark If multiple inputs have the same key seems like its gonna delete 
 * them all
 * 
 * @param has the hash table
 * @param key they key we are deleting
 */
void delete(struct hashtab *has, long int key)
{
        struct linkedlist *bucket, *prev;
        prev = NULL;
        bucket = has[key % 31].bucket;
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


/**
 * @brief gets a files pathway.
 * @remark this is a helper function for mass inserts.
 * 
 * @param path the path of the file
 * @return the file location.
 */
FILE *grabfile(void)
{
        char path[128];
        printf("Please enter a file pathway. WARNGING IF THE PATHWAY DOES NOT");
        printf(" EXIST THE PROGRAM WILL CRASH.\n");
        fgets(path, 128, stdin);
        FILE *fp = fopen(path, "r");
        if(fp == NULL){
                printf("Wrong file path\n");
                printf("please use ./[file pathway]\n");
                fp = grabfile();
        }
        return fp;
}


/**
 * @brief does a mass insertion of a file.
 * 
 * @param has is the hash table we are inserting to.
 * 
 */
void mass_insert(struct hashtab *has)
{
        FILE *fp = grabfile();
        char message[128];
        while(1 == 1){
                fgets(message, 128, fp);
                insert(has, init_bucket(message));
                if(message[strlen(message) - 1] != '\n')
                        break;
        }
}