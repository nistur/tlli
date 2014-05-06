#ifndef __UTIL_MAP_H__
#define __UTIL_MAP_H__

typedef struct _map map;

map* InitMap();
void TerminateMap(map** map_p);

void MapAdd(map* map_p, const char* key, void* value);
void* MapGet(map* map_p, const char* key);

#endif/*__UTIL_MAP_H__*/