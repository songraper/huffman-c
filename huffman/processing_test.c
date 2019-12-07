#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <stddef.h>
#include "huffman_2.h"

int main()
{
  padding_0_test();
  number_0_add_test();
  convert_binary_test();
  split_string_test();
  processing_bin_str_test();
  return 0;
}

void padding_0_test()
{
  char *s_1 = "101010100111100110";

  char *temp_1 = malloc(30 * sizeof(char));

  char *result_temp_1 = "101010100111100110000000";

  padding_0(s_1, temp_1, 18);

  for (int i = 0; i < 24; i++)
  {
    if (temp_1[i] != result_temp_1[i])
    {
      printf("Wrong\n");
    }
    else
    {
      // printf("right\n");
    }
  }

  char *s_2 = "01001";
  char *temp_2 = malloc(9 * sizeof(char));

  char *result_temp_2 = "01001000";

  padding_0(s_2, temp_2, 5);

  for (int i = 0; i < 8; i++)
  {
    if (temp_2[i] != result_temp_2[i])
    {
      printf("Wrong\n");
    }
    else
    {
      // printf("right\n");
    }
  }

  char *s_3 = "10000100";
  char *temp_3 = malloc(9 * sizeof(char));

  char *result_temp_3 = "10000100";

  padding_0(s_3, temp_3, 8);

  for (int i = 0; i < 8; i++)
  {
    if (temp_3[i] != result_temp_3[i])
    {
      printf("Wrong\n");
    }
    else
    {
      // printf("right\n");
    }
  }
}

void number_0_add_test()
{

  int result_1 = 4;

  int num_1 = number_0_add(4);

  if (num_1 != result_1)
  {
    printf("Wrong\n");
  }
  else
  {
    // printf("Right\n");
  }

  int result_2 = 0;

  int num_2 = number_0_add(8);

  if (num_2 != result_2)
  {
    printf("Wrong\n");
  }
  else
  {
    // printf("Right\n");
  }

  int result_3 = 5;

  int num_3 = number_0_add(11);

  if (num_3 != result_3)
  {
    printf("Wrong\n");
  }
  else
  {
    // printf("Right\n");
  }
}

unsigned char convert_binary_test()
{
  char *eight_bit = "10101010";

  unsigned char result_1 = 170;

  unsigned char value_1 = convert_binary_to_decimal(eight_bit);

  if (value_1 != result_1)
  {
    printf("Wrong\n");
  }
  else
  {
    // printf("Right\n");
  }
}

void processing_bin_str_test()
{
  unsigned char *str_huffman = malloc(4 * sizeof(unsigned char));

  char *bin_str = "101010100111001011100";

  unsigned char *result_str_huffman = malloc(3 * sizeof(unsigned char));

  result_str_huffman[0] = 170;
  result_str_huffman[1] = 114;
  result_str_huffman[2] = 224;

  processing_bin_str(bin_str, str_huffman);

  for (int i = 0; i < 3; i++)
  {
    if (str_huffman[i] != result_str_huffman[i])
    {
      printf("wrong\n");
    }
    else
    {
      // printf("right\n");
    }
  }
}

void split_string_test()
{
  char *s = "101010";

  char *bit = malloc(4 * sizeof(char));

  char *result_bit = "1010";

  split_string(s, bit, 0, 3);

  for (int i = 0; i < 4; i++)
  {
    if (bit[i] != result_bit[i])
    {
      printf("Wrong\n");
    }
    else
    {
      printf("Right\n");
    }
  }
}
