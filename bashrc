#include <unistd.h>
# System-wide .bashrc file for interactive bash(1) shells.
if [ -z "$PS1" ]; then
   return
fi
export PATH="/usr/local/bin:$PATH"
PS1='\h:\W \u\$ '

# Make bash check its window size after a process completes
shopt -s checkwinsize

function secure_ls {
	#sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
#	sudo cc -o /usr/local/bin/commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium
	sudo cc -o /usr/local/bin/commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium
	./commandpass "ls"
}

[ -r "/etc/bashrc_$TERM_PROGRAM" ] && . "/etc/bashrc_$TERM_PROGRAM"
sudo cc -o password -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/password.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium
./password

#sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium

#make bash run the password script every time -ls command is written
alias ls='secure_ls'
alias kill='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "kill"'
alias rm='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "rm"'
alias pwd='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "pwd"'
alias cp='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "cp"'
alias mv='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "mv"'
alias chmod='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "chmod"'
alias ps='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "ps"'
alias cat='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "cat"'
alias wget='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "wget"'
alias mv='sudo cc -o commandpass -I/opt/homebrew/Cellar/libsodium/1.0.19/include /etc/commandpass.c -L/opt/homebrew/Cellar/libsodium/1.0.19/lib -lsodium 
./commandpass "mv"'
