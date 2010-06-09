/*
 * Copyright (c) 2008 Martin Decky
 * All rights reserved.
 *
 * Distributed under the terms of GPL.
 *
 */

#include <stddef.h>
#include <assert.h>

#include "list.h"


/** Initialize a list
 *
 * @param list The list to initialize.
 *
 */
void list_init(list_t *list)
{
	list->head = NULL;
	list->tail = NULL;
}


/** Initialize an item
 *
 * @param item The item to initialize.
 *
 */
void item_init(item_t *item)
{
	item->list = NULL;
}


/** Append an item to a list
 *
 * @param list The list to append to.
 * @param item The item to append.
 *
 */
void list_append(list_t *list, item_t *item)
{
	/* Make sure the item is not a member of a list, then add it. */
	assert(item->list == NULL);
	item->list = list;
	
	/* In an empty list, attach us as head.
	   Otherwise, attach us to current tail. */
	if (list->tail == NULL)
		list->head = item;
	else
		list->tail->next = item;
	
	/* Our previous item is current tail.
	   We obviously have no next item. */
	item->prev = list->tail;
	item->next = NULL;
	
	/* We are the new tail. */
	list->tail = item;
}


/** Remove an item from a list
 *
 * @param list The list to remove from.
 * @param item The item to remove.
 *
 */
void list_remove (list_t *list, item_t *item)
{
	/* Make sure the item is a member of the list, then remove it. */
	assert(item->list == list);
	item->list = NULL;
	
	if (item->prev == NULL)
		/* If we are list head, our next item is the new head.
		   This works even if we happen to be the tail too. */
		list->head = item->next;
	else
		/* Otherwise, just make our previous
		   item point to our next item. */
		item->prev->next = item->next;
	
	/* The same for the other end of the list. */
	if (item->next == NULL)
		list->tail = item->prev;
	else
		item->next->prev = item->prev;
}

/** Rotate the list by making its head into its tail
*
* @param list The list to rotate.
*
* @return The rotated item.
*
*/
item_t *list_rotate (list_t *list)
{
	/* 
 	 * Simply remove and append current list head.
 	 * Not most efficient but working nonetheless.
 	 */

	item_t *item = list->head;
	list_remove(list, item);
	list_append(list, item);
	return item;
} 
