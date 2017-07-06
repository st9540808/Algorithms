/**
 *	2017 7/6
 *	using a modulo hash table for O(1) key search and insert
 *	and a doubly linked list to keep track of the prioirity
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct llist_node llist_node;

typedef struct entry {
	int key;
	int value;
	llist_node *node_ptr;
	struct entry *next;
	struct entry *prev;
} entry;

// NULL terminated doubly llist
typedef struct llist_node {
	entry *entry_ptr;
	struct llist_node *next;
	struct llist_node *prev;
} llist_node;

typedef struct LRUCache {
	entry **data; // resolve collision by chaining
	llist_node *priority_head;
	llist_node *priority_tail;
	int size;
	int capacity;
} LRUCache;

static inline // node_ptr should not be the tail of priority_list
void lRUCache_llist_put_in_tail(LRUCache *obj, llist_node *node_ptr)
{
	if (obj->priority_tail == node_ptr || obj->capacity == 1) return;
	node_ptr->prev->next = node_ptr->next;
	node_ptr->next->prev = node_ptr->prev;
	node_ptr->prev = obj->priority_tail;
	node_ptr->next = NULL;
	obj->priority_tail->next = node_ptr;
	obj->priority_tail = node_ptr;
}

static inline
void lRUCache_entry_put_in_head(LRUCache *obj, int slot_index, entry *entry_ptr)
{
	entry_ptr->next = obj->data[slot_index];
	entry_ptr->prev = NULL;
	if (obj->data[slot_index] != NULL)
		obj->data[slot_index]->prev = entry_ptr;
	obj->data[slot_index] = entry_ptr;
}

LRUCache* lRUCacheCreate(int capacity)
{
	LRUCache *obj = malloc(sizeof(LRUCache));
	obj->data = calloc(capacity, sizeof(entry *));
	
	// create sentinel
	obj->priority_head = calloc(1, sizeof(llist_node));
	obj->priority_tail = obj->priority_head;

	obj->size = 0;
	obj->capacity = capacity <= 0 ? 1 : capacity; // default capicity is 1
	return obj;
}

int lRUCacheGet(LRUCache* obj, int key)
{
	entry *entry_ptr = obj->data[key % obj->capacity];
	while (entry_ptr != NULL) {
		if (entry_ptr->key == key) {
			lRUCache_llist_put_in_tail(obj, entry_ptr->node_ptr);
			return entry_ptr->value;
		}
		entry_ptr = entry_ptr->next;
	}
	return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value)
{
	const int slot_index = key % obj->capacity;
	
	// find duplicate
	do {
		entry *entry_ptr = obj->data[slot_index];
		while (entry_ptr != NULL) {
			if (entry_ptr->key == key) {
				entry_ptr->value = value;
				lRUCache_llist_put_in_tail(obj, entry_ptr->node_ptr);
				return;
			}
			entry_ptr = entry_ptr->next;
		}
	} while (0);
	
	if (obj->size < obj->capacity) {
		obj->size++;

		// allocate an entry and initialize
		entry *new_entry = malloc(sizeof(entry));
		new_entry->key = key;
		new_entry->value = value;

		// insert into the head of slot chain
		lRUCache_entry_put_in_head(obj, slot_index, new_entry);

		// allocate priority node and set relation between entry and llist_node
		llist_node *new_llist_node = malloc(sizeof(llist_node));
		new_entry->node_ptr = new_llist_node; 
		new_llist_node->entry_ptr = new_entry;
		
		// insert into the tail of the priority list
		new_llist_node->next = NULL;
		new_llist_node->prev = obj->priority_tail;
		obj->priority_tail->next = new_llist_node;
		obj->priority_tail = new_llist_node;
	} else {
		// retrieve the first element in priority list
		llist_node *node_ptr = obj->priority_head->next;
		entry *entry_ptr = node_ptr->entry_ptr;
		const int evict_slot_index = entry_ptr->key % obj->capacity;

		// re-assign key and value
		entry_ptr->key = key;
		entry_ptr->value = value;
		
		// retrieve entry_ptr and put it in the new hash slot
		if (entry_ptr->prev == NULL) {
			if (entry_ptr->next != NULL)
				entry_ptr->next->prev = NULL;
			obj->data[evict_slot_index] = entry_ptr->next;
		} else {
			if (entry_ptr->next != NULL)
				entry_ptr->next->prev = entry_ptr->prev;
			entry_ptr->prev->next = entry_ptr->next;
		}
		lRUCache_entry_put_in_head(obj, slot_index, entry_ptr);
		lRUCache_llist_put_in_tail(obj, node_ptr); // update prioirty list
	}
}

void lRUCacheFree(LRUCache* obj)
{
	// free entry hash table
	for (int i = 0; i < obj->capacity; i++) {
		while (obj->data[i] != NULL) {
			entry *node_ptr = obj->data[i];
			obj->data[i] = obj->data[i]->next;
			free(node_ptr);
		}
	}
	free(obj->data);
	
	// free llist
	llist_node *current_ptr = obj->priority_head;
	while (current_ptr != NULL) {
		llist_node *node_ptr = current_ptr;
		current_ptr = current_ptr->next;
		free(node_ptr);
	}
	free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */

int main()
{
	struct LRUCache* obj = lRUCacheCreate(6);
	printf("value : %d\n", lRUCacheGet(obj, 2));
	lRUCachePut(obj, 2, 6);
	printf("value : %d\n", lRUCacheGet(obj, 1));
	lRUCachePut(obj, 1, 5);
	lRUCachePut(obj, 1, 2);
	lRUCachePut(obj, 4, 4);
	lRUCachePut(obj, 7, 7);
	lRUCachePut(obj, 3, 3);
	printf("value : %d\n", lRUCacheGet(obj, 1));
	printf("value : %d\n", lRUCacheGet(obj, 2));
	lRUCachePut(obj, 5, 5);
	lRUCachePut(obj, 12, 12);
	lRUCachePut(obj, 13, 13);
	lRUCachePut(obj, 11, 11);
	printf("value : %d\n", lRUCacheGet(obj, 5));
	printf("value : %d\n", lRUCacheGet(obj, 4));
	printf("value : %d\n", lRUCacheGet(obj, 1));

	lRUCacheFree(obj);

	return 0;
}
