#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <stddef.h>
#include "huffman.h"

int read_and_count(character_frequency *character_frequency_list, char *file)
{

  FILE *text_file = fopen(file, "r");

  int number_of_characters = 0;

  wint_t current_char = 0;
  wchar_t *str = malloc(1000000 * sizeof(wchar_t));
  for (int h = 0; h < 500; h++)
  {
    character_frequency_list[h].root_address = NULL;
    character_frequency_list[h].frequency = 0;
    character_frequency_list[h].character = '\0';
  }

  while (current_char != WEOF)
  {
    read_text(str, &current_char, text_file);
    count_frequency(str, character_frequency_list);
  }

  while (character_frequency_list[number_of_characters].frequency != 0)
  {
    number_of_characters++;
  }

  free(str);

  fclose(text_file);

  return number_of_characters;
}

binary_tree *build_bin_tree(int number_of_characters, character_frequency *character_frequency_list)
{

  for (int j = 0; j < number_of_characters - 1; j++)
  {
    sort(character_frequency_list, number_of_characters);

    character_frequency_list[j + 1].root_address = build_tree(character_frequency_list[j], character_frequency_list[j + 1]);
    character_frequency_list[j + 1].frequency += character_frequency_list[j].frequency;
    character_frequency_list[j + 1].character = '\0';
  }

  binary_tree *array_tree = malloc((2 * number_of_characters - 1) * 5 * sizeof(binary_tree));
  int g = 0;
  array_tree = create_array_tree(character_frequency_list[number_of_characters - 1].root_address, number_of_characters, g);

  return array_tree;
}

void create_encode_table(int number_of_characters, character_frequency *character_frequency_list, character_01_string *encoding_table)
{

  int k = 0;

  char *temp_bit = malloc(50 * sizeof(char));

  set_01_for_char(character_frequency_list[number_of_characters - 1].root_address, 0, temp_bit, encoding_table, &k);
}

void processing_and_compressing(struct character_01_string *encoding_table, int number_of_characters, binary_tree *result_tree, char *file)
{
  char *binary_string = malloc(8000 * sizeof(char));
  unsigned char *str_huffman = malloc(1000 * sizeof(unsigned char));
  int length_str_huffman = 0, num_0 = 0, h = 0;
  wint_t s = 0;

  wint_t current_char = 0;
  wchar_t *str = malloc(1000000 * sizeof(wchar_t));
  FILE *bin_file = NULL;
  FILE *text_file = fopen(file, "r");

  bin_file = fopen("bin.dat", "wb+");

  while (current_char != WEOF)
  {
    read_text(str, &current_char, text_file);

    s = wcslen(str);

    process_binary_and_compress(binary_string, str, encoding_table, s, str_huffman, &length_str_huffman, &num_0, &h, bin_file);
  }

  binary_string[h] = '\0';

  num_0 = number_0_add(strlen(binary_string));


  length_str_huffman += ((strlen(binary_string) + num_0) / 8);


  rewind(bin_file);

  fwrite(&length_str_huffman, sizeof(int), 1, bin_file);
  fseek(bin_file, 0, SEEK_END);

  processing_bin_str(binary_string, str_huffman);

  for (int a = 0; a < ((strlen(binary_string) + num_0) / 8); a++)
  {
    fwrite(&str_huffman[a], sizeof(unsigned char), 1, bin_file);

  }

  fclose(text_file);

  save_to_binfile(num_0, number_of_characters, result_tree, bin_file);

  fclose(bin_file);
}

void save_to_binfile(int num_0, int number_of_characters, binary_tree *result_tree, FILE *bin_file)
{

  fwrite(&num_0, sizeof(int), 1, bin_file);

  fwrite(&number_of_characters, sizeof(int), 1, bin_file);

  for (int i = 0; i < ((2 * number_of_characters) - 1); i++)
  {
    fwrite(&result_tree[i], sizeof(binary_tree), 1, bin_file);
  }
}

void read_text(wchar_t *str, wint_t *current_char, FILE *text_file)
{
  wint_t n = 0;
  while (n != 1000000)
  {
    if (*current_char != WEOF)
    {
      *current_char = fgetwc(text_file);
      str[n] = *current_char;
      n++;
    }
    else
    {
      str[n - 1] = '\0';
      break;
    }
  }
  
  str[n] = '\0';
}

