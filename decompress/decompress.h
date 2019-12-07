#ifndef DEF_DECOMPRESS
#define DEF_DECOMPRESS

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

struct binary_tree
{
  int freq;
  wchar_t chr;
  int left;
  int right;
};

typedef struct tree tree;
typedef struct character_frequency character_frequency;
typedef struct binary_tree binary_tree;

void read_and_decompress();
void decompress(int length_str_huffman, int number_of_characters, int number_0_add, unsigned char *str_huffman, binary_tree *result_tree);
void convert_decimal_to_binary(unsigned char chr, char *result);
void decode_huffman(binary_tree *root, char *real_bin, wchar_t *str, binary_tree *result);

void convert_decimal_test();

#endif
