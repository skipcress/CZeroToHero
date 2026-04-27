#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

#define DEAD 0x1

size_t hash(char *key, size_t capacity) {
	size_t hash = 0x123456789;
	while(*key) {
		hash ^= *key;
		hash = hash << 8;
		hash += *key;

		key++;
	}

	return hash % capacity;
} 

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

// Returns index of the key, otherwise -1
size_t kv_put(kv_t *table, char *key, char *value) {
	if(!key || !value) {
		return -1;
	}

	size_t index = hash(key, table->capacity);

	for(int i = 0; i < table-> capacity; i++) {
		size_t walking_index = (index + i) % table->capacity;

		kv_entry_t *entry = &table->entries[walking_index];
		if(entry->key
			&& !strcmp(entry->key, key)
			&& entry->key != (void*)DEAD) {
			char *newVal = strdup(value);

			if(!newVal) {
				return -1;
			}

			entry->value = newVal;

			return walking_index;
		}

		if(!entry->key || entry->key == (void*)DEAD) {
			char *newVal = strdup(value);
			char *newKey = strdup(key);

			if(!newVal || !newKey) {
				return -1;
				free(newVal);
				free(newKey);
			}


			entry->key = newKey;
			entry->value = newVal;

			table->count++;

			return walking_index;
		}
	}

	return -2;
}
