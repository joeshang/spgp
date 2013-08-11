/**
 * File: dlist.h
 * Author: Joe Shang <shangchuanren@gmail.com>
 * Brief: double-linked list.
 */

#ifndef _DLIST_H_
#define _DLIST_H_

#include "typedef.h"

DECLS_BEGIN

struct _DList;
typedef struct _DList DList;

DList *dlist_create(DataDestroyFunc destroy, void *destroy_ctx);
void   dlist_destroy(DList *thiz);
Ret    dlist_insert(DList *thiz, size_t index, void *data);
Ret    dlist_append(DList *thiz, void *data);
Ret    dlist_prepend(DList *thiz, void *data);
Ret    dlist_delete(DList *thiz, size_t index);
Ret    dlist_set_by_index(DList *thiz, size_t index, void *data);
Ret    dlist_get_by_index(DList *thiz, size_t index, void **data);
size_t dlist_length(DList *thiz);
int    dlist_find(DList *thiz, DataCompareFunc compare, void *ctx);
Ret    dlist_foreach(DList *thiz, DataVisitFunc visit, void *ctx);

DECLS_END

#endif
