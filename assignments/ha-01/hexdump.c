/* fread example: read an entire file */ 

#include <stdio.h> 

#include <stdlib.h>  
 

int main (int argc, char *argv[]) { 
//Brings in the N value. 
int hexN = atoi(argv[2]);
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
    if(counter%hexN == 0){
        int hexDigit = counter * 2;
        // prints out the location based on the counter. 
        printf("%08x ", counter);
    }
    //Prints out the data changing it into hex. 
    printf("%02x ", (unsigned int)(unsigned char)buffer[counter]);
    // If you want the output like Hexdump vice xdd. 
    // printf("%02x", (unsigned int)(unsigned char)buffer[counter + 1]);
    // printf("%02x \n", (unsigned int)(unsigned char)buffer[counter]);
    //increments counter. 
    counter++;
    // checks for break points again to see if it needs to insert a new line. 
    if(counter%hexN == 0){
        printf("\n");
    }
}


 
 

// terminate 

fclose (pFile); 

free (buffer); 

return 0; 

} 

 