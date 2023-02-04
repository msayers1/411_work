/* fread example: read an entire file */ 

#include <stdio.h> 

#include <stdlib.h>  


int convertDecimal_to_IP(int ip){};

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

    int subnetMask =  (unsigned int)(unsigned char)buffer[counter + 4]; 
    int nMask = 0;
    for (int i = 31; i > (31 - subnetMask); i --) {
            nMask |= (1 << i);
    }
    int subnetMaskDecimal[4];
    int counter = subnetMask;
    for (int i = 0; i < 4; i++) {
            printf("%d\n", counter);
            if((counter - 8) > 0){
                subnetMaskDecimal[i] = 255;
                counter = counter - 8;
            } else if (counter > 0){
                printf("%d\n", (7 - counter));
                subnetMaskDecimal[i] = 0;
                for (int j = 7; j > (7 - counter); j--) {
                    subnetMaskDecimal[i] |= (1 << j);
                    printf("%x\n", subnetMaskDecimal[i]);
                }
                
                counter = 0;
            }else{
                subnetMaskDecimal[i] = 0;
            }
    }
    int ip = ((unsigned int)(unsigned char)buffer[counter] << 24) + ((unsigned int)(unsigned char)buffer[counter + 1] << 16) + ((unsigned int)(unsigned char)buffer[counter + 2] << 8) + ((unsigned int)(unsigned char)buffer[counter + 3]);
    int network = ip & nMask;
    printf("%x\n", ip);
    printf("%x\n", network);
    printf("%d\n", subnetMask);
    printf("%x\n", nMask);
    printf("IP address:\t%02x.%02x.%02x.%02x/%02d\n", (unsigned int)(unsigned char)buffer[counter], (unsigned int)(unsigned char)buffer[counter + 1], (unsigned int)(unsigned char)buffer[counter + 2], (unsigned int)(unsigned char)buffer[counter + 3], (unsigned int)(unsigned char)buffer[counter + 4]);
    printf("IP address:\t%02d.%02d.%02d.%02d/%02d\n", (unsigned int)(unsigned char)buffer[counter], (unsigned int)(unsigned char)buffer[counter + 1], (unsigned int)(unsigned char)buffer[counter + 2], (unsigned int)(unsigned char)buffer[counter + 3], (unsigned int)(unsigned char)buffer[counter + 4]);
    // printf("Network Address:\t%02d.%02d.%02d.%02d/%02d\n", (unsigned int)(unsigned char)buffer[counter], (unsigned int)(unsigned char)buffer[counter + 1], (unsigned int)(unsigned char)buffer[counter + 2], (unsigned int)(unsigned char)buffer[counter + 3], (unsigned int)(unsigned char)buffer[counter + 4]);
    // printf("Usable IP range:\t%02d.%02d.%02d.%02d/%02d\n", (unsigned int)(unsigned char)buffer[counter], (unsigned int)(unsigned char)buffer[counter + 1], (unsigned int)(unsigned char)buffer[counter + 2], (unsigned int)(unsigned char)buffer[counter + 3], (unsigned int)(unsigned char)buffer[counter + 4]);
    printf("Subnet mask:\t%02d.%02d.%02d.%02d\n", subnetMaskDecimal[0], subnetMaskDecimal[1], subnetMaskDecimal[2], subnetMaskDecimal[3]);
    //increments counter. 
    counter = counter + 5;
    // Inserts a new line for next ip address. 
    printf("\n");
    
}


 
 

// terminate 

fclose (pFile); 

free (buffer); 

return 0; 

} 

int * convertDecimal_to_IP(int ip){
    static int returnIP[4];
     returnIP[0] = ip & 0xFF;
    returnIP[1] = (ip >> 8) & 0xFF;
    returnIP[2] = (ip >> 16) & 0xFF;
    returnIP[3] = (ip >> 24) & 0xFF;   
    printf("%d.%d.%d.%d\n", returnIP[3], returnIP[2], returnIP[1], returnIP[0]);      
    return returnIP;
}