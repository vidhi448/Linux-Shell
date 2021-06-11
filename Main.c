#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#define MAXCOM 1000 
#define MAXLIST 100
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define clear() printf("\033[H\033[J") 
static char *history[MAXCOM];
static int history_count = 0;



void add_history( const char *command )
{
   if (history_count < MAXCOM) 
   {
        history[history_count++] = strdup( command );
   } 
   else 
   {
        free( history[0] );
        for (int index = 1; index < MAXCOM; index++) 
        {
            history[index - 1] = history[index];
        }
        history[MAXCOM - 1] = strdup( command );
    }
}

char **split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strtok(line,LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void helpexit()
  {
    printf("\nexit: exit [n]\nExit the shell.\nExits the shell with a status of N.  If N is omitted, the exit status is that of the last command executed.\n\n");
  }

  void helpcd()
  {
    printf("\ncd: cd [-L| [dir]\nChange the shell working directory.\nChange the current directory to DIR. The default DIR is the value of the HOME shell variable.\n");
    printf("Options:\n-L	force symbolic links to be followed: resolve symbolic links in DIR after processing instances of `..'\n");
    printf("`..' is processed by removing the immediately previous pathname component back to a slash or the beginning of DIR.\n");
    printf("Exit Status:\nReturns 0 if the directory is changed, and if $PWD is set successfully when -P is used; non-zero otherwise.\n\n");
  }

  void helppwd()
  {
     printf("\npwd: pwd [-LP]\nPrint the name of the current working directory.\nOptions:\n-L print the value of $PWD if it names the current working directory\n");
     printf("-P	print the physical directory, without any symbolic links\n");
     printf("Exit Status:\nReturns 0 unless an invalid option is given or the current directory cannot be read.\n\n");
  }

void init_shell() 
{ 
    clear(); 
    printf("\n\n\n\n******************************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
    printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n******************************************"); 
    printf("\n"); 
    sleep(1); 
}

  char *read_line(void)
  {
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We recieved an EOF
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }
  return line;
 }

 void printDir() 
  { 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("Dir: %s$ ", cwd); 
  } 
  void printDir2() 
  { 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("%s", cwd); 
  } 

  int ownCmdHandler(char** parsed,char* inputString, char *cwd) 
  { 
    int NoOfOwnCmds = 5, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username; 
  
    ListOfOwnCmds[0] = "cd"; 
    ListOfOwnCmds[1] = "echo"; 
    ListOfOwnCmds[2] = "history"; 
    ListOfOwnCmds[3] = "pwd"; 
    ListOfOwnCmds[4] = "exit";
  
    for (i = 0; i < NoOfOwnCmds; i++) 
    { 
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) 
        { 
            switchOwnArg = i + 1; 
            break; 
        } 
    } 
    if(switchOwnArg==0)
       return 1;

    switch (switchOwnArg) 
    { 
      case 1: 
        if(parsed[1]==NULL)
          chdir(cwd);
        else if(strcmp(parsed[1],"-L")==0)
        {
          if(chdir(parsed[2])==-1)
            printf("NO such file or directory\n");
        }
        else if(strcmp(parsed[1],"--help")==0)
        {
          helpcd();
        }
        else 
        {
          if(chdir(parsed[1])==-1)
            printf("NO such Option or file or directory\n");
        }
        break;

      case 2:;
        if(parsed[1]==NULL)
        {
          printf("Argument required\n");
        }
        else 
        {
        int i;
        if(strcmp(parsed[1],"-E")==0)
          i=2;
        else if(strcmp(parsed[1],"-n")==0)
          i=2;
        else
          i=1;
        for(;i<sizeof(parsed);i++)
        {
          if(parsed[i]!=NULL)
            printf("%s ",parsed[i]);
        }
        if(strcmp(parsed[1],"-n")!=0)
          printf("\n");
        }
        break;

      case 3:
        if(parsed[1]==NULL)
        {
           for(int i=0;i<history_count;i++)
           {
             int d=i+1;
             printf("%d %s",d,history[i]);
           }
        }
        else if(strcmp(parsed[1],"-c")==0)
        {
          history_count=0;
        }
        else if(strcmp(parsed[1],"-d")==0)
        {
          int index=atoi(parsed[2]);
          if(index>=history_count)
          {
            printf("Offset entered is wrong\n");
          }
          else 
          {
          free(history[index-1]);
          for (; index < history_count; index++) 
          {
            history[index - 1] = history[index];
          }
          history_count--;
          }
        }
        else
        {
          printf("Option not present\n");
        }
        
        break; 

      case 4: 
        if(parsed[1]==NULL)
        {
          printDir2();
          printf("\n");
        }
        else if(strcmp(parsed[1],"-L")==0)
        {
          printDir2();
          printf("\n");
        }
        else if(strcmp(parsed[1],"-P")==0)
        {
          printDir2();
          printf("\n");
        }
        else if(strcmp(parsed[1],"--help")==0)
        {
          helppwd();
        }
        else 
        {
          printf("Option not found\n");
        }

        break;

      case 5:
          if(parsed[1]==NULL)
          {
            exit(0);
          }
          else if(strcmp(parsed[1],"--help")==0)
          {
            helpexit();
          }
          else
          {
            int n=atoi(parsed[1]);
            exit(n);
          }

      default:
          printf("Command not found");
          break; 
    } 
    return 0; 
} 

void external_commands(char** parsed,char *cwd)
{
    int pid;
    int status;
    pid = fork ();
    if(pid<0)
    {
      perror("fork creation failed!!!\n"); 
    }
    else if (pid == 0) 
    {
      if(strcmp(parsed[0],"ls")==0)
      {
        char st[1024];
        strcpy(st,cwd);
        strcat(st,"/ls");
        execvp(st,parsed);
      }
      else if(strcmp(parsed[0],"cat")==0)
      {
        char st[1024];
        strcpy(st,cwd);
        strcat(st,"/cat");
        execvp(st,parsed);
      }
      else if(strcmp(parsed[0],"date")==0)
      {
        char st[1024];
        strcpy(st,cwd);
        strcat(st,"/date");
        execvp(st,parsed);
      }
      else if(strcmp(parsed[0],"rm")==0)
      {
        char st[1024];
        strcpy(st,cwd);
        strcat(st,"/rm");
        execvp(st,parsed);
      }
      else if(strcmp(parsed[0],"mkdir")==0)
      {
        char st[1024];
        strcpy(st,cwd);
        strcat(st,"/mkdir");
        execvp(st,parsed);
      }
      else 
      {
        printf("Command not found\n");
      }
    }
    else 
    {
      if (waitpid (pid, &status, 0) == -1)
         perror("parent:error\n");
    }
}

int main(int argc, char **argv) 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd));
    char* inputString;
    init_shell(); 
    while(1) 
    { 
      printDir(); 
        inputString=read_line();
        add_history(inputString);
        char** parsed=split_line(inputString);
        if(ownCmdHandler(parsed,inputString,cwd)==1)
        {
          external_commands(parsed,cwd);
        }
    } 
    return 0; 
}
