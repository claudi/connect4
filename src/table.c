#include "table.h"


void printEntry(const Entry entry) {
    printf("%llx\t%ld\n", (unsigned long long) entry.key, entry.heuristic);
}

void printTable(const Table *table) {
    ASSERT(table->size < T_BUFFER);
    for(short iter = 0; iter < table->size; iter++) {
        printf("%d\t", iter);
        printEntry(table->entry[iter]);
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

