#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <stddef.h>
#include <locale.h>
#include "decompress.h"

int main(int argc, char const *argv[])
{
  setlocale(LC_CTYPE, "vi_VN.UTF8");

  read_and_decompress();

  return 0;
}
