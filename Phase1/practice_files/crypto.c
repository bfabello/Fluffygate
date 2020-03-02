/**
 * Copyright (C) 2018 David C. Harrison - All Rights Reserved.
 * You may not use, distribute, or modify this code without
 * the written permission of the copyright holder.
 *
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 *
 * Compile any program including this file with -lssl -lcrypto
 */

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "crypto.h"

static void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
    unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) 
        handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    // EVP_CIPHER_CTX_set_padding(ctx,0);

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) 
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
    unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) 
        handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    EVP_CIPHER_CTX_set_padding(ctx,0);

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) 
        handleErrors();

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
/* Encrypt the plaintext */
void do_encrypt(char *file, char *key, char *iv){
    
    FILE *in, *out;
    int plaintext_len, ciphertext_len;
    unsigned char ciphertext[1024*4];
    unsigned char plaintext[1024*4];

    in = fopen(file, "rb");
    if (in == NULL) {
        perror("Failed to open");
    }
    fseek(in, 0, SEEK_END);
    plaintext_len = ftell(in);
    fseek(in, 0, SEEK_SET);
    fread(&plaintext, plaintext_len, 1, in);
    fclose(in);

     /* Encrypt the plaintext */
    ciphertext_len = encrypt(plaintext, plaintext_len, key, iv, ciphertext);
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
    
    out = fopen("message.ciphertext", "wb");
    fwrite (ciphertext, 1, ciphertext_len, out);
    fclose(out);
}       
int do_decrypt(char* decryptedtext, char *file, char *key, char *iv){
    
    FILE *in, *out;
    unsigned char ciphertext[1024*4];
    int decryptedtext_len, ciphertext_len;
    unsigned char ch;
    
    in = fopen(file, "rb");
    if (in == NULL) {
        perror("Failed to open");
    }
    fseek(in, 0, SEEK_END);
    ciphertext_len = ftell(in);
    fseek(in, 0, SEEK_SET);
    fread(&ciphertext, ciphertext_len, 1, in);
    fclose(in);
    
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';
    return decryptedtext_len;
    // out = fopen("phase3.message1_0.plain", "wb");
    // fwrite (decryptedtext, 1, strlen(decryptedtext), out);
    // fclose(out);
    // printf("Decrypted text is:\n");
    // BIO_dump_fp (stdout, (const char *)decryptedtext, decryptedtext_len);
    // printf("%s\n", decryptedtext);
    // printf("%s\n", "DECRYPTED");
    // for(int i = 0; i < strlen(decryptedtext); i++){
    //     ch = decryptedtext[i];
    //     if(ch < 0 || ch > 127){
    //         printf("%d ", ch);    
    //     }
    // }
}

void find_key(char *decryptedtext, char *iv, char *keyfile, char *decryptfile){
    
    FILE *in, *out;
    unsigned char filebuff[32];
    unsigned char key_test[1024];
    unsigned char key[32+1];
    int key_len, decryptedtext_len, file_count;
    bool alpha;
    unsigned char ch;

    in = fopen(keyfile, "rb");
    fseek(in, 0, SEEK_END);
    key_len = ftell(in);
    fseek(in, 0, SEEK_SET);
    fread(&key_test, key_len, 1, in);
    fclose(in);

    for(int i = 0; i < key_len-32; i++)
    {   
        memcpy(key, &key_test[i], 32);
        decryptedtext_len = do_decrypt(decryptedtext, decryptfile, key, iv);
        // for(int i = 0; i < strlen(decryptedtext); i++){
        //     // ch = decryptedtext[i];
        //     // if(!(isalnum(ch) == 0 || isspace(ch) == 0 || ispunct(ch) == 0 || isprint(ch) == 0)){
        //     if(isascii(decryptedtext[i]) == 0){
        //         alpha = false;
        //         break;
        //     }  
        //     alpha = true; 
        // }
        // if(alpha){
            snprintf(filebuff, sizeof(char) * 32, "%i_message.plain", file_count);
            out = fopen(filebuff, "wb");
            fwrite (decryptedtext, 1, decryptedtext_len, out);
            fwrite ("\n", 1, 1, out);
            fwrite (key, 1, strlen(key), out);
            fclose(out);
            file_count++;
        // }
    }
}
void main()
{
    // unsigned char *key = (unsigned char *)"4E000F471E8B5F2C4D7049C49450EB9A";
    unsigned char *iv = (unsigned char *)"E7C6357864F322AF2EC892CC2D4E4EBA";
    unsigned char *decrypt_file = "/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase1/practice_files/message.cipher";
    unsigned char *key_file = "/afs/cats.ucsc.edu/users/y/bfabello/CMPS122/Lab3/Phase1/practice_files/key";
    unsigned char decryptedtext[1024*4];

    // do_encrypt(cipher_file, key, iv);
    // do_decrypt(decryptedtext, decrypt_file, key, iv);
    find_key(decryptedtext, iv, key_file, decrypt_file);
}
