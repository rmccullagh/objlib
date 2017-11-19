#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <float.h>

#include "map.h"
#include "string.h"
#include "long.h"

#define key_type_valid(key) \
	!((!como_type_is(key, como_string_type) \
		&& !como_type_is(key, como_long_type))) 

COMO_OBJECT_API como_object *como_map_new(como_size_t size)
{
	como_map *map = malloc(sizeof(*map));
	como_size_t i;
	map->base.type = &como_map_type;
	map->base.next = NULL;

	map->capacity = size;
	map->size = 0;

	map->buckets = malloc(sizeof(como_map_bucket*) * size);

	for(i = 0; i < size; i++)
		map->buckets[i] = NULL;

	return (como_object *)map;
}

static void do_resize(como_map *map)
{
	/* FUCK */
}

static void maybe_resize(como_map *map)
{
	if(map->size >= map->capacity)
		do_resize(map);
}

COMO_OBJECT_API como_object *como_map_put(como_object *obj, 
	como_object *key, como_object *value)
{
	/* Only ints, and strings are allowed as keys */
	if(!como_type_is(key, como_string_type) && 
		!como_type_is(key, como_long_type)) {

		return NULL;
	}

	como_map *map 	   = (como_map *)obj;

	maybe_resize(map);

	como_size_t hashed = key->type->hash(key);
	como_size_t index  = hashed % map->capacity;
	como_map_bucket *bucket = map->buckets[index];

	/* Check to see if this key already exists */
	while(bucket != NULL) {
		como_map_bucket *next = bucket->next;
		como_object *thiskey   = bucket->key;

		if(thiskey->type->equals(thiskey, key)) {
			bucket->value = value;
			goto done;
		}

		bucket = next;
	}

	bucket = malloc(sizeof(*bucket));
	bucket->key = key;
	bucket->value = value;
	bucket->next = map->buckets[index];

	map->buckets[index] = bucket;
	map->size++;

done:
	return value;
}


COMO_OBJECT_API como_object *como_map_get(como_object *obj, como_object *key)
{
	como_map *map = (como_map *)obj;

	if(!key_type_valid(key))
		return NULL;

	como_size_t hashed = key->type->hash(key);
	como_size_t index  = hashed % map->capacity;
	como_map_bucket *bucket = map->buckets[index];

	/* Check to see if this key already exists */
	while(bucket != NULL) {
		como_map_bucket *next = bucket->next;
		como_object *thiskey   = bucket->key;

		if(thiskey->type->equals(thiskey, key)) {
				return bucket->value;
		}

		bucket = next;
	}

	return NULL;
}


COMO_OBJECT_API como_object *como_map_delete(como_object *obj, como_object *key)
{
	como_map *map = (como_map *)obj;

	if(!key_type_valid(key))
		return NULL;

	como_size_t hashed = key->type->hash(key);
	como_size_t index  = hashed % map->capacity;
	como_map_bucket *bucket = map->buckets[index];
	como_map_bucket *prev = NULL;
	como_map_bucket *first = map->buckets[index];;

	while(bucket != NULL) {
		como_map_bucket *next = bucket->next;
		como_object *thiskey   = bucket->key;

		if(thiskey->type->equals(thiskey, key)) {
			if(prev) {
				prev->next = bucket->next;
				free(bucket);
			}
			else {
				map->buckets[index] = NULL;
				free(first);
			}

			map->size--;
			return key;
		}

		bucket = next;
		prev = bucket;
	}


	return NULL;
}



static void map_dtor(como_object *ob)
{
	como_map *map = (como_map *)ob;
	como_size_t i;

	for(i = 0; i < map->capacity; i++) {
		como_map_bucket *bucket = map->buckets[i];

		if(bucket) 
			while(bucket != NULL) {
				como_map_bucket *next = bucket->next;
				/* we don't free keys, or values, */
				free(bucket);
				bucket = next;
			}
	}

	free(map->buckets);
	free(map);
}

como_type como_map_type = {
	"map",
	NULL,
	map_dtor,
	NULL,
	NULL,
	NULL
};















