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
    uint8_t buffer[16];
    size_t bytes_read;
    int offset=0;
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

    for (size_t j = 0; j < bytes_read; j++)
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
   //gcc hex-viewer/hex_viewer.c -o hex-viewer/hex_viewer
//hex-viewer/hex_viewer ~/hello.txt