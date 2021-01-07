#ifndef TABLE_GUARD
#define TABLE_GUARD
#include "defs.h"
#include "key.h"

#define T_BUFFER 1024

typedef struct {
    Key key;
    long heuristic;
} Entry;

typedef struct {
    unsigned short size;
    Entry entry[T_BUFFER];
} Table;

extern Table *tables;

void printEntry(const Entry entry);
void printTable(const Table *table);
void initTables(void);
void freeTables(void);

#endif // TABLE_GUARD

