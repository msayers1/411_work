/* fread example: read an entire file */ 

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>  
 

int main (int argc, char *argv[]) { 
//Brings in the search term. 
unsigned int needle = atoi(argv[2]);
//Brings in the data type.
char* data_type = argv[3];
char *endptr;
int needle_size = strtol(data_type, &endptr, 10);
char encoding = data_type[1];
//printf("0x%08x %x %d", needle, needle, needle);
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

result = fread (buffer, 1,lSize,pFile); 

//checks that the full file got into the buffer. 
if (result != lSize) {fputs ("Reading error",stderr); exit (3);} 
/* the whole file is now loaded in the memory buffer. */ 

//sets up a counter. 
int counter = 0;
//while loop to loop through the file. 
while(counter < lSize){
    //checks for break points based on N value. 
    int data_address = counter;
    unsigned long decimal = 0;
        if(encoding == 'b'){
            for(int i = 0; i < needle_size; i++){
                //printf("%dx%X ", counter, (unsigned int)(unsigned char)buffer[counter]);
                decimal = (decimal << 8) | (unsigned int)(unsigned char)buffer[counter];
                counter++;
            }
        } else if (encoding == 'l') {
            counter = counter + (needle_size - 1);
            for(int i = 0; i < needle_size; i++){
                //printf("%dx%X", counter, (unsigned int)(unsigned char)buffer[counter]);
                decimal = (decimal << 8) | (unsigned int)(unsigned char)buffer[counter];
                counter--;
            }
            counter = counter + (needle_size + 1);
        } else {fputs ("Encoding error",stderr); exit (3);}
    
    //printf("\t %lX \t %lu \n", decimal, decimal);
    if(needle == decimal){
        printf("0x%08X 0x%X %d\n", data_address, needle, needle );
    }
    decimal = 0;
    //counter = counter + needle_size;
    unsigned int data_byte = (unsigned int)(unsigned char)buffer[counter];
    //printf("%02x \t", data_byte);
    // if(data_byte == needle){
    //     printf("0x%08X ( %d ) 0x%X %d\n", counter, data_byte, needle, needle );
    // }
    // printf("%sx \n", return_string);
    
    //printf("%02x \n", (unsigned int)(unsigned char)buffer[counter]);
    
    
}


 
 

// terminate 

fclose (pFile); 

free (buffer); 

return 0; 

} 

