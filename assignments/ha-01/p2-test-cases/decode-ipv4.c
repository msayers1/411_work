/* fread example: read an entire file */ 

#include <stdio.h> 

#include <stdlib.h>  




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



// printf("Total size of %s = %ld bytes", argv[1], lSize); 

// allocate memory to contain the whole file: 

buffer = (char*) malloc (sizeof(char)*lSize); 

if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);} 

 
 

// copy the file into the buffer: 



//checks that the full file got into the buffer. 
// if (result != lSize) {fputs ("Reading error",stderr); exit (3);} 
/* the whole file is now loaded in the memory buffer. */ 

//sets up a counter. 
int counter = 0;
//while loop to loop through the file taking each ip and subnet mask at a time. 
while ((result = fread(buffer,5,1,pFile)) > 0){
    
    //Grabbing the subnet mask. 
    int subnetMask =  (unsigned int)(unsigned char)buffer[counter + 4]; 
    //Creating the mask for the subnet mask #. 
    int nMask = 0;
    for (int i = 31; i > (31 - subnetMask); i --) {
            nMask |= (1 << i);
    }
    //initializing the subnetMask decimal and then working through each octet. 
    int subnetMaskDecimal[4];
    int counter = subnetMask;
    for (int i = 0; i < 4; i++) {
            // case for if the octet is full
            if((counter - 8) > 0){
                subnetMaskDecimal[i] = 255;
                //taking the counter down an octet. 
                counter = counter - 8;
            // case for if the octet is not full, but not empty
            } else if (counter > 0){
                // printf("%d\n", (7 - counter));
                subnetMaskDecimal[i] = 0;
                for (int j = 7; j > (7 - counter); j--) {
                    subnetMaskDecimal[i] |= (1 << j);
                    // printf("%x\n", subnetMaskDecimal[i]);
                }
                //setting counter to 0. 
                counter = 0;
            // case for if the octet is empty
            }else{
                subnetMaskDecimal[i] = 0;
            }
    }
    //Bringing in the IP address. 
    int ip = ((unsigned int)(unsigned char)buffer[counter] << 24) + ((unsigned int)(unsigned char)buffer[counter + 1] << 16) + ((unsigned int)(unsigned char)buffer[counter + 2] << 8) + ((unsigned int)(unsigned char)buffer[counter + 3]);
    //Getting the network address by AND the ip and the mask. 
    int network = ip & nMask;
    //Now getting the decimal for the Network. 
    int networkDecimal[4];
    networkDecimal[0] = network & 0xFF;
    networkDecimal[1] = (network >> 8) & 0xFF;
    networkDecimal[2] = (network >> 16) & 0xFF;
    networkDecimal[3] = (network >> 24) & 0xFF;
    //Now getting the decimal for the starting IP for the network. 
    int startingIP = network + 1;
    int startingIPDecimal[4];
    startingIPDecimal[0] = startingIP & 0xFF;
    startingIPDecimal[1] = (startingIP >> 8) & 0xFF;
    startingIPDecimal[2] = (startingIP >> 16) & 0xFF;
    startingIPDecimal[3] = (startingIP >> 24) & 0xFF;   
    //Now getting the decimal for the ending IP for the network. 
    int endingIP = network + (1 << (32 - subnetMask)) - 2;
    int endingIPDecimal[4];
    endingIPDecimal[0] = endingIP & 0xFF;
    endingIPDecimal[1] = (endingIP >> 8) & 0xFF;
    endingIPDecimal[2] = (endingIP >> 16) & 0xFF;
    endingIPDecimal[3] = (endingIP >> 24) & 0xFF;   
    //Printing out the required data. 
    printf("IP address:      %d.%d.%d.%d\n", (unsigned int)(unsigned char)buffer[counter], (unsigned int)(unsigned char)buffer[counter + 1], (unsigned int)(unsigned char)buffer[counter + 2], (unsigned int)(unsigned char)buffer[counter + 3]);
    printf("Network address: %d.%d.%d.%d\n", networkDecimal[3], networkDecimal[2], networkDecimal[1], networkDecimal[0]);
    printf("Usable IP range: %d.%d.%d.%d - %d.%d.%d.%d\n", startingIPDecimal[3], startingIPDecimal[2], startingIPDecimal[1], startingIPDecimal[0], endingIPDecimal[3], endingIPDecimal[2], endingIPDecimal[1], endingIPDecimal[0]);
    printf("Subnet mask:     %d.%d.%d.%d\n", subnetMaskDecimal[0], subnetMaskDecimal[1], subnetMaskDecimal[2], subnetMaskDecimal[3]);
    // Inserts a new line for next ip address. 
    printf("\n");    
}

fclose (pFile); 

free (buffer); 

return 0; 

} 
