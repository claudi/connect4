#include "table.h"

unsigned getIndex(const Table *table, Key key) {
    Key mirrored = mirrorKey(key);
    if(mirrored > key) {
        key = mirrored;
    }
    return key % table->size;
}

const Entry *findEntry(const Table *table, const Key key) {
    unsigned index = getIndex(table, key);

    if(table->entry[index].key == key) {
        return table->entry + index;
    } else {
        return NULL;
    }
}

void printEntry(const Entry entry) {
    printf("%llx\t%ld\n", (unsigned long long) entry.key, entry.heuristic);
}

void printTable(const Table *table) {
    for(unsigned long iter = 0; iter < table->size; iter++) {
        printf("%lu\t", iter);
        printEntry(table->entry[iter]);
    }
}

void addEntry(Table *table, const Entry entry) {
    unsigned index = getIndex(table, entry.key);

    table->entry[index].key = entry.key;
    table->entry[index].heuristic = entry.heuristic;
}

void resetTable(Table *table) {
    for(unsigned iter = 0; iter < table->size; iter++) {
        table->entry[iter].key = (Key) 0;
    }
}

Table *tables;
void initTables(void) {
    tables = (Table *) malloc(sizeof(Table));
    tables->size = TABLE_SIZE;
    tables->entry = (Entry *) malloc(TABLE_SIZE * sizeof(Entry));
    resetTable(tables);
}

void freeTables(void) {
    free(tables->entry);
    free(tables);
}

