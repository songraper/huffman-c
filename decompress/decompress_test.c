#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stddef.h>
#include "decompress.h"

int main()
{
  convert_decimal_test();
  return 0;
}

void convert_decimal_test()
{
  char *eight_bit = malloc(9 * sizeof(char));

  char *result = "10101010";

  convert_decimal_to_binary(170, eight_bit);

  for (int i = 0; i < 8; i++)
  {
    if (eight_bit[i] != result[i])
    {
      printf("Wrong\n");
    }
    else
    {
      printf("Right\n");
    }
  }

  char *eight_bit_2 = malloc(9 * sizeof(char));

  char *result_2 = "00000000";

  convert_decimal_to_binary(0, eight_bit_2);

  for (int i = 0; i < 8; i++)
  {
    if (eight_bit_2[i] != result_2[i])
    {
      printf("Wrong\n");
    }
    else
    {
      printf("right\n");
    }
  }
}
