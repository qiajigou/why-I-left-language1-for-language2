#include <stdio.h>

#include "dict.h"
#include "fs.h"
#include "format.h"


int main(int argc, char *argv[]) {
  dict *d = dict_create();
  char *template_path = "templates/en/article.md";
  char *template = read_template(template_path);

  char *lan1 = "Python";
  char *lan2 = "Java";

  dict_insert(d, "language0", "C");
  dict_insert(d, "language1", lan1);
  dict_insert(d, "language2", lan2);
  dict_insert(d, "language3", "GO");

  dict_insert(d, "project_names", "tornado Flask");

  char *lan1_hello = read_helloworld(lan1);
  char *lan2_hello = read_helloworld(lan2);

  dict_insert(d, "language1_hello_world", lan1_hello);
  dict_insert(d, "language2_hello_world", lan2_hello);

  char *replaced = replace(template, d);

  printf("%s\n", replaced);

  dict_destory(d);
  return 0;
}
