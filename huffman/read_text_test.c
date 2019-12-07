#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <stddef.h>
#include "huffman_2.h"

int main()
{
  setlocale(LC_CTYPE, "vi_VN.UTF8");

  read_text_test();
  count_frequency_test();

  return 0;
}

void read_text_test()
{
  FILE *test = NULL;
  test = fopen("text_file_test.txt", "r");

  wint_t current_char = 0;
  wchar_t *str = malloc(13 * sizeof(wchar_t));
  wchar_t result_str[] = L"abcdefghiklm";

  read_text(str, &current_char, test);
  fclose(test);

  for (int i = 0; i < 12; i++)
  {
    if (str[i] != result_str[i])
    {
      printf("Wrong\n");
    }
  }
}

void count_frequency_test()
{

  wchar_t str[7] = {'b', 'a', 'c', 'a', 'c', 'a'};
  character_frequency *character_frequency_list = malloc(3 * sizeof(character_frequency));
  for (int i = 0; i < 3; i++)
  {
    character_frequency_list[i].character = '\0';
    character_frequency_list[i].frequency = 0;
  }
  character_frequency *result_character_frequency_list = malloc(3 * sizeof(character_frequency));

  result_character_frequency_list[0].character = 'b';
  result_character_frequency_list[0].frequency = 1;
  result_character_frequency_list[1].character = 'a';
  result_character_frequency_list[1].frequency = 3;
  result_character_frequency_list[2].character = 'c';
  result_character_frequency_list[2].frequency = 2;

  count_frequency(str, character_frequency_list);

  for (int i = 0; i < 3; i++)
  {
    if (character_frequency_list[i].character != result_character_frequency_list[i].character)
    {
      printf("wrong\n");
    }

    if (character_frequency_list[i].frequency != result_character_frequency_list[i].frequency)
    {
      printf("wrong\n");
    }
  }
}
