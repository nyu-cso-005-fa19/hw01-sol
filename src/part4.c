#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "part4.h"

// Your task: implement functions set_zip, set_first_name, and compare_addresses

// Free the heap-allocated strings owned by the address structure pointed
// to by addr.
void free_address(struct address* addr) {
  free(addr->first_name);
  free(addr->last_name);
  free(addr->city);
}

// Set the zip field of the address structure pointed to by addr
// to the new_zip value passed in as argument.  The address structure
// is defined in the part4.h header file.
void set_zip(struct address* addr, int new_zip) {
  // Replace the following with your code
  // assert(0);
  addr->zip = new_zip;
}

// Set the city field of the address structure pointed to by addr
// to the same string as new_city. To that end, allocate a new string
// on the heap that can hold new_city and then make a copy of new_city.
//
// Hint: you can use strcpy(..) to copy a NULL-terminated C string and
// strlen(..) to get the length of a C string.
// Type "man strcpy" respectively "man strlen" to learn how to use these.
void set_city(struct address* addr, char* new_city) {
  // Replace the following with your code
  // assert(0);
  free(addr->city);
  size_t s = strlen(new_city);
  addr->city = malloc((s + 1) * sizeof(char));
  strcpy(addr->city, new_city);
}

// Compare two addresses lexicographically by name. That is,
// compare_addresses should return a negative integer if the last_name of
// addr1 is smaller than last_name of addr2, or they are equal and the
// first_name of addr1 is smaller than the first_name of addr2. If both
// last_name and first_name are equal, compare_addresses should return 0.
// In all other cases, it should return a positive value.
//
// Hint: you can use strcmp(..) to compare two NULL-terminated C strings
// type "man strcmp" to learn how to use it.
int compare_addresses(struct address* addr1, struct address* addr2) {
  // Replace the following with your code
  // assert(0);
  // return 0;
  int cmp_last = strcmp(addr1->last_name, addr2->last_name);
  if (cmp_last == 0) {
    return strcmp(addr1->first_name, addr2->first_name);
  } else {
    return cmp_last;
  }
}
