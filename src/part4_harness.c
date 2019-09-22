#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>

#include "panic_cond.h"
#include "harness.h"
#include "part4.h"  

void set_str_field(char** field, char* new_str) {
  size_t s = strlen(new_str);
  *field = malloc((s + 1) * sizeof(char));
  strcpy(*field, new_str);
}

void init_address(struct address* addr, char* first_name, char* last_name, char* city, int zip) {
  set_str_field(&(addr->first_name), first_name);
  set_str_field(&(addr->last_name), last_name);
  set_str_field(&(addr->city), city);
  addr->zip = zip;
}

void test_set_zip(struct address* addr, int new_zip) {
  int old_zip = addr->zip;
  set_zip(addr, new_zip);

  panic_cond(addr->zip == new_zip,
             "test set_zip with\naddr:\n"
             " { first_name: Jane,\n"
             "   last_name: Doe,\n"
             "   city: New York,\n"
             "   zip: %d\n"
             " }\n"
             "expected new value %d for zip, actually %d\n",
             old_zip, new_zip, addr->zip);
}

int compare_addresses_gold(struct address* addr1, struct address* addr2) {
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

void test_set_city(struct address* addr, char* city) {
  char* old_city;
  size_t s = strlen(addr->city);
  size_t new_s = strlen(city);
  old_city = malloc((s + 1) * sizeof(char));
  strcpy(old_city, addr->city);

  char* before_city = addr->city;
  set_city(addr, city);

  panic_cond(strcmp(addr->city, city) == 0,
             "test set_city with\n"
             " addr:\n"
             " { first_name: %s,\n"
             "   last_name: %s,\n"
             "   city: %s,\n"
             "   zip: %d\n"
             " }\n"
             " new_city: %s\n"
             " expected city to be set to %s, actual %s",
             addr->first_name, addr->last_name, old_city, addr->zip,
             city, city, addr->city);
  
  panic_cond(addr->city != city,
             "test new_city with\n"
             " addr:\n"
             " { first_name: %s,\n"
             "   last_name: %s,\n"
             "   city: %s,\n"
             "   zip: %d\n"
             " }\n"
             " new_city: %s\n"
             " expected input string to be copied but it wasn't",
             addr->first_name, addr->last_name, old_city, addr->zip);

  free(old_city);
}

void test_compare_address(struct address* addr1, struct address* addr2) {
  int cmp_gold = compare_addresses_gold(addr1, addr2);
  int cmp = compare_addresses(addr1, addr2);

  int cond = cmp_gold > 0 ? cmp > 0 : cmp_gold < 0 ? cmp < 0 : cmp == 0;
  char* exp = cmp_gold > 0 ? "> 0" : cmp_gold < 0 ? "< 0" : "== 0";
  panic_cond(cond,
             "test compare_addresses with\n"
             " addr1:\n"
             " { first_name: %s,\n"
             "   last_name: %s,\n"
             "   city: %s,\n"
             "   zip: %d\n"
             " }\n"
             " addr2:\n"
             " { first_name: %s,\n"
             "   last_name: %s,\n"
             "   city: %s,\n"
             "   zip: %d\n"
             " }\n"
             "expected value %s, actually %d\n",
             addr1->first_name, addr1->last_name, addr1->city, addr1->zip,
             addr2->first_name, addr2->last_name, addr2->city, addr2->zip,
             exp, cmp);
  
}

int main(int argc, char** argv)
{
  struct address jane;
  init_address(&jane, "Jane", "Doe", "New York", 10011);

  struct address jane_bo;
  init_address(&jane_bo, "Jane", "Bo", "New York", 10011);

  struct address john;
  init_address(&john, "John", "Doe", "New York", 10011);

  printf("part4: testing set_zip...\n");
  for (int i = 10012; i < 10020; i++) {
    test_set_zip(&jane, i);
  }
  printf("part4: set_zip OK\n");

  printf("part4: testing set_city...\n");
  test_set_city(&jane, "Philadelphia");
  test_set_city(&jane, "Boston");
  printf("part4: set_city OK\n");
  
  printf("part4: testing compare_addresses...\n");
  test_compare_address(&john, &jane);
  test_compare_address(&jane, &john);
  test_compare_address(&jane, &jane);
  test_compare_address(&jane_bo, &jane);
  test_compare_address(&jane, &jane_bo);
  test_compare_address(&john, &jane_bo);
  test_compare_address(&jane_bo, &john);  
  test_compare_address(&jane, &jane);
  printf("part4: compare_addresses OK\n");

  free_address(&jane);
  free_address(&jane_bo);
  free_address(&john);
  
  return 0;
}
