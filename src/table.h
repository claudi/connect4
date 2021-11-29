#ifndef TABLE_GUARD
#define TABLE_GUARD
#include "defs.h"
#include "key.h"

#define TABLE_SIZE 10000000

typedef struct {
    Key key;
    long heuristic;
} Entry;

typedef struct {
    unsigned long size;
    Entry *entry;
} Table;

extern Table *tables;

void addEntry(Table *table, const Entry entry);
const Entry *findEntry(const Table *table, const Key key);
void resetTable(Table *table);

#endif // TABLE_GUARD