wint_t check_alike(wchar_t *str, character_frequency *character_frequency_list, int i)
{
  int j = 0;
  int k = character_frequency_list[j].frequency;

  while (k != 0)
  {
    k = character_frequency_list[j].frequency;
    if (str[i] == character_frequency_list[j].character)
    {
      return j;
    }
    j++;
  }

  return -1;
}

void count_frequency(wchar_t *str, character_frequency *character_frequency_list)
{
  wint_t j = 0;
  wint_t n = wcslen(str);
  for (wint_t i = 0; i < n; i++)
  {
    if (check_alike(str, character_frequency_list, i) == -1)
    {
      character_frequency_list[j].character = str[i];
      character_frequency_list[j].frequency = 1;
      character_frequency_list[j].root_address = NULL;
      j++;
    }
    else
    {
      wint_t p = check_alike(str, character_frequency_list, i);
      character_frequency_list[p].frequency += 1;
    }
  }
}

void sort(character_frequency *character_frequency_list, int counter)
{
  character_frequency *temp = malloc(sizeof(character_frequency));

  for (int i = 0; i < counter - 1; i++)
  {
    for (int j = i + 1; j < counter; j++)
    {
      if (character_frequency_list[i].frequency > character_frequency_list[j].frequency)
      {

        temp->root_address = character_frequency_list[i].root_address;
        temp->character = character_frequency_list[i].character;
        temp->frequency = character_frequency_list[i].frequency;
        character_frequency_list[i].root_address = character_frequency_list[j].root_address;
        character_frequency_list[i].character = character_frequency_list[j].character;
        character_frequency_list[i].frequency = character_frequency_list[j].frequency;
        character_frequency_list[j].root_address = temp->root_address;
        character_frequency_list[j].character = temp->character;
        character_frequency_list[j].frequency = temp->frequency;
      }
    }
  }
  free(temp);
}

tree *build_tree(character_frequency num_input1, character_frequency num_input2)
{
  tree *left_node;
  tree *right_node;
  tree *root = malloc(sizeof(tree));

  if (num_input1.root_address == NULL)
  {
    left_node = malloc(sizeof(tree));
    left_node->fre = num_input1.frequency;
    left_node->c = num_input1.character;
    left_node->left = NULL;
    left_node->right = NULL;
  }
  else

  {
    left_node = num_input1.root_address;
  }

  if (num_input2.root_address == NULL)
  {
    right_node = malloc(sizeof(tree));
    right_node->fre = num_input2.frequency;
    right_node->c = num_input2.character;
    right_node->left = NULL;
    right_node->right = NULL;
  }
  else
  {
    right_node = num_input2.root_address;
  }

  root->fre = num_input1.frequency + num_input2.frequency;
  root->c = '\0';
  root->left = left_node;
  root->right = right_node;

  return root;
}

void set_01_for_char(struct tree *root, int node, char *temp_bit, struct character_01_string *encoding_table, int *i)
{
  node++;
  if (root != NULL)
  {
    temp_bit[node - 1] = '0';
    set_01_for_char(root->left, node, temp_bit, encoding_table, i);
    temp_bit[node - 1] = '\0';

    temp_bit[node - 1] = '1';
    set_01_for_char(root->right, node, temp_bit, encoding_table, i);
    temp_bit[node - 1] = '\0';

    if (root->c != '\0')
    {
      encoding_table[*i].ch = root->c;
      int x = strlen(temp_bit);
      encoding_table[*i].str = malloc(x * sizeof(char));
      strcpy(encoding_table[*i].str, temp_bit);
      *i += 1;
    }
  }
  node--;
}

void process_binary_and_compress(char *binary_string, wchar_t *string, struct character_01_string *encoding_table, int n, unsigned char *str_huffman, int *length_str_huffman, int *num_0, int *k, FILE *bin_file)
{
  wint_t t = 0;

  while (t < n)
  {
    wint_t j = 0, h = 0;
    while (string[t] != encoding_table[j].ch)
    {
      j++;
    }
    while (encoding_table[j].str[h] != '\0')
    {
      binary_string[*k] = encoding_table[j].str[h];
      *k += 1;
      h += 1;

      if (*k == 8000)
      {
        binary_string[*k] = '\0';
        processing_bin_str(binary_string, str_huffman);
        *length_str_huffman += 1000;

        rewind(bin_file);

        fwrite(length_str_huffman, sizeof(int), 1, bin_file);

        fseek(bin_file, 0, SEEK_END);

        for (int a = 0; a < 1000; a++)
        {
          fwrite(&str_huffman[a], sizeof(unsigned char), 1, bin_file);
        }
        *k = 0;
      }
    }

    t += 1;
  }
}

