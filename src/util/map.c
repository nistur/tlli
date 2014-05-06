#include "map.h"
#include "stb.h"

#include <string.h>

typedef const char const_char;
struct _map
{
	const_char** 	keys;
	void** 			values;
};

map* InitMap()
{
	map* m = malloc(sizeof(map));
	m->keys = 0;
	m->values = 0;
	return m;
}

void TerminateMap(map** map_p)
{
	if(map_p && *map_p)
	{
		sbfree((*map_p)->keys);
		sbfree((*map_p)->values);
		free(*map_p);
	}
	*map_p = 0;
}

void MapAdd(map* map_p, const char* key, void* value)
{
	if(map_p)
	{
		sbpush(map_p->keys, key);
		sbpush(map_p->values, value);
	}
}

void* MapGet(map* map_p, const char* key)
{
	if(map_p)
	{
		for(int i = 0; i < sbcount(map_p->keys); ++i)
		{
			if(strcmp(map_p->keys[i], key) == 0)
			{
				return map_p->values[i];
			}
		}
	}
	return 0;
}