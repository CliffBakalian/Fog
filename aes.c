#include "aes.h"

int main(int argc, char **argv){
  char *key = "This is my very very secure key!";
  int bufSize = 32, bytes,algo = GCRY_CIPHER_AES256,keyLength = 32,blkLength = 16;
  char iniVector[32];
  char *encBuffer = NULL;
  FILE *fp, *fpout;
  gcry_cipher_hd_t hd;
  memset(iniVector, 0, 32);

  encBuffer = malloc(bufSize);
  if(strcmp(argv[1], "encrypt") == 0){

    fp = fopen(argv[2], "r");
    fpout = fopen("out", "w");

    gcry_cipher_open(&hd, algo, GCRY_CIPHER_MODE_CBC, 0);
    gcry_cipher_setkey(hd, key, keyLength);
    gcry_cipher_setiv(hd, iniVector, blkLength);
    while(!feof(fp))
    {
        bytes = fread(encBuffer, 1, bufSize, fp);
        if (!bytes) break;
        while(bytes < bufSize)
            encBuffer[bytes++] = 0x0;
        gcry_cipher_encrypt(hd, encBuffer, bufSize, NULL, 0);
        bytes = fwrite(encBuffer, 1, bufSize, fpout);
    }
    gcry_cipher_close(hd);
    fclose(fp);
    fclose(fpout);
  }else if(strcmp(argv[1], "decrypt") == 0){
    gcry_cipher_open(&hd, algo, GCRY_CIPHER_MODE_CBC, 0);
    gcry_cipher_setkey(hd, key, keyLength);
    gcry_cipher_setiv(hd, iniVector, blkLength);

    fp = fopen("out", "r");
    fpout = fopen("orgn.txt", "w");
    while(!feof(fp))
    {
        bytes = fread(encBuffer, 1, bufSize, fp);
        if (!bytes) break;
        gcry_cipher_decrypt(hd, encBuffer, bufSize, NULL, 0);
        bytes = fwrite(encBuffer, 1, bufSize, fpout);
    }
    gcry_cipher_close(hd);

    free(encBuffer); encBuffer = NULL;
  }else{
    printf("Invalid syntax\n");
  }
  return 0;
}

