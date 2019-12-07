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
  struct tree *root_address;
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

int read_and_count(character_frequency *character_frequency_list, char *file);
binary_tree *build_bin_tree(int number_of_characters, character_frequency *character_frequency_list);
void create_encode_table(int number_of_characters, character_frequency *character_frequency_list, character_01_string *encoding_table);
void processing_and_compressing(struct character_01_string *encoding_table, int number_of_characters, binary_tree *result_tree, char *file);
void save_to_binfile(int num_0, int number_of_characters, binary_tree *result_tree, FILE *bin_file);
wint_t check_alike(wchar_t *str, character_frequency *character_frequency_list, int i);
void read_text(wchar_t *str, wint_t *current_char, FILE *text_file);
void count_frequency(wchar_t *str, character_frequency *character_frequency_list);
void sort(character_frequency *character_frequency_list, int counter);
tree *build_tree(character_frequency num_input1, character_frequency num_input2);
void set_01_for_char(struct tree *root, int node, char *temp_bit, struct character_01_string *encoding_table, int *i);
void process_binary_and_compress(char *binary_string, wchar_t *string, struct character_01_string *encoding_table, int n, unsigned char *str_huffman, int *length_str_huffman, int *num_0, int *k, FILE *bin_file);
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
binary_tree *create_array_tree(tree *root, int m, int k);

void read_and_count_test();

void read_text_test();

void count_frequency_test();

void build_tree_test_case_1();
void build_tree_test_case_2();
void build_tree_test_case_3();
void build_tree_test_case_4();

void encode_table_case_1();
void encode_table_case_2();
void encode_table_case_3();
void encode_table_case_4();

void compress_test_case_1();
void compress_test_case_2();
void compress_test_case_3();

void sort_test();
void padding_0_test();
void number_0_add_test();
void split_string_test();
unsigned char pow_test();
unsigned char convert_binary_test();
void processing_bin_str_test();

#endif
