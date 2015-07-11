#ifndef __UTIL_MAP_H__
#define __UTIL_MAP_H__

typedef struct _map map;
typedef struct _map_it map_it;

map* InitMap();
void TerminateMap(map** map_p);

void MapAdd(map* map_p, const char* key, void* value);
void* MapGet(map* map_p, const char* key);
map_it* MapFind(map* map_p, const char* key);
void* MapReplace(map_it* it, void* value);
void MapFindFree(map_it* it);

#endif/*__UTIL_MAP_H__*/