void padding_0(char *s, char *temp, int n)
{
  if (n % 8 == 0)
  {
    strcpy(temp, s);
  }
  else
  {
    for (int i = 0; i < n; i++)
    {
      temp[i] = s[i];
    }
    for (int i = n; i < n + (8 - (n % 8)); i++)
    {
      temp[i] = '0';
    }

    temp[n + (8 - (n % 8))] = '\0';
  }
}

int number_0_add(int x)
{
  if (x % 8 == 0)
  {
    return 0;
  }
  else
  {
    int i = 0;
    i = 8 - (x % 8);

    return i;
  }
}

void split_string(char *temp, char *eight_bit, int a, int b)
{
  int k = 0;

  for (int i = a; i <= b; i++)
  {
    eight_bit[k] = temp[i];
    k++;
  }

  eight_bit[k] = '\0';
}

unsigned char pow_n(int x, int y)
{
  unsigned char p = 1;

  if (y == 0)
  {
    p = 1;
  }
  else
  {
    for (int i = 1; i <= y; i++)
    {
      p *= x;
    }
  }

  return p;
}
unsigned char convert_binary_to_decimal(char *eight_bit)
{
  unsigned char value = 0;

  for (int i = 0; i < 8; i++)
  {
    if (eight_bit[i] == '1')
    {
      value += pow_n(2, (7 - i));
    }
  }

  return value;
}

void processing_bin_str(char *s, unsigned char *str_huffman)
{
  char *temp_bin = malloc(8000 * sizeof(char));

  int n = strlen(s);
  char *eight_bit = malloc(9 * sizeof(char));

  padding_0(s, temp_bin, n);

  int a = 0, b = 7;
  int m = strlen(temp_bin);
  int loop = m / 8;

  for (int i = 0; i < loop; i++)
  {
    split_string(temp_bin, eight_bit, a, b);
    str_huffman[i] = convert_binary_to_decimal(eight_bit);

    a += 8;
    b += 8;
  }
  str_huffman[loop] = '\0';
}

tree **init_queue(int *front, int *rear, int m)
{
  tree **queue = malloc((2 * m - 1) * sizeof(tree *));
  *front = *rear = 0;
  return queue;
}

void push(tree **queue, int *rear, tree *new_node)
{
  queue[*rear] = new_node;

  queue[*rear]->fre = new_node->fre;
  queue[*rear]->c = new_node->c;
  queue[*rear]->left = new_node->left;
  queue[*rear]->right = new_node->right;

  (*rear)++;
}

tree *pop(tree **queue, int *front)
{
  (*front)++;

  return queue[*front - 1];
}

binary_tree *create_array_tree(tree *root, int m, int k)
{
  binary_tree *bin_tree = malloc((2 * m - 1) * 5 * sizeof(binary_tree));

  int front = 0;
  int rear = 0;

  k = 0;

  tree **save = malloc((2 * m - 1) * sizeof(tree *));

  tree **queue = init_queue(&front, &rear, m);

  tree *temp_node = root;

  temp_node->fre = root->fre;
  temp_node->c = root->c;
  temp_node->left = root->left;
  temp_node->right = root->right;

  while (temp_node != NULL)
  {
    save[k] = temp_node;

    save[k]->fre = temp_node->fre;
    save[k]->c = temp_node->c;
    save[k]->left = temp_node->left;
    save[k]->right = temp_node->right;

    if (temp_node->left != NULL)
    {
      push(queue, &rear, temp_node->left);
    }
    if (temp_node->right != NULL)
    {
      push(queue, &rear, temp_node->right);
    }

    temp_node = pop(queue, &front);

    k++;
  }

  int j = 0;

  for (int i = 0; i < (2 * m - 1); i++)
  {

    bin_tree[i].freq = save[i]->fre;
    bin_tree[i].chr = save[i]->c;
    bin_tree[i].left = j + 1;
    bin_tree[i].right = j + 2;

    if (save[i]->c != '\0')
    {
      bin_tree[i].left = 0;
      bin_tree[i].right = 0;
      j -= 2;
    }

    j += 2;
  }

  return bin_tree;
}
