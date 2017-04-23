#include "map.h"
#include "stb.h"

#include <string.h>

typedef const char const_char;
struct _map
{
	const_char** 	keys;
	void** 			values;
};

struct _map_it
{
  map* map;
  int index;
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
	  int i;
		for(i = 0; i < sbcount(map_p->keys); ++i)
		{
			if(strcmp(map_p->keys[i], key) == 0)
			{
				return map_p->values[i];
			}
		}
	}
	return 0;
}

map_it* MapFind(map* map_p, const char* key)
{
  if(map_p)
  {
    int i;
    for(i = 0; i < sbcount(map_p->keys); ++i)
      if(strcmp(key, map_p->keys[i]) == 0)
      {
	map_it* it = malloc(sizeof(map_it));
	it->map = map_p;
	it->index = i;
	return it;
      }
  }
  return 0;
}

void* MapReplace(map_it* it, void* value)
{
  if(it && it->map && sbcount(it->map->keys) > it->index)
  {
    void* old = it->map->values[it->index];
    it->map->values[it->index] = value;
    return old;
  }
  return 0;
}

void MapFindFree(map_it* it)
{
  if(it)
    free(it);
}

void MapRemove(map_it* it)
{
}

map_it* MapForEach(map* map, map_it* it)
{
}
