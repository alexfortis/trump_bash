#pragma GCC diagnostic ignored "-Wunused-parameter" 
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

//use this to handle all incoming signals
void handler(int sig) {
  int status = 0;
  pid_t childPid;
  switch(sig) {
  case SIGHUP: //hangup
    printf("It is so nice that the shackles have been taken off me and I can now fight for America the way I want to.\n\n");
    break;
  case SIGINT: //interrupt
    printf("She went over time, I can go over too.\n\n");
    break;
  case SIGQUIT: //quit
    printf("I\'d never withdraw. I\'ve never withdrawn in my life. No, I\'m not quitting. I have tremendous support.\n\n");
    break;
  case SIGBUS: //bus error
    printf("You\'re fired.\n\n");
    break;
  case SIGFPE: //floating point exception
    printf("I\'m very rich, believe me.\n\n");
    break;
  case SIGSEGV: //segmentation violation
    printf("In many cases, I probably identify more as Democrat. It just seems that the economy does better under the Democrats than the Republicans.\n\n");
    break;
  case SIGCHLD: //child process dies
    childPid = wait(&status);
    printf("I won\'t do anything to take care of them. I\'ll supply funds and she\'ll take care of the kids.\n\n");
    break;
  case SIGTERM: //terminate
    printf("You\'re the puppet.\n\n");
    break;
  case SIGCONT: //continue
    printf("It\'s just locker room talk.\n\n");
    break;
  case SIGIO: //I/O ready
    printf("WRONG.\n\n");
    break;
  default: //just in case
    printf("You\'re wrong.\n\n");
  }
  //give the user time to read Trump's response
  sleep(3);
}

//take care of extraneous escape characters and such
char *fix(char *broken) {
  char *ret = (char *)calloc(strlen(broken), sizeof(char));
  int counter = 0;
  for(unsigned i = 0; i < strlen(broken); i++) {
    if(broken[i] == '\\') {
      if(broken[i+1] == 'n') {
	ret[counter] = '\n';
	i++;
      }
    }
    else if(broken[i] == '&') {
      if((broken[i+1] == 'a') &&
	 (broken[i+2] == 'm') &&
	 (broken[i+3] == 'p') &&
	 (broken[i+4] == ';')) {
	i += 4;
	ret[counter] = '&';
      }
    }
    else {
      ret[counter] = broken[i];
    }
    counter++;
  }
  return ret;
}

int main() {
  //set up the signal handlers
  signal(SIGHUP, handler);
  signal(SIGINT, handler);
  signal(SIGQUIT, handler);
  signal(SIGBUS, handler);
  signal(SIGFPE, handler);
  signal(SIGSEGV, handler);
  signal(SIGCHLD, handler);
  signal(SIGTERM, handler);
  signal(SIGCONT, handler);
  signal(SIGIO, handler);
  //get the file
  size_t n = 141;
  FILE *tweetFile = fopen("trump_tweets.txt", "r");
  if(tweetFile) {
    //read in all the lines from the file
    char *buf = (char *)calloc(n, sizeof(char));
    getline(&buf, &n, tweetFile);
    int numLines = atoi(buf);
    char *tweets[numLines];
    tweets[0] = buf;
    for(int i = 0; i < numLines; i++) {
      buf = (char *)calloc(n, sizeof(char));
      getline(&buf, &n, tweetFile);
      tweets[i] = buf;
    }
    fclose(tweetFile);
    //every 3 seconds, print a random tweet from tweetFile to stdout
    while(1) {
      srand(time(NULL));
      int tweetIndex = rand()%numLines;
      char *tweet = fix(tweets[tweetIndex]);
      sleep(3);
      printf("%s\n", tweet);
      free(tweet);
    }
  }
  //error checking
  else {
    printf("error: tweet file is NULL\n");
  }
}
