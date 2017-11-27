# SLang documentation

*This is a work in progress.*

## Interface Documentation


#### The format for header files shall be as follows:

##### Object Libraries

This files shall contain the specification of the object in the following order:

(neccessary libraries will be included at the top)

PURPOSE: Why this object library must exist

DATA: A description of the data contained in the object

INTERFACE: The object function prefix and any information about the interface that is important to the user
  The function prefix identifies both the prefix of interface functions (uppercase and general)
  and the parameter representing the instance object handle  being passed to an interface function (lowercase and instance-specific)

  __Function identifier syntax__
  *[Object Prefix]_[Operation Type]_[Operation Descriptor](Object handle, params...)*

  Operation types:
  - init: create a new instance, returns a pointer to a new instance of the object
  - edit: modify contents of the data, returns void
  - get : see the data contained in the object, returns a value
  - free: free all memory allocated to the object, returns void
  - do  : Perform an internal operation within the object, returns void

  In the implementations, the void pointer handle  passed to a function is converted to a pointer to the 
  proper struct type called "self" for internal reference using a macro "CAST"

CONSTANT DEFINITIONS: The definitions of any constants that may be revelant to the object

HANDLE DECLERATION: The decleration of a handle used to identify instances of the library object

INTERFACE DECLERATIONS: The decleration of interface functions and accompanying documentation

#### Utility Libraries

(neccessary libraries will be included at the top)

PURPOSE: Why this library must exist

INDEX: A description of each function or other included item and it's purpose

  __Function identifier syntax__
  *[Library Prefix]_[Operation Type]_[Operation Descriptor](params...)*

  Operation types:
  - do  : Perform an operation, returns void
  - get : Get a value, returns a value

CONSTANT DEFINITIONS: The definitions of any constants that may be revelant to the library

DECLERATIONS: The decleration of interface functions and other items and accompanying documentation

===

Disclaimer: This software is provided "AS IS" and with no warranty of any kind so don't send me an angry email when a program that processes text files eats your core os libraries and demmands bitcoins. It won't do that.

(c) 2017 Mercury Built International All Rights Reserved
