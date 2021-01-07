#include "table.h"

void printEntry(const Entry *entry) {
    printf("%llx\t%ld\n", (unsigned long long) entry->key, entry->heuristic);
}

void printTable(const Table *table) {
    for(short iter = 0; iter < table->size; iter++) {
        printEntry(table->entry);
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

