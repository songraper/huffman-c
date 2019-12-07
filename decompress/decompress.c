#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stddef.h>
#include "decompress.h"

void read_and_decompress()
{
  int length_str_huffman = 0;
  int number_of_characters = 0;
  int number_0_add = 0;

  FILE *bin_file = NULL;
  bin_file = fopen("bin.dat", "rb");

  fread(&length_str_huffman, sizeof(int), 1, bin_file);

  unsigned char *str_huffman = malloc(length_str_huffman * sizeof(unsigned char));

  for (int i = 0; i < length_str_huffman; i++)
  {
    fread(&str_huffman[i], sizeof(unsigned char), 1, bin_file);
  }

  fread(&number_0_add, sizeof(int), 1, bin_file);
  fread(&number_of_characters, sizeof(int), 1, bin_file);

  binary_tree *result_tree = malloc((2 * number_of_characters - 1) * sizeof(binary_tree));

  int i = 0;

  while (!feof(bin_file))
  {
    fread(&result_tree[i], sizeof(binary_tree), 1, bin_file);
    i++;
  }

  decompress(length_str_huffman, number_of_characters, number_0_add, str_huffman, result_tree);
}

void decompress(int length_str_huffman, int number_of_characters, int number_0_add, unsigned char *str_huffman, binary_tree *result_tree)
{

  FILE *text_file = NULL;
  text_file = fopen("text_file.txt", "wb");

  char *bin_string = malloc(8000 * sizeof(char));
  char *real_bin_string = malloc((8000) * sizeof(unsigned char));
  char *temp_8bit = malloc(9 * sizeof(char));
  wchar_t *str = malloc(1000 * sizeof(wchar_t));
  unsigned char *real_str = malloc(4000 * sizeof(unsigned char));
  int k = 0, j = 0;
  binary_tree *x = malloc(sizeof(binary_tree));

  x->freq = result_tree[0].freq;
  x->chr = result_tree[0].chr;
  x->left = result_tree[0].left;
  x->right = result_tree[0].right;

  for (int i = 0; i < length_str_huffman; i++)
  {
    int h = 0;

    convert_decimal_to_binary(str_huffman[i], temp_8bit);
    while (temp_8bit[h] != '\0')
    {
      bin_string[k] = temp_8bit[h];
      k++;
      h++;
      if (k == 1000)
      {
        bin_string[k] = '\0';

        decode_huffman(result_tree, bin_string, str, x);

        wint_t a = wcslen(str);
        size_t len = wcstombs(real_str, str, 4000 * sizeof(unsigned char));

        for (wint_t i = 0; i < len; i++)
        {
          fwrite(&real_str[i], sizeof(unsigned char), 1, text_file);
        }
        k = 0;
      }
    }
  }
  bin_string[k] = '\0';

  int y = strlen(bin_string);

  for (int i = 0; i < y - number_0_add; i++)
  {
    real_bin_string[i] = bin_string[i];
  }
  real_bin_string[y - number_0_add] = '\0';

  decode_huffman(result_tree, real_bin_string, str, x);
  size_t len = wcstombs(real_str, str, 4000 * sizeof(unsigned char));

  for (wint_t i = 0; i < len; i++)
  {
    fwrite(&real_str[i], sizeof(unsigned char), 1, text_file);
  }

  fclose(text_file);
}

void convert_decimal_to_binary(unsigned char chr, char *result)
{
  int i = 7;

  while (i >= 0)
  {
    if (chr % 2 == 0)
    {
      result[i] = '0';
    }
    else
    {
      result[i] = '1';
    }

    chr = chr / 2;
    i--;
  }

  result[8] = '\0';
}

void decode_huffman(binary_tree *root, char *real_bin, wchar_t *str, binary_tree *result)
{

  int j = 0;
  int n = strlen(real_bin);

  for (int i = 0; i < n; i++)
  {
    if (real_bin[i] == '0')
    {
      int l = result->left;
      result->freq = root[l].freq;
      result->chr = root[l].chr;
      result->left = root[l].left;
      result->right = root[l].right;
    }

    else if (real_bin[i] == '1')
    {
      int r = result->right;
      result->freq = root[r].freq;
      result->chr = root[r].chr;
      result->left = root[r].left;
      result->right = root[r].right;
    }

    if (result->chr != '\0')
    {
      str[j] = result->chr;
      result->freq = root[0].freq;
      result->chr = root[0].chr;
      result->left = root[0].left;
      result->right = root[0].right;
      j++;
    }
  }
  str[j] = '\0';
}
