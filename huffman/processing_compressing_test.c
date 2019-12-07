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

  compress_test_case_1();
  compress_test_case_2();
  compress_test_case_3();

  return 0;
}

void compress_test_case_1()
{
  character_01_string *encoding_table = malloc(4 * sizeof(character_01_string));

  encoding_table[0].ch = 'c';
  encoding_table[0].str = "00";
  encoding_table[1].ch = '\n';
  encoding_table[1].str = "01";
  encoding_table[2].ch = 'a';
  encoding_table[2].str = "10";
  encoding_table[3].ch = 'b';
  encoding_table[3].str = "11";

  binary_tree *result_tree = malloc(7 * sizeof(binary_tree));

  result_tree[0].chr = '\0';
  result_tree[0].freq = 4;
  result_tree[0].left = 1;
  result_tree[0].right = 2;
  result_tree[1].chr = '\0';
  result_tree[1].freq = 2;
  result_tree[1].left = 3;
  result_tree[1].right = 4;
  result_tree[2].chr = '\0';
  result_tree[2].freq = 2;
  result_tree[2].left = 5;
  result_tree[2].right = 6;
  result_tree[3].chr = 'c';
  result_tree[3].freq = 1;
  result_tree[3].left = 0;
  result_tree[3].right = 0;
  result_tree[4].chr = '\n';
  result_tree[4].freq = 1;
  result_tree[4].left = 0;
  result_tree[4].right = 0;
  result_tree[5].chr = 'a';
  result_tree[5].freq = 1;
  result_tree[5].left = 0;
  result_tree[5].right = 0;
  result_tree[6].chr = 'b';
  result_tree[6].freq = 1;
  result_tree[6].left = 0;
  result_tree[6].right = 0;

  processing_and_compressing(encoding_table, 4, result_tree, "test.txt");

  int length_str_huffman = 0, result_length = 1;
  int number_of_characters = 0, result_number = 4;
  int number_0_add = 0, result_num_0 = 0;
  unsigned char *result_str_huffman = malloc(1 * sizeof(unsigned char));
  result_str_huffman[0] = 177;

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

  binary_tree *tree = malloc(7 * sizeof(binary_tree));

  int i = 0;

  while (!feof(bin_file))
  {
    fread(&tree[i], sizeof(binary_tree), 1, bin_file);
    i++;
  }

  fclose(bin_file);

  if (number_of_characters != result_number || length_str_huffman != result_length || number_0_add != result_num_0)
  {
    printf("Wrong:");
    printf("%d <-- %d\n", number_of_characters, result_number);
    printf("%d <-- %d\n", length_str_huffman, result_length);
    printf("%d <-- %d\n", number_0_add, result_num_0);
  }
  else
  {
    printf("Right\n");
  }

  for (int i = 0; i < 1; i++)
  {
    if (str_huffman[i] != result_str_huffman[i])
    {
      printf("wrong : %d <-- %d\n", str_huffman[i], result_str_huffman[i]);
    }
    else
    {
      printf("Right\n");
    }
  }

  for (int i = 0; i < 7; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %c <-- %c    %d <-- %d    %d <== %d   %d <== %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("right\n");
    }
  }
}

void compress_test_case_2()
{

  character_01_string *encoding_table = malloc(2 * sizeof(character_01_string));

  encoding_table[0].ch = '\n';
  encoding_table[0].str = "0";
  encoding_table[1].ch = 'a';
  encoding_table[1].str = "1";

  binary_tree *result_tree = malloc(3 * sizeof(binary_tree));

  result_tree[0].chr = '\0';
  result_tree[0].freq = 102;
  result_tree[0].left = 1;
  result_tree[0].right = 2;
  result_tree[1].chr = '\n';
  result_tree[1].freq = 1;
  result_tree[1].left = 0;
  result_tree[1].right = 0;
  result_tree[2].chr = 'a';
  result_tree[2].freq = 101;
  result_tree[2].left = 0;
  result_tree[2].right = 0;

  processing_and_compressing(encoding_table, 2, result_tree, "test2.txt");

  int length_str_huffman = 0, result_length = 13;
  int number_of_characters = 0, result_number = 2;
  int number_0_add = 0, result_num_0 = 2;
  unsigned char *result_str_huffman = malloc(13 * sizeof(unsigned char));
  for (int i = 0; i < 12; i++)
  {
    result_str_huffman[i] = 255;
  }
  result_str_huffman[12] = 248;

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

  binary_tree *tree = malloc(7 * sizeof(binary_tree));

  int i = 0;

  while (!feof(bin_file))
  {
    fread(&tree[i], sizeof(binary_tree), 1, bin_file);
    i++;
  }

  fclose(bin_file);

  if (number_of_characters != result_number || length_str_huffman != result_length || number_0_add != result_num_0)
  {
    printf("Wrong:");
    printf("%d <-- %d\n", number_of_characters, result_number);
    printf("%d <-- %d\n", length_str_huffman, result_length);
    printf("%d <-- %d\n", number_0_add, result_num_0);
  }
  else
  {
    printf("Right\n");
  }

  for (int i = 0; i < 12; i++)
  {
    if (str_huffman[i] != result_str_huffman[i])
    {
      printf("wrong : %d <-- %d\n", str_huffman[i], result_str_huffman[i]);
    }
    else
    {
      printf("Right\n");
    }
  }

  for (int i = 0; i < 3; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %c <-- %c    %d <-- %d    %d <== %d   %d <== %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("right\n");
    }
  }
}

