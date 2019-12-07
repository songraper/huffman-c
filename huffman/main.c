#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <stddef.h>
#include "huffman.h"

int main(int argc, char const *argv[])
{
  setlocale(LC_CTYPE, "vi_VN.UTF8");
  character_frequency *character_frequency_list = malloc(500 * sizeof(character_frequency));

  char *file = "file_text.txt";

  int number_of_characters = read_and_count(character_frequency_list, file);

  binary_tree *result_tree = build_bin_tree(number_of_characters, character_frequency_list);

  character_01_string *encoding_table = malloc(number_of_characters * sizeof(character_01_string));
  create_encode_table(number_of_characters, character_frequency_list, encoding_table);

  processing_and_compressing(encoding_table, number_of_characters, result_tree, file);

  return 0;
}
