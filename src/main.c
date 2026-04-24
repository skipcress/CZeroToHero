#include <stdio.h>
#include <assert.h>
#include "kv.h"

int main() {
	kv_t *table = kv_init(16);
	assert(NULL != table);
	assert(16 == table->capacity);
	assert(0 == table->count);
	kv_free(table);
}
