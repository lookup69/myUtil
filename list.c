#include "debugUtility.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

void list_head_init(list_node_t *head_ptr)
{
    memset(head_ptr, 0, sizeof(list_node_t));
    head_ptr->next = head_ptr;
    head_ptr->prev = head_ptr;
}

int list_insert_end(list_node_t *head_ptr, void *cookie)
{
    list_node_t *node;

    node = (list_node_t *)malloc(sizeof(list_node_t));
    if(!node) {
        DEBUG_PRINT("%s\n", "malloc() fail");
        return -1;
    }

    memset(node, 0, sizeof(*node));
    node->cookie = cookie;
    if(head_ptr->next == head_ptr) {
        head_ptr->next = node;
        head_ptr->prev = node;
        node->next = head_ptr;
        node->prev = head_ptr;
    } else {
        head_ptr->prev->next = node;
        node->prev = head_ptr->prev;
        node->next = head_ptr;
        head_ptr->prev = node;
    }
    
    return 0;
}
