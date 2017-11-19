#include "interpret.h"
#define NEWREF_DB false
#define KILLSESSION_DB false

Session newSession(void)
{
  Session new;

  new.mode = INTERACTIVE;

  new.program = 0;
  new.line = 0;
  new.symbol = 0;
  new.chr = 0;

  new.filev = (Program*)malloc(sizeof(Program));
  new.filec = 1;

  new.active = &new.filev[0]; 

  new.refv = NULL;
  new.refc = 0;
  new.refnames = NULL;

  return new;
}

void killSession(Session *toKill)
{
  int i;

  for(i = 0; i < toKill->filec; i++)
  {
    killProgram(&toKill->filev[i]);
  }
  toKill->active = NULL;
  free(toKill->filev); toKill->filev = NULL;
  toKill->filec = 0;
  
  if(toKill->refv != NULL)
  {
    for(i = 0; i < toKill->refc; i++)
    {
      fclose(toKill->refv[i]);
      toKill->refv[i] = NULL;
    }
    free(toKill->refv); toKill->refv = NULL;
    toKill->refc = 0;
  }
}

void endSession(Session *toEnd)
{
  killSession(toEnd);
}

void loadRef(Session *s, int refn)
{
  char c;
  printf("LOAD REF #%d. FILENAME: %s\n",refn, s->refnames[refn].chars);
  addProgram(s,s->refnames[refn]);

  while((c = fgetc(s->refv[refn])) != EOF)
  {
    //read
  }
  if(feof(s->refv[refn]))
  {
    //great success
  }
  else
  {
    throwExceptionWithString(BAD_FILE_READ,s->refnames[refn].chars);
  }
  printf("successful refload #%d\n",refn);
}

void loadRefs(Session *s)
{
  int i;

  for(i = 0; i < s->refc; i++)
  {
    loadRef(s,i);
  }
}

void newRef(Session *s,FILE *ref, const char* name)
{
  
  NEWREF_DB ? printf("making new ref to %p in session @%p with name '%s'\n",s,ref,name) : 0;
  s->refc++;
  NEWREF_DB ? printf("incremented refc to %d\n",s->refc) : 0;

  NEWREF_DB ? printf("about to allocate %ld bytes (%d * %ld), cast to (FILE**) and assign it to refv @%p\n",sizeof(FILE*) * s->refc,s->refc,sizeof(FILE*),s->refv) : 0;
  s->refv = (FILE**)safeRealloc(s->refv,sizeof(FILE*) * s->refc);
  s->refv[s->refc-1] = ref;
  NEWREF_DB ? printf("refv[%d] points to %p\n",s->refc,s->refv[s->refc]) : 0;
  NEWREF_DB ? printf("sizeof new refv: %ld bytes located @%p\n",sizeof(s->refv), s->refv) : 0;
  
  s->refnames = (String*)safeRealloc(s->refnames,sizeof(String) * s->refc);
  NEWREF_DB ? printf("about to assign file name '%s' to String ",name) : 0;
  NEWREF_DB ? printString(constToString(name)) : 0;

  s->refnames[s->refc-1] = constToString(name);
}

void addProgram(Session *s,String name)
{
  s->filec++;

  printf("adding program called '%s' to file in filev[%d]\n",name.chars,s->filec-1);
  s->filev = (Program*)safeRealloc(s->filev,sizeof(Program)*s->filec);
  s->filev[s->filec-1] = newProgram(name);
}
