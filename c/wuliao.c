#include <stdio.h>
#include <getopt.h>

#include "dict.h"
#include "fs.h"
#include "format.h"


int main(int argc, char *argv[]) {
  dict *d = dict_create();

  int c;

  char *lan0 = "C";
  char *lan1 = "Python";
  char *lan2 = "Java";
  char *lan3 = "GO";
  char *template_path = "templates/en/article.md";
  char *lan1_projects = "tornado Flask";
  char *output = NULL;

  while ((c = getopt (argc, argv, "0:1:2:3:t:p:o")) != -1)
  {
    switch (c)
    {
      case '0':
        lan0 = optarg;
        break;
      case '1':
        lan1 = optarg;
        break;
      case '2':
        lan2 = optarg;
        break;
      case '3':
        lan3 = optarg;
        break;
      case 't':
        template_path = optarg;
        break;
      case 'p':
        lan1_projects = optarg;
        break;
      case 'o':
        output = optarg;
        break;
      default:
        break;
    }
  }

  char *template = read_template(template_path);

  dict_insert(d, "language0", lan0);
  dict_insert(d, "language1", lan1);
  dict_insert(d, "language2", lan2);
  dict_insert(d, "language3", lan3);

  dict_insert(d, "project_names", lan1_projects);

  char *lan1_hello = read_helloworld(lan1);
  char *lan2_hello = read_helloworld(lan2);

  dict_insert(d, "language1_hello_world", lan1_hello);
  dict_insert(d, "language2_hello_world", lan2_hello);

  char *replaced = replace(template, d);

  printf("%s\n", replaced);

  dict_destory(d);
  return 0;
}
