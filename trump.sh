#!/bin/bash

FILE="trump"
TITLE="^[Tt]r(ump_[Bb])?ash$"
printf "%s\n\n" "Donald Trump is stuck in a Terminal and can\'t get out! Of course, we don\'t want him out, but we can still communicate with him. He will send out tweets every few seconds, and we can send him signals, which he will respond to."
if [ -f $FILE ]; then
    rm $FILE
fi
make $FILE

./$FILE &
sigs=(SIGQUIT SIGHUP SIGINT SIGQUIT SIGBUS SIGFPE SIGSEGV SIGCHLD SIGSTOP SIGCONT SIGIO)
running=`ps --no-headers -C $FILE | wc -l`
while true;
do
    if [ ${running} -gt 0 ];
    then
	break
    fi
done
while [ ${running} -gt 0 ];
do
    signal=$(zenity --entry --title $TITLE --text "${sigs[@]}" --text "Choose a signal to send to Mr. Trump, or click Cancel to quit.")
    if [[ $? -eq 1 ]]; then
	killall -KILL $FILE
	break
    fi
    killall -$signal $FILE
done
printf "%s is a mess. %s is a big fat mistake.\n" $USER $USER
