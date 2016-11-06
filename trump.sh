trap "killall -SIGINT trump" SIGINT
trap "killall -SIGQUIT trump" SIGQUIT
FILE="trump"
TITLE="^[Tt]r(ump_[Bb])?ash$"
printf "%s\n\n" "Donald Trump is stuck in a Terminal and can\'t get out! Of course, we don\'t want him out, but we can still communicate with him. He will send out tweets every few seconds, and we can send him signals, which he will respond to."
if [ -f $FILE ]; then
    rm $FILE
fi
make $FILE

./$FILE &
sigs=(SIGQUIT SIGHUP SIGINT SIGQUIT SIGBUS SIGFPE SIGSEGV SIGCHLD SIGSTOP SIGCONT SIGIO)
while true;
do
    if pgrep "$FILE" > /dev/null;
    then
	break
    fi
done
while true;
do
    if pgrep "$FILE" > /dev/null;
    then
	signal=$(zenity --entry --title $TITLE --text "${sigs[@]}" --text "Choose a signal to send to Mr. Trump, or click Cancel to quit.")
	killall -$signal $FILE
    else
	break
    fi
done
printf "%s is a mess. %s is a big fat mistake.\n" $USER $USER
