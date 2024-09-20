#include "hashmap.h"
#include <unistd.h>

#define HTABLE_LEN 7

/* 创建hashmap */
hashtable_t **create_hashtable()
{
    int i;
    hashtable_t **h = NULL;
    h = (hashtable_t **)malloc(HTABLE_LEN * sizeof(hashtable_t *));

    memset(h, 0, sizeof(HTABLE_LEN * sizeof(hashtable_t *)));

    for (i = 0; i < HTABLE_LEN; i++)
    {
        h[i] = NULL;
    }
    return h;
}

/* 插入数据: key - value */
void insert_data_hash(hashtable_t **h, char * key, datatype_t value)
{
    hashtable_t *temp = NULL;
    hashtable_t **p = NULL;

    int index = 0, i = 0;
    int code = 0;

    code = hashcode(key);

    index = code % HTABLE_LEN;

    for (p = &h[index]; *p != NULL; p = &((*p)->next))
    {
        if ((*p)->data.pid > value.pid)
            break;
    }

    temp = (hashtable_t *) malloc(sizeof(hashtable_t));
    temp->data = value;
    temp->next = *p;
    *p = temp;
    return;
}

/* 输出hashmap */
void printf_hash_table(hashtable_t **h)
{
    int i = 0;
    hashtable_t **p = NULL;

    for(i = 0; i < HTABLE_LEN; i++)
    {
        printf("index = %d : ", i);
        for (p = &h[i]; *p != NULL; p = &((*p)->next))
        {
            printf("%s\n",(*p)->data.topic);
        }
        putchar('\n');
    }
    return;
}

/* 计算key的hashcode */
int hashcode(const char *string)
{
    int hashcode = 0;

    while(*string)
    {
        hashcode += *string++;
    }

    return hashcode;
}

/* 查询数据 */
int search_hash_table(hashtable_t **h, char * key, pid_t result[])
{
    int code = hashcode(key);
    int cnt = 0;
    int index = code % HTABLE_LEN;
    hashtable_t **p = NULL;
    printf("index = %d\n", index);

    for (p = &h[index]; *p != NULL; p = &((*p)->next))
    {
        printf("key : %s,(*p)->data.topic : %s\n",key,(*p)->data.topic);
        if (strcmp(key,(*p)->data.topic) == 0)
        {
            return result[cnt++] = (*p)->data.pid;
        }
    }

    return cnt;
}

/* int main(int argc, char const *argv[])
{
    // char *p = "hello";

    // int num = hashcode(p);

    // printf("num = %d\n", num);

    
    hashtable_t **h = create_hashtable();

    char * key = "name";
    datatype_t data;
    data.pid = getpid();
    strcpy(data.topic, "name");
    insert_data_hash(h, key, data);

    char * key1 = "age";
    datatype_t data1;
    data1.pid = getpid();
    strcpy(data1.topic, "age");
    insert_data_hash(h, key1, data1);

    char * key2 = "job";
    datatype_t data2;
    data2.pid = getpid();
    strcpy(data2.topic, "job");
    insert_data_hash(h, key2, data2);

    pid_t result[] = {0};
    // search_hash_table(h, key1, result);

    printf_hash_table(h);

    return 0;
}
 */