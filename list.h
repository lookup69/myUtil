#ifndef _COMMON_LIST_H_
#define _COMMON_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_node_s list_node_t;
struct list_node_s {
    list_node_t *next;
    list_node_t *prev;
    void *cookie;
};

void list_head_init(list_node_t *head_ptr);
int list_insert_end(list_node_t *head_ptr, void *cookie);

#define list_for_each(pos, head) \
    for(pos = (head)->next; pos != (head); pos = pos->next)

#ifdef __cplusplus
}
#endif

#endif
