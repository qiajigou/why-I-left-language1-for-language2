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

  if( 1 != fread( buf , size, 1 , fp) ) {
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
  char *d = (char *)malloc(strlen(s) * sizeof(char*));
  int i = 0;
  for(i = 0; s[i]; i++){
    d[i] = tolower(s[i]);
  }
  d[i] = '\0';
  return d;
}

char *firstofchararry(char *s)
{
  char *c = (char *)malloc(2 * sizeof(char*));
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

char *make_path_full(char *path)
{
  int len = strlen(path);
  char *full_path;

  if (path[len-1] != '/')
  {
    full_path = malloc((len+1) * sizeof(char*));
    for (int i=0; i<len; i++)
    {
      full_path[i] = path[i];
    }
    full_path[len] = '/';
    full_path[len+1] = '\0';
  }
  else
  {
    full_path = malloc(len * sizeof(char*));
    for (int i=0; i<len; i++)
    {
      full_path[i] = path[i];
    }
    full_path[len] = '\0';
  }

  return full_path;
}

char *search_by_language(char *language, char* hello_folder_path)
{
  char* full_path = make_path_full(hello_folder_path);
  char *c = firstofchararry(language);
  char *folder = full_path;
  char *e = "/";
  char *fd = NULL;
  int folder_size = strlen(folder);
  int e_size = strlen(e);
  int c_size = strlen(c);
  int total_size = folder_size + e_size + c_size;
  char *lf = (char *)malloc((total_size) * sizeof(char*));

  strcpy(lf, folder);
  strcat(lf, c);
  strcat(lf, e);

  DIR *dp;
  struct dirent *ep;

  dp = opendir(lf);

  if ( dp != NULL )
  {
    while ( fd )
    {
      ep = readdir(dp);

      if (!ep) {
        break;
      }

      int cpr = compare(language, ep->d_name);
      if ( cpr )
      {
        fd = ep->d_name;
        break;
      }

    }
    closedir(dp);
  }

  char *fp = NULL;

  free(c);
  free(lf);
  free(full_path);

  if ( fd )
  {
    int size = strlen(lf) + strlen(fd);
    fp = (char *)malloc(size * sizeof(char*));
    strcpy(fp, lf);
    strcat(fp, fd);
    return fp;
  }
  return NULL;
}

char *read_helloworld(char *language, char* hello_folder_path)
{
  char *path = search_by_language(language, hello_folder_path);
  char *hello = NULL;
  if (path)
  {
    hello = read_template(path);
  }
  free(path);
  return hello;
}
