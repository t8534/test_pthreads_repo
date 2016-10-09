#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

typedef struct forward_list_ctx forward_list_ctx;
typedef int (*pred)(int l, int r);

typedef struct node {
	int key;
	struct node *next;
} node;

typedef struct forward_list {
	forward_list_ctx *ctx;
	const node* (*insert)(struct forward_list *self, int key);
	const node* (*find)(struct forward_list *self, int key);
	const node* (*erase)(struct forward_list *self, int key);
	const node* (*front)(struct forward_list *self);
	void (*clear)(struct forward_list *self);
} forward_list;

forward_list* alloc_forward_list(pred p);
void init_forward_list(forward_list *fl, pred p);

void free_forward_list(forward_list *fl);
void clean_forward_list(forward_list *fl);

int fl_default_pred(int l, int r);

#endif

