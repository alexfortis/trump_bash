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

//when the controlling terminal quits
void hupHandler(int sig) {
  printf("It is so nice that the shackles have been taken off me and I can now fight for America the way I want to.\n\n");
  sleep(3);
}

//when the interrupt signal (ctrl+C) is sent
void intHandler(int sig) {
  printf("She went over time, I can go over too.\n\n");
  sleep(3);
}

//when the quit signal (ctrl+\) is sent
void quitHandler(int sig) {
  printf("I\'d never withdraw. I\'ve never withdrawn in my life. No, I\'m not quitting. I have tremendous support.\n\n");
  sleep(3);
}

//bus error (misaligned pointer)
void busHandler(int sig) {
  printf("You\'re fired.\n\n");
  sleep(3);
}

//floating point exception
void fpeHandler(int sig) {
  printf("I\'m very rich, believe me.\n\n");
  sleep(3);
}

//segmentation fault
void segvHandler(int sig) {
  printf("In many cases, I probably identify more as Democrat. It just seems that the economy does better under the Democrats than the Republicans.\n\n");
  sleep(3);
}

//when a child (process) dies
void chldHandler(int sig) {
  int status = 0;
  pid_t childPid = wait(&status);
  printf("I won\'t do anything to take care of them. I\'ll supply funds and she\'ll take care of the kids.\n\n");
  sleep(3);
}

//When the OS pauses this process
void termHandler(int sig) {
  printf("You\'re the puppet.\n\n");
  sleep(3);
}

//when the OS gets this process back
void contHandler(int sig) {
  printf("It\'s just locker room talk.\n\n");
  sleep(3);
}

void ioHandler(int sig) {
  printf("WRONG.\n\n");
  sleep(3);
}

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
  signal(SIGHUP, hupHandler);
  signal(SIGINT, intHandler);
  signal(SIGQUIT, quitHandler);
  signal(SIGBUS, busHandler);
  signal(SIGFPE, fpeHandler);
  signal(SIGSEGV, segvHandler);
  signal(SIGCHLD, chldHandler);
  signal(SIGTERM, termHandler);
  signal(SIGCONT, contHandler);
  signal(SIGIO, ioHandler);
  //fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_SETFL) | O_ASYNC);
  size_t n = 141;
  FILE *tweetFile = fopen("trump_tweets.txt", "r");
  if(tweetFile) {
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
    while(1) {
      srand(time(NULL));
      int tweetIndex = rand()%numLines;
      char *tweet = fix(tweets[tweetIndex]);
      sleep(3);
      printf("%s\n", tweet);
      free(tweet);
    }
  }
  else {
    printf("error: tweet file is NULL\n");
  }
}
