/**
 * File: main.c
 * Author: Joe Shang <shangchuanren@gmail.com>
 * Brief: The main program for testing dlist.
 */

#include <stdio.h>
#include "dlist.h"

Ret print_int(void *ctx, void *data)
{
    int i = (int)data;
    printf("%d ", i);

    return RET_OK;
}

int equal_int(void *ctx, void *data)
{
    return ((int)ctx == (int)data);
}

int main(int argc, char *argv[])
{
    int i;
    DList *list = NULL;

    list = dlist_create(NULL, NULL);

    for (i = 0; i < 10; i++)
    {
        dlist_prepend(list, (void *)i);
    }

    printf("dlist length: %d\n", dlist_length(list));
    dlist_foreach(list, print_int, NULL);
    printf("\n");

    for (i = 0; i < 10; i++)
    {
        dlist_delete(list, 0);
    }

    printf("dlist length: %d\n", dlist_length(list));
    dlist_foreach(list, print_int, NULL);
    printf("\n");

    for (i = 0; i < 10; i++)
    {
        dlist_append(list, (void *)i);
    }

    printf("dlist length: %d\n", dlist_length(list));
    dlist_foreach(list, print_int, NULL);
    printf("\n");

    dlist_set_by_index(list, 0, (void *)-1);
    dlist_get_by_index(list, 0, (void **)&i);
    printf("index 0: %d\n", i);

    i = dlist_find(list, equal_int, (void *)5);
    printf("the index of data which is equal to 5: %d\n", i);

    dlist_destroy(list);

    return 0;
}
