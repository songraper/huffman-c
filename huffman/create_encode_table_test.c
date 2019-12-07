#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <stddef.h>
#include "huffman_2.h"

int main()
{
  setlocale(LC_CTYPE, "vi_VN.UTF8");

  sort_test();
  encode_table_case_1();
  encode_table_case_2();
  encode_table_case_3();
  encode_table_case_4();

  return 0;
}

void sort_test()
{
  character_frequency *character_frequency_list = malloc(5 * sizeof(character_frequency));

  character_frequency_list[0].character = 'a';
  character_frequency_list[0].frequency = 12;
  character_frequency_list[1].character = 'b';
  character_frequency_list[1].frequency = 5;
  character_frequency_list[2].character = 'c';
  character_frequency_list[2].frequency = 6;
  character_frequency_list[3].character = 'd';
  character_frequency_list[3].frequency = 100;
  character_frequency_list[4].character = 'e';
  character_frequency_list[4].frequency = 0;

  character_frequency *result_character_frequency_list = malloc(5 * sizeof(character_frequency));

  result_character_frequency_list[0].character = 'e';
  result_character_frequency_list[0].frequency = 0;
  result_character_frequency_list[1].character = 'b';
  result_character_frequency_list[1].frequency = 5;
  result_character_frequency_list[2].character = 'c';
  result_character_frequency_list[2].frequency = 6;
  result_character_frequency_list[3].character = 'a';
  result_character_frequency_list[3].frequency = 12;
  result_character_frequency_list[4].character = 'd';
  result_character_frequency_list[4].frequency = 100;

  sort(character_frequency_list, 5);

  for (int i = 0; i < 5; i++)
  {
    if (character_frequency_list[i].character != result_character_frequency_list[i].character)
    {
      printf("Wrong\n");
    }

    if (character_frequency_list[i].frequency != result_character_frequency_list[i].frequency)
    {
      printf("Wrong\n");
    }
  }
}

void encode_table_case_1()
{
  character_01_string *encoding_table = malloc(4 * sizeof(character_01_string));

  for (int i = 0; i < 4; i++)
  {
    encoding_table[i].ch = '\0';
    encoding_table[i].str = malloc(4 * sizeof(char));
  }

  character_frequency *character_frequency_list = malloc(4 * sizeof(character_frequency));

  character_frequency_list[0].character = 'd';
  character_frequency_list[0].frequency = 1;
  character_frequency_list[1].character = 'a';
  character_frequency_list[1].frequency = 2;
  character_frequency_list[2].character = 'b';
  character_frequency_list[2].frequency = 2;
  character_frequency_list[3].character = 'c';
  character_frequency_list[3].frequency = 3;

  character_01_string *result_encoding_table = malloc(4 * sizeof(character_01_string));

  result_encoding_table[0].ch = 'c';
  result_encoding_table[0].str = "0";
  result_encoding_table[1].ch = 'b';
  result_encoding_table[1].str = "10";
  result_encoding_table[2].ch = 'd';
  result_encoding_table[2].str = "110";
  result_encoding_table[3].ch = 'a';
  result_encoding_table[3].str = "111";

  build_bin_tree(4, character_frequency_list);
  create_encode_table(4, character_frequency_list, encoding_table);

  int j = 0;
  for (int i = 0; i < 4; i++)
  {
    if (encoding_table[i].ch != result_encoding_table[i].ch)
    {
      printf("Wrong : %lc <-- %lc\n", encoding_table[i].ch, result_encoding_table[i].ch);
    }
    while (encoding_table[i].str[j] != '\0')
    {
      if (encoding_table[i].str[j] != result_encoding_table[i].str[j])
      {
        printf("wrong\n");
      }

      else
      {
        printf("Right\n");
      }

      j++;
    }

    j = 0;
  }
}

void encode_table_case_2()
{
  character_01_string *encoding_table = malloc(2 * sizeof(character_01_string));

  for (int i = 0; i < 2; i++)
  {
    encoding_table[i].ch = '\0';
    encoding_table[i].str = malloc(2 * sizeof(char));
  }

  character_frequency *character_frequency_list = malloc(2 * sizeof(character_frequency));

  character_frequency_list[0].character = 'd';
  character_frequency_list[0].frequency = 1;
  character_frequency_list[1].character = 'b';
  character_frequency_list[1].frequency = 1;

  character_01_string *result_encoding_table = malloc(2 * sizeof(character_01_string));

  result_encoding_table[0].ch = 'd';
  result_encoding_table[0].str = "0";
  result_encoding_table[1].ch = 'b';
  result_encoding_table[1].str = "1";

  build_bin_tree(2, character_frequency_list);
  create_encode_table(2, character_frequency_list, encoding_table);

  int j = 0;
  for (int i = 0; i < 2; i++)
  {
    if (encoding_table[i].ch != result_encoding_table[i].ch)
    {
      printf("Wrong :%lc <-- %lc\n", encoding_table[i].ch, result_encoding_table[i].ch);
    }
    while (encoding_table[i].str[j] != '\0')
    {
      if (encoding_table[i].str[j] != result_encoding_table[i].str[j])
      {
        printf("wrong\n");
      }
      else
      {
        printf("right\n");
      }

      j++;
    }
    j = 0;
  }
}

