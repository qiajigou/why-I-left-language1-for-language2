#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>

#include "tmp.h"

char *read_template(char* template_path)
{
  char *buf = NULL;
  size_t size = 0;

  FILE *fp = fopen(template_path, "r");

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);

  rewind(fp);

  buf = calloc(1, size + 1);

  if( !buf ) {
    fclose(fp);
    fputs("memory alloc fails", stderr);
    exit(1);
  }

  if( 1!=fread( buf , size, 1 , fp) ) {
    fclose(fp);
    free(buf);
    fputs("entire read fails", stderr);
    exit(1);
  }

  fclose(fp);

  return buf;
}

char *strtolower(char *s)
{
  char *d = (char *)malloc(strlen(s+1));
  int i = 0;
  for(i = 0; s[i]; i++){
    d[i] = tolower(s[i]);
  }
  d[i] = '\0';
  return d;
}

char *firstofchararry(char *s)
{
  char *c = (char *)malloc(2);
  int i = 0;
  for(i=0; i<1; i++){
    c[i] = tolower(s[i]);
  }
  c[1] = '\0';
  return c;
}

int compare(char *language, char* language_file)
{
  char *lan = strtolower(language);
  char *lf = strtolower(language_file);
  lf = strtok(lf, ".");

  int cpr = -1;
  int r = 0;
  if ( lan && lf)
  {
    cpr = strcmp(lan, lf);
  }
  if ( cpr == 0 )
  {
    r = 1;
  }
  free(lan);
  free(lf);
  return r;
}

char *search_by_language(char *language, char* hello_folder_path)
{
  char *c = firstofchararry(language);
  char *folder = hello_folder_path;
  char *e = "/\0";
  char *fd = NULL;
  int folder_size = strlen(folder);
  int e_size = strlen(e);
  int c_size = strlen(c);
  char *lf = malloc(folder_size + e_size + c_size + 1);

  strcpy(lf, folder);
  strcat(lf, c);
  strcat(lf, e);

  DIR *dp;
  struct dirent *ep;

  dp = opendir(lf);

  if ( dp != NULL )
  {
    int condition = 1;

    while ( condition || fd )
    {
      ep = readdir(dp);

      if (!ep) {
        condition = 0;
        break;
      }
      int cpr = compare(language, ep->d_name);
      if ( cpr )
      {
        fd = ep->d_name;
        break;
      }

    }
    (void) closedir(dp);
  }

  char *fp = NULL;

  if ( fd )
  {
    fp = malloc(strlen(lf) + strlen(fd) + 1);
    strcpy(fp, lf);
    strcat(fp, fd);
  }

  free(c);
  return fp;
}

char *read_helloworld(char *language, char* hello_folder_path)
{
  char *path = search_by_language(language, hello_folder_path);
  char *hello = NULL;
  if (path)
  {
    hello = read_template(path);
  }
  else
  {
    printf("path is null!\n");
  }
  free(path);
  return hello;
}
