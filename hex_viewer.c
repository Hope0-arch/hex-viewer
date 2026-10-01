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
    while((bytes_read=fread(buffer,1,sizeof(buffer),file))>0)
    {
        
      for(size_t j=0;j<bytes_read;j++)
      {
    
        printf("%X ",buffer[j]);
    
      }
      printf("\n");
      }
   fclose(file);
   }
}
