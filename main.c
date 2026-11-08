#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "reader.h"
#include "string.h"
#include "bmh.h"
#include "dynarray.h"
#include "line_matcher.h"

char valid_flags[6] = "aeiou";
bool validated_flags[256] = {false};

int count_non_options(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-')
      return argc - i;
  }
  return 0;
}

int main(int argc, char** argv) {
  int opt = getopt(argc, argv, valid_flags);
  while (opt >= 0) {
    if (opt == '?') exit(1);
    validated_flags[opt] = true;
    opt = getopt(argc, argv, valid_flags);
  }
  int non_options = count_non_options(argc, argv);
  if (argc < 2 || non_options == 0) {
    fprintf(stderr, 
      "%s: The grip command needs at least one argument\n",
      argv[0]);
    exit(1);
  }
  if (non_options > 2) {
    fprintf(stderr, 
      "%s: The grip command needs at most two arguments\n",
      argv[0]);
    exit(1);
  }
  reader* r;
  char* pattern;
  if (non_options == 2) {
    pattern = argv[argc - 2];
    char* filename = argv[argc - 1];
    r = init_reader(filename);
  } else if (non_options < 2) {
    pattern = argv[argc - 1];
    r = init_reader_stdin();
  }
  int pattern_length = strlen(pattern);
  read_file(r);
  char skip_table[TABLE_SIZE];
  make_skip_table(skip_table, pattern, pattern_length);
  intDynArray* occurences = find_all_patterns(skip_table,
                                              pattern,
                                              pattern_length,
                                              r->buffer,
                                              r->length,
                                              !validated_flags['i']);
  // print_intDynArray(occurences);
  // printf("%d\n", occurences->length);
  // print_lines_from_indexes(occurences, pattern_length, r->buffer, r->length);
  printf("%s", r->buffer);
  free_intDynArray(occurences);
  free_reader(r);
  return 0;
}
