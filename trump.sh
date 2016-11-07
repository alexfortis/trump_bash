#!/bin/bash

FILE="trump"
TITLE="^[Tt]r(ump_[Bb])?ash$"
printf "%s\n\n" "Donald Trump is stuck in a Terminal and can't get out! Of course, we don't want him out, but we can still communicate with him. He will send out tweets every few seconds, and we can send him signals, which he will respond to."
if [ -f $FILE ]; then
    rm $FILE
fi
make $FILE 2> /dev/null

./$FILE &
sigs=(SIGKILL SIGSTOP SIGHUP SIGINT SIGQUIT SIGBUS SIGFPE SIGSEGV SIGCHLD SIGTERM SIGCONT SIGIO)
running=`ps -e | grep -c ${FILE}\$`
while [ ${running} -eq 0 ];
do
    : #do nothing while waiting for trump to start
done
while [ ${running} -gt 0 ];
do
    signal=$(zenity --entry --title $TITLE --text "${sigs[@]}" --text "Choose a signal to send to Mr. Trump, or click Cancel to quit.\nSend SIGSTOP to pause the Donald, SIGCONT to resume." 2> /dev/null)
    if [[ $? -eq 1 ]]; then
	killall -KILL $FILE
	break
    fi
    killall -$signal $FILE
done
printf "%s is a mess. %s is a big fat mistake.\n" $USER $USER
rm -rf trump *.dSYM #the .dSYM files appear on Mac