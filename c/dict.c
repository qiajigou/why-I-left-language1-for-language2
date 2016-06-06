#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dict.h"

dictnode *node_create(char *key, char *value)
{
  dictnode *n = calloc(1, sizeof(dictnode));
  n->key = key;
  n->value = value;
  n->next = NULL;
  return n;
}

dict *dict_create()
{
  dict *d = calloc(1, sizeof(dict));
  d->nodelist = NULL;
  return d;
}

void dict_destory(dict *d)
{
  if ( d->nodelist )
  {
    dictnode *n = d->nodelist;
    while ( n )
    {
      free(n);
      n = n->next;
    }
  }
  free(d);
}

void dict_insert(dict *d, char *key, char* value)
{
  dictnode *n = node_create(key, value);

  if ( d->nodelist )
  {
    dictnode *t = d->nodelist;

    while ( t )
    {
      if (strcmp(key, t->key) == 0)
      {
        t->value = value;
        return;
      }

      if ( t->next )
      {
        t = t->next;
      }
      else
      {
        break;
      }
    }

    t->next = n;
    // end of while
  }
  else
  {
    d->nodelist = n;
  }
}

void print_dict(dict *d)
{
  if ( d->nodelist )
  {
    dictnode *t = d->nodelist;

    while ( t )
    {
      printf("key=%s, value=%s\n", t->key, t->value);
      t = t->next;
    }
  }
}

char *get_value_by_key(dict *d, char *key)
{
  if ( !d->nodelist )
  {
    printf("%s\n", "nothing");
    return NULL;
  }

  dictnode *t = d->nodelist;

  while (t)
  {
    if ( strcmp(t->key, key) == 0 )
    {
      return t->value;
    }
    t = t->next;
  }

  return NULL;
}