void encode_table_case_3()
{
  character_01_string *encoding_table = malloc(6 * sizeof(character_01_string));

  for (int i = 0; i < 6; i++)
  {
    encoding_table[i].ch = '\0';
    encoding_table[i].str = malloc(6 * sizeof(char));
  }

  character_frequency *character_frequency_list = malloc(6 * sizeof(character_frequency));

  character_frequency_list[0].character = L'â';
  character_frequency_list[0].frequency = 1;
  character_frequency_list[1].character = 'n';
  character_frequency_list[1].frequency = 1;
  character_frequency_list[2].character = 'g';
  character_frequency_list[2].frequency = 1;
  character_frequency_list[3].character = L'ơ';
  character_frequency_list[3].frequency = 2;
  character_frequency_list[4].character = L'ạ';
  character_frequency_list[4].frequency = 2;
  character_frequency_list[5].character = L'ế';
  character_frequency_list[5].frequency = 3;

  character_01_string *result_encoding_table = malloc(6 * sizeof(character_01_string));

  result_encoding_table[0].ch = L'ơ';
  result_encoding_table[0].str = "00";
  result_encoding_table[1].ch = L'ạ';
  result_encoding_table[1].str = "01";
  result_encoding_table[2].ch = 'g';
  result_encoding_table[2].str = "100";
  result_encoding_table[3].ch = L'â';
  result_encoding_table[3].str = "1010";
  result_encoding_table[4].ch = 'n';
  result_encoding_table[4].str = "1011";
  result_encoding_table[5].ch = L'ế';
  result_encoding_table[5].str = "11";

  build_bin_tree(6, character_frequency_list);
  create_encode_table(6, character_frequency_list, encoding_table);

  int j = 0;
  for (int i = 0; i < 6; i++)
  {
    if (encoding_table[i].ch != result_encoding_table[i].ch)
    {
      printf("Wrong: %lc <-- %lc\n", encoding_table[i].ch, result_encoding_table[i].ch);
    }
    while (encoding_table[i].str[j] != '\0')
    {
      if (encoding_table[i].str[j] != result_encoding_table[i].str[j])
      {
        printf("wrong\n");
      }

      else
      {
        printf("Right\n");
      }

      j++;
    }

    j = 0;
  }
}

void encode_table_case_4()
{
  character_01_string *encoding_table = malloc(9 * sizeof(character_01_string));

  for (int i = 0; i < 9; i++)
  {
    encoding_table[i].ch = '\0';
    encoding_table[i].str = malloc(6 * sizeof(char));
  }

  wchar_t *str = L"ow xy\nuv1";

  int fre[] = {1, 1, 1, 14, 4, 3, 2, 1, 1};

  character_frequency *character_frequency_list = malloc(9 * sizeof(character_frequency));

  for (int i = 0; i < 9; i++)
  {
    character_frequency_list[i].character = str[i];
    character_frequency_list[i].frequency = fre[i];
  }

  character_01_string *result_encoding_table = malloc(9 * sizeof(character_01_string));

  result_encoding_table[0].ch = '1';
  result_encoding_table[0].str = "0000";
  result_encoding_table[1].ch = ' ';
  result_encoding_table[1].str = "00010";
  result_encoding_table[2].ch = 'v';
  result_encoding_table[2].str = "00011";
  result_encoding_table[3].ch = '\n';
  result_encoding_table[3].str = "001";
  result_encoding_table[4].ch = 'o';
  result_encoding_table[4].str = "01000";
  result_encoding_table[5].ch = 'w';
  result_encoding_table[5].str = "01001";
  result_encoding_table[6].ch = 'u';
  result_encoding_table[6].str = "0101";
  result_encoding_table[7].ch = 'y';
  result_encoding_table[7].str = "011";
  result_encoding_table[8].ch = 'x';
  result_encoding_table[8].str = "1";

  build_bin_tree(9, character_frequency_list);
  create_encode_table(9, character_frequency_list, encoding_table);

  int j = 0;
  for (int i = 0; i < 9; i++)
  {
    if (encoding_table[i].ch != result_encoding_table[i].ch)
    {
      printf("Wrong: %lc <-- %lc\n", encoding_table[i].ch, result_encoding_table[i].ch);
    }
    while (encoding_table[i].str[j] != '\0')
    {
      if (encoding_table[i].str[j] != result_encoding_table[i].str[j])
      {
        printf("wrong\n");
      }

      else
      {
        printf("Right\n");
      }

      j++;
    }

    j = 0;
  }
}
