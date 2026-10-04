#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
  for(int i=1; i<argc;i++){
    
    FILE *file=fopen(argv[i],"rb");
    
    if(file==NULL)
    {
    
      printf("The file doesn't exist\n\n");
      continue;
    
    }
    
    uint8_t buffer[16]; //Gives the buffer aray 16 obj capacity, each obj of 1 byte (8 bits)
    
    size_t bytes_read; // Sizeof function returns a data type called size_t, hence we used size_t for bytes read for convenienc. some unsigned integer type large enough to represent object sizes
    
    size_t offset=0; // Byte offset from the beginning of the file  
    
    while ((bytes_read = fread(buffer, 1, sizeof buffer, file)) > 0)
{
    printf("%08zX  ", offset); 

    for (size_t j = 0; j < bytes_read; j++)
    {
        printf("%02X ", buffer[j]);
    }

    for (size_t j = bytes_read; j < sizeof buffer; j++)
    {
        printf("   ");
    }

    printf(" |");

    for (size_t j = 0; j < bytes_read; j++) // ASCII character print loop. Handles alignment too
    {
        if (buffer[j] >= 32 && buffer[j] <= 126)
            printf("%c", buffer[j]); 
        else
            printf(".");
    }

    printf("|\n");

    offset += bytes_read;
}
    fclose(file);
   }
}

