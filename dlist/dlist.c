/**
 * File: dlist.c
 * Author: Joe Shang <shangchuanren@gmail.com>
 * Brief: double-linked list.
 */

#include "dlist.h"

#include <stdlib.h>

typedef struct _DListNode
{
    struct _DListNode *prev;
    struct _DListNode *next;
    void *data;
}DListNode;

struct _DList
{
    DListNode *head;
    size_t length;
    DataDestroyFunc data_destroy;
    void *data_destroy_ctx;
};

static DListNode *dlist_node_create(void *data)
{
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));

    if (node != NULL)
    {
        node->prev = NULL;
        node->next = NULL;
        node->data = data;
    }

    return node;
}

static void dlist_node_destroy(DListNode *node,
        DataDestroyFunc data_destroy,
        void *data_destroy_ctx)
{
    if (node != NULL)
    {
        node->prev = NULL;
        node->next = NULL;
        if (data_destroy != NULL)
        {
            data_destroy(node->data, data_destroy_ctx);
        }

        free(node);
    }
}

static DListNode *dlist_get_node(DList *thiz, 
        size_t index, int return_last_if_outrange)
{
    DListNode *iter = thiz->head;
    while (iter != NULL && index > 0)
    {
        iter = iter->next;
        index--;
    }

    /* node's index is out of range */
    if (index > 0 && !return_last_if_outrange)
    {
        iter = NULL;
    }

    return iter;
}

DList *dlist_create(DataDestroyFunc data_destroy, void *data_destroy_ctx)
{
    DList *thiz = (DList *)malloc(sizeof(DList));

    if (thiz != NULL)
    {
        thiz->head = NULL;
        thiz->length = 0;
        thiz->data_destroy = data_destroy;
        thiz->data_destroy_ctx = data_destroy_ctx;
    }

    return thiz;
}

void dlist_destroy(DList *thiz)
{
    DListNode *iter = thiz->head;
    DListNode *next = NULL;
    
    while (iter != NULL)
    {
        next = iter->next; 
        dlist_node_destroy(iter, thiz->data_destroy, thiz->data_destroy_ctx);
        iter = next;
    } 

    thiz->head = NULL;
    free(thiz);
}

Ret dlist_insert(DList *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    DListNode *cursor = NULL;
    DListNode *node = NULL;
    
    if ((node =dlist_node_create(data)) == NULL)
    {
        return RET_OOM;
    }

    thiz->length++;

    /* 1. insert when list empty */
    if (thiz->head == NULL)
    {
        thiz->head = node;
        return RET_OK;
    }

    /* find the insert positon */
    cursor = dlist_get_node(thiz, index, 1);

    if (index < thiz->length)
    {
        /* 2. insert at the top of list */
        if (thiz->head == cursor)
        {
            thiz->head = node;
        }
        /* 3. insert at the middle of list */
        else
        {
            node->prev = cursor->prev;
            cursor->prev->next = node;
        }
        node->next = cursor;
        cursor->prev = node;
    }
    /* 4. insert at the end of list */
    else
    {
        cursor->next = node;
        node->prev = cursor;
    }

    return RET_OK;
}

Ret dlist_delete(DList *thiz, size_t index, void **data)
{
    /* 1. delete at the top of list */
    /* 2. delete at other positions */

    return RET_OK;
}

size_t dlist_length(DList *thiz)
{
    return thiz->length;
}

