#ifndef TABLE_GUARD
#define TABLE_GUARD
#include "defs.h"
#include "key.h"

#define T_BUFFER 10000000

typedef struct {
    Key key;
    long heuristic;
} Entry;

typedef struct {
    unsigned long size;
    Entry *entry;
} Table;

extern Table *tables;

void printEntry(const Entry entry);
void printTable(const Table *table);
void addEntry(Table *table, const Entry entry);
const Entry *findEntry(const Table *table, const Key key);
void resetTable(Table *table);
void initTables(void);
void freeTables(void);

#endif // TABLE_GUARD

