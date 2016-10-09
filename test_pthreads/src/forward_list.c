#include "forward_list.h"
#include <stdlib.h>

struct forward_list_ctx {
	pred p;
	node *root;
};

static const node* fl_insert(struct forward_list *self, int key);
static const node* fl_find(struct forward_list *self, int key);
static node* fl_find_with_parent(struct forward_list *self, int key, node **parent);
static const node* fl_erase(struct forward_list *self, int key);
static const node* fl_front(struct forward_list *self);
static void fl_clear(struct forward_list *self);

forward_list* alloc_forward_list(pred p)
{
	forward_list *r = malloc(sizeof(forward_list));
	init_forward_list(r, p);
	return r;
}

void init_forward_list(forward_list *fl, pred p)
{
	forward_list_ctx *ctx = malloc(sizeof(forward_list_ctx));
	ctx->root = 0;
	ctx->p = p;

	fl->ctx = ctx;
	fl->insert = fl_insert;
	fl->find = fl_find;
	fl->erase = fl_erase;
	fl->front = fl_front;
	fl->clear = fl_clear;
}

void free_forward_list(forward_list *fl)
{
	fl_clear(fl);
	free(fl->ctx);
	free(fl);
}

void clean_forward_list(forward_list *fl)
{
	fl_clear(fl);
	free(fl->ctx);
	fl->ctx = 0;
}

int fl_default_pred(int l, int r)
{
	return l > r;
}

static const node* fl_insert(struct forward_list *self, int key)
{
	node *res = 0;
	forward_list_ctx *ctx = self->ctx;

	res = malloc(sizeof(node));
	res->key = key;
	res->next = 0;

	if (!ctx->root) {
		ctx->root = res;
	} else {
		node *p = 0;
		node *i;
		for (i = ctx->root; i != 0; p = i, i = i->next) {
			if (ctx->p(i->key, key)) {
				if (p) {
					p->next = res;
				} else {
					ctx->root = res;
				}
				res->next = i;
				break;
			}
		}
		if (!i)
			p->next = res;
	}

	return res;
}

static const node* fl_find(struct forward_list *self, int key)
{
	return fl_find_with_parent(self, key, 0);
}

static node* fl_find_with_parent(struct forward_list *self, int key, node **parent)
{
	node *p = 0;
	node *i = self->ctx->root;
	for (; i != 0; p = i, i = i->next) {
		if (i->key == key) break;
	}

	if (parent) {
		if (i) *parent = p;
		else *parent = 0;
	}

	return i;
}

static const node* fl_erase(struct forward_list *self, int key)
{
	node* p = 0;
	node* n = fl_find_with_parent(self, key, &p);

	if (n) {
		if (p)
			p->next = n->next;
		else
			self->ctx->root = n->next;

		free(n);
	}

	return n;
}

static const node* fl_front(struct forward_list *self)
{
	return self->ctx->root;
}

static void fl_clear(struct forward_list *self)
{
	node *i = self->ctx->root;
	node *t = 0;
	for (; i != 0; i = t) {
		t = i->next;
		free(i);
	}

	self->ctx->root = 0;
}

