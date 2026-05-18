//we will use ptrace(the api which strace uses)
//to record all syscalls
//that belong to a process
//we will analyze syscalls like:
//open, write,connect,execv
//we will basically detect shellcode or injection behaviour. how?
//so explain the wole logic in thi code, how it it planning to reach it's goal?
//is it only an ids, or can we then play with thses processes we are watching here?are we a sole observer?how can we sart interacting with them?i other than the kill or freeze**
#include <sys/ptrace.h>
#include <sys/types.h> //why we use types library
#include <sys/wait.h> // why we ...
#include <sys/reg.h> //why we use this?what is orig_rax
#include <unistd.h>//why we use this?
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>//why we use this?
//explain everything like a pro network and system engineer
//exec()	جایگزین کردن باینری مشکوک
//fork()	ساخت child برای process monitoring
//ptrace	مانیتورینگ کامل syscallها
//mmap/mem	بررسی حافظه process
//signal handling	پاسخ خودکار به حمله
//اضافه کردن socket monitor با netlink


int main(int argc, char *argv[]){
    //commands

    while(1){
        //eternal program loop in while(1)
        //we let the program run before syscall, what doese it even mean and how?
        if(argc <2){
            //if argc <2 mwans if number of inputs is something wrong(like error)?
            //because argc is argumet(inputs user enters in cli) count, and 2 means stderr, argc < 2 must mean something like if wrong number of inputs..

        }

        //after checking argument count what is the best loop/condition/variable to initialize and how do we decide on that in such program like this?
        pid_t child = fork(); //what is pid_t, where in library it belongs? here by initializing a custom variable called child we make a variable that can copy the input in it because child is equal to fork(), and also because fork is used for copying a process and duplicating it, am i right?

        if (child ==0 ){
            // if child == 0 means if the child variable have benn used in anywhere inside the cod, because 0 means stdin, so child == 0 must mean something like fork() == stdin means when fork has had benn used somewhere, am i right?
            ptrace(PTRACE_TRACEME, 0, NULL, NULL);// you should explain these more. what about this constant variable because it is all in caps and it must have came from one of those libraries we have just included, and it goese inside ptrace as the first argument which means...? explain ptrace system call and what is it taking as inputs overal more. you should explain all new or imported variables, system calls when you are teaching a code.
            execvp(argv[1], &argv[1]);//explain execvp. and what it can do, and what it doese here. i guess it is taking an argument vector which is the uset input or someinput from somewhere, and it is taking in the secound element of that input or that [1] indicates the memrory this argv is going to occupy.
            //the it takes the value which is stored inside this input (argument vector) and that is only the place of argv[1]byte and argv[2] or argv[0] will not be included inside that container &argv[1], am i right?

            perror("execvp");//here we perror so if the previous apis we used fail here the perror system call realizes it automatically or we use this perror api because this loop is a (if failed) condition if chil ==0 is a failing situation?
            //we exit with 1 which means stdout?
            exit(1);
        } else {
            //if the previous if condition wasafailing condition, the this else means if child was successfull?
            int status;
            long syscall;
            wait(&status);//the whole situation here inside else needs explanatin, so we if the forking was sucessfull, will create two variable one in type of int and the other with type of long, then we use wait syscall which what it doese is ..? and we put the value inside status which has benninitialized but has not been assigned anything else yet, wich means we will be accesing it outside this condition through the code and maybe inside other loops/conditions

            while(1){
                //here we will write all the real things our programs do because it is written inside an ever running loop cause while(1) means while(true) which is always
                //let program run before the syscall be run by the program or the program of the target
                ptrace(PTRACE_SYSCALL, child, NULL, NULL);//which means we use ptrace system call, it uses child variable which is actually fork() wich is a duplicationg function,this whole api mans when ..
                wait(&status); //we have used status again. what doese it even do it has not been assigned anywhere yet
                if (WIFEXITED(status))break; //which means in a special status, the exit will happen

                //read the syscall number, which means read what pid/hash this syscall has in kernel right now?
                syscall = ptrace(PTRACE_PEEKUSER, child, NULL, NULL); //explain please
                wait(&status);
                if(WIFEXITED(status)) break; //?

            }
        }




    }
    return 0;
}
//در نسخه پیشرفته‌تر می‌توانیم:

//نام System Call واقعی بنویسیم (جدول map).
//آرگومان‌های فوتبال را از دیگر رجیسترها (RDI, RSI, RDX) بخوانیم.