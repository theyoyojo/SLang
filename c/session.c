#include "interpret.h"
#include "parse.h"

#define LIVE_NAME "LIVE"
#define DEFAULT_BUFFER_SIZE 1000

#define NEWREF_DB false 
#define KILLSESSION_DB false
#define LOADREF_DB false
#define ADDPROGRAM_DB false

Session newSession(void)
{
  Session new;

  new.mode = INTERACTIVE;

  new.program = 0;
  new.line = 0;
  new.symbol = 0;
  new.chr = 0;

  new.filev = (Program*)malloc(sizeof(Program));
  new.filev[0] = newProgram(constToString(LIVE_NAME));
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

  KILLSESSION_DB ? printf("about to loop from 0 to %d (filec)\n",toKill->filec) : 0;
  for(i = 0; i < toKill->filec; i++)
  {
    KILLSESSION_DB ? printf("inremented i to %d\n",i) : 0;
    KILLSESSION_DB ? printf("about to kill program '%s' in filev[%d]\n",toKill->filev[i].name.chars,i) : 0;
    killProgram(&toKill->filev[i]);
    KILLSESSION_DB ? printf("kill success\n") : 0;
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
  int buffLength,i;
  char* buff;
  String raw;
  StringString parsed;
  LOADREF_DB ? printf("LOAD REF #%d. FILENAME: %s\n",refn, s->refnames[refn].chars) : 0;
  addProgram(s,s->refnames[refn]);
  s->active = &s->filev[0];

  LOADREF_DB ? printf("[IF you must know] s->active->lines points to %p\n",s->active->lines) : 0;

  while((c = fgetc(s->refv[refn])) != EOF)
  {
    LOADREF_DB ? printf("[@c=%c IF you must know] s->active->lines points to %p\n",c,s->active->lines) : 0;
    ungetc(c,s->refv[refn]);
    buffLength = getRawLine(s->refv[refn],&buff,DEFAULT_BUFFER_SIZE);
    raw = newString(buffLength); 
    for(i = 0; i < buffLength; i++)
    {
      raw.chars[i] = buff[i];
    }
    free(buff); buff = NULL;
    parsed = parseRawLine(raw);
    
    //must be refn+1 beacause filev[0] is the live program buffer
    appendLine(&s->filev[refn+1],&parsed);
    killString(&raw);
    
  }
  if(feof(s->refv[refn]))
  {
    //great success
    LOADREF_DB ? printf("[@EOF IF you must know again] s->active->lines points to %p\n",s->active->lines) : 0;
  }
  else
  {
    throwExceptionWithString(BAD_FILE_READ,s->refnames[refn].chars);
  }
  LOADREF_DB ? printf("successful refload #%d\n",refn) : 0;
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
  NEWREF_DB ? printString(stdout, constToString(name)) : 0;

  s->refnames[s->refc-1] = constToString(name);
}

void addProgram(Session *s,String name)
{
  s->filec++;
  ADDPROGRAM_DB ? printf("incrememnted filec to %d\n",s->filec) : 0;

  ADDPROGRAM_DB ? printf("realloc %ld bytes for for Program* filev, adding '%s' to filev[%d]\n",sizeof(Program)*s->filec,name.chars,s->filec-1) : 0;
  s->filev = (Program*)safeRealloc(s->filev,sizeof(Program)*s->filec);
  s->filev[s->filec-1] = newProgram(name);
}
