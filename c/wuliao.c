#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/stat.h>

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
  printf("-w\t%s\n", "-w=hello-world folder path");
  printf("-h\t%s\n", "-> Show this help");
  printf("\n");
  printf("%s\n", "Example: ./wuliao -1=Java -2=Python -3=Python3 -t=templates/en/justno.md");
  printf(":)\n");
}

int check_path(char *path)
{
  struct stat s;
  int err = stat(path, &s);
  if(-1 == err) {
    return 1;
  }
  return 0;
}

char *get_config_path(char* path_name, char *path)
{
  int err = check_path(path);
  int len = strlen(path);
  char *HOME = getenv("HOME");
  int home_len = strlen(HOME);
  char *real_path;
  char *slash = "/.wuliao/";
  int slash_len = strlen(slash);

  if ( err )
  {
    int total_size = len + home_len + slash_len + 1;
    real_path = (char *)malloc(total_size);
    strcpy(real_path, HOME);
    strcat(real_path, slash);
    strcat(real_path, path);
    real_path[total_size - 1] = '\0';
  }
  else
  {
    real_path = (char *)malloc(len + 1);
    strcpy(real_path, path);
    real_path[len + 1] = '\0';
  }

  return real_path;
}

int main(int argc, char *argv[]) {
  dict *d = dict_create();

  int c;

  char *lan0 = "C";
  char *lan1 = "Java";
  char *lan2 = "Python";
  char *lan3 = "Python3";
  char *template_path = "templates/en/article.md";
  char *hello_folder_path = "hello-world";
  char *lan1_projects = "Spring MVC, Tomcat";

  while ((c = getopt (argc, argv, "0:1:2:3:t:p:o:w:h")) != -1)
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
        break;
      case 'w':
        hello_folder_path = optarg;
        break;
      case 'h':
        show_help();
        return 0;
        break;
      default:
        break;
    }
  }

  char * real_hello_path = get_config_path("hello-world", hello_folder_path);
  int prr = check_path(real_hello_path);

  if ( prr )
  {
    printf("hello-world template path=%s unavaliable\n", real_hello_path);
    return 1;
  }

  char *real_template_path = get_config_path("template", template_path);
  prr = check_path(real_template_path);

  if ( prr )
  {
    printf("template path=%s unavaliable\n", real_template_path);
    return 1;
  }

  char *template = read_template(real_template_path);
  int err = check_block_is_open(template);

  if ( err )
  {
    printf("ERR: template in %s is invalid, maybe lost { or }?\n",
      real_template_path);
    return 1;
  }

  dict_insert(d, "language0", lan0);
  dict_insert(d, "language1", lan1);
  dict_insert(d, "language2", lan2);
  dict_insert(d, "language3", lan3);

  dict_insert(d, "project_names", lan1_projects);

  char *lan1_hello = read_helloworld(lan1, real_hello_path);
  char *lan2_hello = read_helloworld(lan2, real_hello_path);

  dict_insert(d, "language1_hello_world", lan1_hello);
  dict_insert(d, "language2_hello_world", lan2_hello);

  char *replaced = replace(template, d);

  printf("%s\n", replaced);

  free(replaced);
  free(real_hello_path);
  free(real_template_path);
  dict_destory(d);
  return 0;
}
