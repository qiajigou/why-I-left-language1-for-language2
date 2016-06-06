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
  char *d = (char *)malloc(strlen(s));
  for(int i = 0; s[i]; i++){
    d[i] = tolower(s[i]);
  }
  return d;
}

char *firstofchararry(char *s)
{
  char *c = (char *)malloc(2);
  for(int i=0; i<1; i++){
    c[i] = tolower(s[i]);
  }
  free(c);
  return c;
}

int compare(char *language, char* language_file)
{
  char *lan = strtolower(language);
  char *lf = strtolower(language_file);
  lf = strtok(lf, ".");

  if ( lan && lf && strcmp(lan, lf) == 0 )
  {
    free(lan);
    free(lf);
    return 1;
  }
  return 0;
}

char *search_by_language(char *language)
{
  char *c = firstofchararry(language);
  char *folder = "./hello-world/";
  char *e = "/";
  char *fd = NULL;
  char *lf = malloc(strlen(folder) + strlen(e) + strlen(c) + 1);

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

      if ( compare(language, ep->d_name) )
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
    free(lf);
    free(fp);
  }

  return fp;
}

char *read_helloworld(char *language)
{
  char *path = search_by_language(language);
  char *hello = NULL;
  if (path)
  {
    hello = read_template(path);
  }
  return hello;
}
