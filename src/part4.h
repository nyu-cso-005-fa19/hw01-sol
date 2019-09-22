#pragma once

// struct type holding address information
// The members first_name, last_name, street, and city are
// pointers to heap-allocated strings which are "owned" by the
// address struct. If the a value of type struct address is no longer used
// (e.g. it goes out of scope) then the heap-allocated strings must be explicitly
// deallocated by calling free_address.
struct address {
  char* first_name;
  char* last_name;
  char* street;
  char* city;
  int zip;
};

void free_address(struct address* addr);

void set_zip(struct address* addr, int new_zip);

void set_city(struct address* addr, char* new_city);

int compare_addresses(struct address* addr1, struct address* addr2);
