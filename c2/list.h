#ifndef LIST_H
#define LIST_H "list.h"

/*
 * Speficication for List object
 *
 * [PURPOSE]
 *
 * This library provides an abstract data structure called a "list" which is essentially an
 * ordered group of objects of an arbitrary type. The aim of this data structure is to
 * provide a framework for performing operations on groups of objects common to any arbitrary
 * group of objects, no matter the type
 *
 * [DATA]
 *
 * The object data is primarily stored as an array of object pointers.
 *
 * [INTERFACE]
 *
 * Object Prefix: [List] (List object type) 
 *
 * */

// [CONSTANT DEFINITIONS]
//
// None yet but I'm sure there will be some
//

// [HANDLE DECLERATION]
typedef void* List;

// For generic object (at least temporarily)
typedef void* Object;

// [INTERFACE DECLERATIONS]

// (_init_ operations)

// Create an empty list
List List_init_default(void);

// (_free_ operations)

// Free all memory associated with the list
void List_free(List list);

// (_edit_ operations)

// Add an object to the end of a list
void List_edit_append(List list, Object obj);

// Insert an object at a certain index
void List_edit_insert(List list, Object obj, int index);

// Remove all items in a list while keeping the memory allocated
void List_edit_delete(List list);
 
// Delete items in a list within a certain index range
void List_edit_deleteRange(List list, int iBegin, int iEnd);

// Reverse the order of the items in the list
void List_edit_reverse(List list);

// (_get_ operations)

// Get the first object in a list
Object List_get_first(List list);

// Get the last object in a list
Object List_get_last(List list);

//get the object in the list an a given index
Object List_get_index(List list, int index);

// (_do_ operations)

// Print the entire list
void List_do_print(List list);

//TODO write the rest and also implemet the entire thing


#endif