void compress_test_case_3()
{
  character_01_string *encoding_table = malloc(9 * sizeof(character_01_string));

  encoding_table[0].ch = '1';
  encoding_table[0].str = "0000";
  encoding_table[1].ch = ' ';
  encoding_table[1].str = "00010";
  encoding_table[2].ch = L'ế';
  encoding_table[2].str = "00011";
  encoding_table[3].ch = '\n';
  encoding_table[3].str = "001";
  encoding_table[4].ch = L'ơ';
  encoding_table[4].str = "01000";
  encoding_table[5].ch = 'w';
  encoding_table[5].str = "01001";
  encoding_table[6].ch = 'u';
  encoding_table[6].str = "0101";
  encoding_table[7].ch = 'y';
  encoding_table[7].str = "011";
  encoding_table[8].ch = 'x';
  encoding_table[8].str = "1";

  binary_tree *result_tree = malloc(17 * sizeof(binary_tree));

  wchar_t *character = L"\0\0x\0\0\0\n\0y1\0\0u ếơw";
  int freq[] = {28, 14, 14, 6, 8, 3, 3, 4, 4, 1, 2, 2, 2, 1, 1, 1, 1};
  int left[] = {1, 3, 0, 5, 7, 9, 0, 11, 0, 0, 13, 15, 0, 0, 0, 0, 0};
  int right[] = {2, 4, 0, 6, 8, 10, 0, 12, 0, 0, 14, 16, 0, 0, 0, 0, 0};

  for (int i = 0; i < 17; i++)
  {
    result_tree[i].chr = character[i];
    result_tree[i].freq = freq[i];
    result_tree[i].left = left[i];
    result_tree[i].right = right[i];
  }

  processing_and_compressing(encoding_table, 9, result_tree, "test5.txt");

  int length_str_huffman = 0, result_length = 9;
  int number_of_characters = 0, result_number = 9;
  int number_0_add = 0, result_num_0 = 5;
  unsigned char *result_str_huffman = malloc(9 * sizeof(unsigned char));

  unsigned char value[] = {66, 69, 255, 251, 109, 149, 81, 144, 32};

  for (int i = 0; i < 9; i++)
  {
    result_str_huffman[i] = value[i];
  }

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

  binary_tree *tree = malloc(17 * sizeof(binary_tree));

  int i = 0;

  while (!feof(bin_file))
  {
    fread(&tree[i], sizeof(binary_tree), 1, bin_file);
    i++;
  }

  fclose(bin_file);

  if (number_of_characters != result_number || length_str_huffman != result_length || number_0_add != result_num_0)
  {
    printf("Wrong:");
    printf("%d <-- %d\n", number_of_characters, result_number);
    printf("%d <-- %d\n", length_str_huffman, result_length);
    printf("%d <-- %d\n", number_0_add, result_num_0);
  }
  else
  {
    printf("Right\n");
  }

  for (int i = 0; i < 9; i++)
  {
    if (str_huffman[i] != result_str_huffman[i])
    {
      printf("wrong : %d <-- %d\n", str_huffman[i], result_str_huffman[i]);
    }
    else
    {
      printf("Right\n");
    }
  }

  for (int i = 0; i < 17; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %c <-- %c    %d <-- %d    %d <== %d   %d <== %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("right\n");
    }
  }
}
