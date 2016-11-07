# ^[Tt]r(ump_[Bb])?ash$
Terminal Based Donald Trump Emulator

Have you ever wondered what would happen if Donald Trump were a process running on your computer? Wonder no more!

Donald Trump is stuck inside your terminal, and he can only communicate by tweeting at you and responding to signals. You can communicate with him by sending him signals from the GUI.

To run the program, just execute the trump.sh script.

Notes:
- On Mac, zenity windows show up behind the terminal window.
- The regular expression in the title not only matches trump_bash but also trash, because Trump is trash.

Guide to signals:
- SIGHUP is the hangup signal, sent when the controlling terminal exits.
- SIGINT is the interrupt signal.
- SIGQUIT is the quit signal.
- SIGBUS is a bus error, sent when the program tries to access a misaligned pointer.
- SIGFPE is a floating point exception, sent when the program performs invalid arithmetic.
- SIGSEGV is a segmentation violation, when the program tries to access memory it's not supposed to.
- SIGCHLD is the child signal, sent when a child process dies.
- SIGTERM is the terminate signal.
- SIGSTOP is the stop signal, used to pause the process until SIGCONT.
- SIGCONT is the continue signal.
- SIGIO is the signal that an input/output device is ready.

Enjoy!