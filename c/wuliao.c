#include <stdio.h>
#include <getopt.h>

#include "dict.h"
#include "tmp.h"
#include "format.h"

void show_help()
{
  printf("%s\n", "Why I left language1 for language2");
  printf("\n");
  printf("-0\t%s\n", "-0=C -> Language that you was used bug gived up");
  printf("-1\t%s\n", "-1=Java -> Language that you used but gona leave this");
  printf("-2\t%s\n", "-2=Python -> Language that you are going to use and love this");
  printf("-3\t%s\n", "-3=Python3 -> If language2 you don't like, there still a chance");
  printf("-t\t%s\n", "-t=template_path -> Customized template path");
  printf("-p\t%s\n", "-p=Tomecat -> Project you was working on with language1");
  printf("-h\t%s\n", "-h -> Show this help");
  printf("\n");
  printf("%s\n", "Example: ./wuliao -1=Java -2=Python -3=Python3 -t=templates/en/justno.md");
  printf(":)\n");
}


int main(int argc, char *argv[]) {
  dict *d = dict_create();

  int c;

  char *lan0 = "=C";
  char *lan1 = "=Java";
  char *lan2 = "=Python";
  char *lan3 = "=Python3";
  char *template_path = "=templates/en/article.md";
  char *lan1_projects = "=Spring MVC, Tomcat";
  char *output = NULL;

  while ((c = getopt (argc, argv, "0:1:2:3:t:p:o:h")) != -1)
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
      case 'h':
        show_help();
        return 0;
        break;
      default:
        break;
    }
  }

  ++lan0;
  ++lan1;
  ++lan2;
  ++lan3;
  ++template_path;
  ++lan1_projects;
  ++output;

  char *template = read_template(template_path);
  int err = check_block_is_open(template);

  if ( err )
  {
    printf("ERR: template in %s is invalid, maybe lost { or }?\n",
      template_path);
    return 1;
  }

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

  free(replaced);
  dict_destory(d);
  return 0;
}
