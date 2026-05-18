#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void scan_memory(pid_t pid){
    
    
    //this void recieves no input from the user, but it recives an input from other function which is pid we made in process-monitor.c
    char maps_file[64];//we empty this much [64] memory space for this variable
    
    sprintf(maps_file, "/proc/%d/maps", pid);//we used the variable we just created inside sprintf which is ....diffrent from our usual printf, this void takes in a variable called pid wich is of pid_t type which is a custum made variable which was originally an int?char?struct? what? the secound variable used inside sprintf is a path with type sting
    
    FILE *maps = fopen(maps_file, "r");//this means we are opening a file, so before we had to make a file called maps_file so it will exist when we want to open it here, the lets talk about what is FILE and where it came from, what is *maps
    

    if(!maps){

        //!maps means if the value inside maps was zero?
        perror("maps");
        return;//why hre we just return and not exit(1 or 0)here?

    }

    char line[256];

    
    while (fgets(line, sizeof(line), maps)){

        //fgets is what? 
        unsigned long start, end;
        char perm[5];

        if(sscanf(line, "%lx-%lx %4s", &start, &end, perm)!=3){
            //what datatype is xl?
            continue;//explain what is heppening inside this if loop
        }

        if(strstr(perm, "x")){
            //why there are wierd functions here like this double str strstr?
            printf("[scan] executable region: %lx-%lx\n", start, end);
        }
    }

    fclose(maps);
}



int main (int argc, char *argv[]){

    if (argc < 2){

        printf("usage : %s <pid>\n", argv[0]);
        return 1;
        //explain all these
    }

    scan_memory(atoi(argv[1]));

    return 0;
    //explain-teach atoi
}