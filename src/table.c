#include "table.h"

const Entry *findEntry(const Table *table, const Key key) {
    ASSERT(table->size < T_BUFFER);

    for(unsigned long iter = 0; iter < table->size; iter++) {
        if(table->entry[iter].key == key) {
            return table->entry + iter;
        }
    }
    return NULL;
}

void printEntry(const Entry entry) {
    printf("%llx\t%ld\n", (unsigned long long) entry.key, entry.heuristic);
}

void printTable(const Table *table) {
    ASSERT(table->size <= T_BUFFER);

    for(unsigned long iter = 0; iter < table->size; iter++) {
        printf("%lu\t", iter);
        printEntry(table->entry[iter]);
    }
}

void addEntry(Table *table, const Key key, const long heuristic) {
    if(table->size < T_BUFFER) {
        if(findEntry(table, key) == NULL) {
            table->entry[table->size].key = key;
            table->entry[table->size].heuristic = heuristic;
            table->size += 1;
        }
    }
}

Table *tables;
void initTables(void) {
    tables = (Table *) malloc(sizeof(Table));
    tables->size = 0;
}

void freeTables(void) {
    free(tables);
}

