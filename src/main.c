#include <stdio.h>
#include <assert.h>
#include "kv.h"

int main() {
	kv_t *table = kv_init(16);
	assert(NULL != table);
	assert(16 == table->capacity);
	assert(0 == table->count);
	
	kv_put(table, "key", "value");
	kv_put(table, "key", "value1");
	kv_put(table, "key2", "value2");

	for(int i = 0; i < table->capacity; i++) {
		if(!(table->entries[i].key)) {
			continue;
		}

		printf("KEY: %s", table->entries[i].key);
		printf("VALUE: %s\n", table->entries[i].value);
	}

	kv_free(table);
}
