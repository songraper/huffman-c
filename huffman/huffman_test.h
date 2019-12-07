
#ifndef DEF_HUFFMAN
#define DEF_HUFFMAN

struct tree
{
  int fre;
  wchar_t c;
  struct tree *left;
  struct tree *right;
};

struct character_frequency
{
  int frequency;
  wchar_t character;
  struct tree *add;
};

struct character_01_string
{
  char *str;
  wchar_t ch;
};

struct binary_tree
{
  int freq;
  wchar_t chr;
  int left;
  int right;
};

typedef struct tree tree;
typedef struct character_frequency character_frequency;
typedef struct character_01_string character_01_string;
typedef struct binary_tree binary_tree;

void read_text(wchar_t *str, wint_t *current_char, FILE *text_file);
wint_t check_alike(wchar_t *str, character_frequency *character_frequency_list, int i);
void count_frequency(wchar_t *str, character_frequency *character_frequency_list);
void read_and_count_test();
int read_count_case_1(character_frequency *character_frequency_list);
int read_count_case_2(character_frequency *character_frequency_list);
int read_count_case_3(character_frequency *character_frequency_list);
int read_count_case_4(character_frequency *character_frequency_list);
int read_count_case_5(character_frequency *character_frequency_list);

void compress_test_case_1();
void compress_test_case_2();
void processing_and_compressing_test_1(struct character_01_string *encoding_table, int number_of_characters, character_frequency *character_frequency_list, unsigned char *str_huffman);
void processing_and_compressing_test_2(struct character_01_string *encoding_table, int number_of_characters, character_frequency *character_frequency_list, unsigned char *str_huffman);
void process_binary_and_compress(char *binary_string, wchar_t *string, struct character_01_string *encoding_table, int n, unsigned char *str_huffman, int *length, int *num_0, int *k, FILE *bin_file);
void save_to_binfile(int num_0, int number_of_characters, binary_tree *resul_tree, FILE *bin_file);
void padding_0(char *s, char *temp, int n);
void split_string(char *temp, char *blank, int a, int b);
unsigned char pow_n(int x, int y);
unsigned char convert_binary_to_decimal(char *blank);
int number_0_add(int x);
void processing_bin_str(char *s, unsigned char *str_huffman);
unsigned int num_0(unsigned char *s, int m);
tree **init_queue(int *front, int *rear, int m);
void push(tree **queue, int *rear, tree *new_node);
tree *pop(tree **queue, int *front);
binary_tree *create_array_tree(tree *root, int m, int *k);

#endif
