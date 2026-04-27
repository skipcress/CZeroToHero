#include <stdio.h>
#include <assert.h>
#include "kv.h"

int main() {
	kv_t *table = kv_init(16);
	assert(NULL != table);
	assert(16 == table->capacity);
	assert(0 == table->count);
	
	printf("%d\n", kv_put(table, "key", "value"));
	printf("%d\n", kv_put(table, "key", "value1"));
	printf("%d\n", kv_put(table, "key2", "value2"));
}
