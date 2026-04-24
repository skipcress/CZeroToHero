#include <stddef.h>
#include <stdlib.h>
#include "kv.h"

kv_t *kv_init(size_t capacity) {
	if(0 == capacity) {
		return NULL;
	}

	kv_t *table = malloc(sizeof(kv_t));
	if(NULL == table) {
		return NULL;
	}

	table->capacity = capacity;
	table->count = 0;
	
	table->entries = calloc(sizeof(kv_entry_t), capacity);
	if(NULL == table->entries) {
		return NULL;
	}

	return table;
}

void kv_free(kv_t *table) {
	free(table->entries);
	table->entries = NULL;

	free(table);
	table = NULL;
}	
