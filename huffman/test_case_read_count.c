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
  read_and_count_test();
}

void read_and_count_test()
{
  character_frequency *character_frequency_list = malloc(500 * sizeof(character_frequency));
  int result_1 = 4;
  int result_2 = 2;
  int result_3 = 0;
  int result_4 = 17;
  int result_5 = 9;

  int num_1 = read_and_count(character_frequency_list, "test.txt");

  if (num_1 != result_1)
  {
    printf("Wrong\n");
  }
  else
  {
    printf("Right\n");
  }

  FILE *test_2 = NULL;

  int num_2 = read_and_count(character_frequency_list, "test2.txt");

  if (num_2 != result_2)
  {
    printf("Wrong\n");
  }
  else
  {
    printf("Right\n");
  }

  int num_3 = read_and_count(character_frequency_list, "test3.txt");

  if (num_3 != result_3)
  {
    printf("Wrong\n");
  }
  else
  {
    printf("Right\n");
  }

  int num_4 = read_and_count(character_frequency_list, "test4.txt");

  if (num_4 != result_4)
  {
    printf("Wrong\n");
  }
  else
  {
    printf("Right\n");
  }
}
