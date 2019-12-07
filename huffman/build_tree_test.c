#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <stddef.h>
#include <locale.h>
#include "huffman_2.h"

int main()
{
  setlocale(LC_CTYPE, "vi_VN.UTF8");

  build_tree_test_case_1();
  build_tree_test_case_2();
  build_tree_test_case_3();
  build_tree_test_case_4();
  return 0;
}

void build_tree_test_case_1()
{
  binary_tree *tree = malloc(7 * sizeof(binary_tree));

  character_frequency *character_frequency_list = malloc(4 * sizeof(character_frequency));

  character_frequency_list[0].character = 'a';
  character_frequency_list[0].frequency = 1;
  character_frequency_list[1].character = 'b';
  character_frequency_list[1].frequency = 1;
  character_frequency_list[2].character = 'c';
  character_frequency_list[2].frequency = 1;
  character_frequency_list[3].character = '\n';
  character_frequency_list[3].frequency = 1;

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

  tree = build_bin_tree(4, character_frequency_list);

  for (int i = 0; i < 7; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %c --> %c    %d --> %d    %d ==> %d   %d ==> %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("Right\n");
    }
  }
}

void build_tree_test_case_2()
{
  binary_tree *tree = malloc(3 * sizeof(binary_tree));

  character_frequency *character_frequency_list = malloc(2 * sizeof(character_frequency));

  character_frequency_list[0].character = 'a';
  character_frequency_list[0].frequency = 101;
  character_frequency_list[1].character = '\n';
  character_frequency_list[1].frequency = 1;

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

  tree = build_bin_tree(2, character_frequency_list);

  for (int i = 0; i < 3; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %lc --> %lc    %d --> %d    %d ==> %d   %d ==> %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("Right\n");
    }
  }
}

void build_tree_test_case_3()
{
  binary_tree *tree = malloc(13 * sizeof(binary_tree));

  wchar_t *str = L"ế ểệrb\n";

  int fre[] = {1, 2, 1, 1, 13, 1, 1};

  character_frequency *character_frequency_list = malloc(7 * sizeof(character_frequency));

  for (int i = 0; i < 7; i++)
  {
    character_frequency_list[i].character = str[i];
    character_frequency_list[i].frequency = fre[i];
  }

  binary_tree *result_tree = malloc(13 * sizeof(binary_tree));

  wchar_t *character = L"\0\0r\0\0\n\0\0 ệbếể";
  int freq[] = {20, 7, 13, 3, 4, 1, 2, 2, 2, 1, 1, 1, 1};
  int left[] = {1, 3, 0, 5, 7, 0, 9, 11, 0, 0, 0, 0, 0};
  int right[] = {2, 4, 0, 6, 8, 0, 10, 12, 0, 0, 0, 0, 0};

  for (int i = 0; i < 13; i++)
  {
    result_tree[i].chr = character[i];
    result_tree[i].freq = freq[i];
    result_tree[i].left = left[i];
    result_tree[i].right = right[i];
  }

  tree = build_bin_tree(7, character_frequency_list);

  for (int i = 0; i < 13; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %c --> %c    %d --> %d    %d ==> %d   %d ==> %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("Right\n");
    }
  }
}

void build_tree_test_case_4()
{
  binary_tree *tree = malloc(17 * sizeof(binary_tree));

  wchar_t *str = L"ow xy\nuv1";

  int fre[] = {1, 1, 1, 14, 4, 3, 2, 1, 1};

  character_frequency *character_frequency_list = malloc(9 * sizeof(character_frequency));

  for (int i = 0; i < 9; i++)
  {
    character_frequency_list[i].character = str[i];
    character_frequency_list[i].frequency = fre[i];
  }

  binary_tree *result_tree = malloc(17 * sizeof(binary_tree));

  wchar_t *character = L"\0\0x\0\0\0\n\0y1\0\0u vow";
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

  tree = build_bin_tree(9, character_frequency_list);

  for (int i = 0; i < 17; i++)
  {
    if (tree[i].chr != result_tree[i].chr || tree[i].freq != result_tree[i].freq || tree[i].left != result_tree[i].left || tree[i].right != result_tree[i].right)
    {
      printf("Wrong: %c --> %c    %d --> %d    %d ==> %d   %d ==> %d\n", tree[i].chr, result_tree[i].chr, tree[i].freq, result_tree[i].freq, tree[i].left, result_tree[i].left, tree[i].right, result_tree[i].right);
    }
    else
    {
      printf("Right\n");
    }
  }
}
