/* fread example: read an entire file */ 

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>  
 
void decodeCommand(unsigned int Byte);

int main (int argc, char *argv[]) { 
//Pointer for the file. 
FILE * pFile; 
//File Size
long lSize; 
//Buffer variable
char * buffer; 
//Result size. 
size_t result; 

 
 
//Opens the file. 
pFile = fopen (argv[1], "rb" ); 
//Checks if there was an error opening the file. 
if (pFile==NULL) {fputs ("File error",stderr); exit (1);} 

 
 

// obtain file size: 

fseek (pFile , 0 , SEEK_END); 

lSize = ftell (pFile); 

rewind (pFile); 

// printf("Total size of %s = %ld bytes", argv[1], lSize); 

// allocate memory to contain the whole file: 

buffer = (char*) malloc (sizeof(char)*lSize); 

if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);} 

 
 

// copy the file into the buffer: 

result = fread (buffer,1,lSize,pFile); 

//checks that the full file got into the buffer. 
if (result != lSize) {fputs ("Reading error",stderr); exit (3);} 
/* the whole file is now loaded in the memory buffer. */ 

//sets up a counter. 
int counter = 0;
//while loop to loop through the file. 
while(counter < lSize){
    //checks for break points based on N value. 
    unsigned int data_byte = (unsigned int)(unsigned char)buffer[counter];
    //printf("%02x \t", data_byte);
    decodeCommand(data_byte);
    // char * return_string = decodeCommand(data_byte);
    // printf("%sx \n", return_string);
    
    //printf("%02x \n", (unsigned int)(unsigned char)buffer[counter]);
    counter++;
    
}


 
 

// terminate 

fclose (pFile); 

free (buffer); 

return 0; 

} 

 void decodeCommand(unsigned int data_byte){
    //printf("%02x \n", data_byte);
    //printf("%x \t", data_byte & 0x3);
    int command_parts[4];
    command_parts[3]= data_byte & 0x3;
    //printf("%x \t", (data_byte >> 2) & 0x3);
    command_parts[2] = (data_byte >> 2) & 0x3;
    //printf("%x \t", (data_byte >> 4) & 0x3);
    command_parts[1] = (data_byte >> 4) & 0x3;
    //printf("%x \t", (data_byte >> 6) & 0x3);
    command_parts[0] = (data_byte >> 6) & 0x3;
    //printf("%d %d %d %d \n", command_parts[0], command_parts[1], command_parts[2], command_parts[3]);
    char decoded_command[14] = "";
    char operation_part[5] = "mul \0";
    //Switch Case to deal with command decoding
    switch(command_parts[0]) {
        case 0:
            break;
        case 1:
            operation_part[0] = 'd';
            operation_part[1] = 'i';
            operation_part[2] = 'v';
            break;
        case 2:
            operation_part[0] = 'a';
            operation_part[1] = 'd';
            operation_part[2] = 'd';
            break;
        case 3:
            operation_part[0] = 's';
            operation_part[1] = 'u';
            operation_part[2] = 'b';
            break;
    }
    printf("%s ", operation_part);
    //strcat(decoded_command, operation_part);
    //Switch Case to deal with register designations ( For loop since there are always 3 registers in this exercise)
    for(int i = 1; i < 4; i++){
        // printf("%d \t", i);
        char register_address[4] = "t0 \0";
        // printf("%s \t", register_address);
        switch(command_parts[i]) {
            case 0:
                break;
            case 1:
                register_address[0] = 't';
                register_address[1] = '1';
                break;
            case 2:
                register_address[0] = 's';
                register_address[1] = '0';
                break;
            case 3:
                register_address[0] = 's';
                register_address[1] = '1';
                break;
        }
        printf("%s ", register_address);
        //decoded_command = strcat(decoded_command, register_address);
    }
    printf("\n");
    // char *str = malloc(14);
    // *str = *decoded_command;
    // return str;
} 