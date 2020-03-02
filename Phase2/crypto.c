/**
 * Copyright (C) 2018 David C. Harrison - All Rights Reserved.
 * You may not use, distribute, or modify this code without
 * the written permission of the copyright holder.
 *
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 *
 * Compile any program including this file with -lssl -lcrypto
 *
 *  gcc crypto.c -o crypto -lssl  -lcrypto
 *
 *  ./crypto
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

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)
{
    // EVP_CIPHER_CTX *ctx;
    // int c_len, f_len, plaintext_len;

    // plaintext_len = ciphertext_len;
    // if(!(ctx = EVP_CIPHER_CTX_new())) 
    //     handleErrors();

    // if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    //     handleErrors();

    // // EVP_CIPHER_CTX_set_padding(ctx,0);

    // if(1 != EVP_DecryptUpdate(ctx, plaintext, &c_len, ciphertext, plaintext_len))
    //     handleErrors();
    // // plaintext_len = len;

    // if(1 != EVP_DecryptFinal_ex(ctx, plaintext + c_len, &f_len)) 
    //     handleErrors();

    // // plaintext_len += len;
    // plaintext_len = c_len + f_len;

    // EVP_CIPHER_CTX_free(ctx);

    // return plaintext_len;
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
void do_decrypt(char *decrypt_file, char *key_file, unsigned char *iv){
    
    FILE *decrypt_open, *key_open, *out;
    unsigned char ciphertext[1024*4];
    unsigned char decryptedtext[1024*4];

    size_t offset = 32;
    unsigned char filebuff[offset];
    unsigned char key_test[1024*4];
    unsigned char key[offset+2];

    int decryptedtext_len, ciphertext_len, key_len;
    unsigned char ch;
    bool alpha;

    decrypt_open = fopen(decrypt_file, "rb");
    if (decrypt_open == NULL) {
        perror("Failed to open cipher text");
    }
    fseek(decrypt_open, 0, SEEK_END);
    ciphertext_len = ftell(decrypt_open);
    fseek(decrypt_open, 0, SEEK_SET);
    fread(&ciphertext, ciphertext_len, 1, decrypt_open);
    fclose(decrypt_open);
    
    key_open = fopen(key_file, "rb");
    if (key_open == NULL) {
        perror("Failed to open key file");
    }
    fseek(key_open, 0, SEEK_END);
    key_len = ftell(key_open);
    fseek(key_open, 0, SEEK_SET);
    fread(&key_test, key_len, 1, key_open);
    fclose(key_open);

    // while (fgets(key, sizeof(key), key_open)){
    //     key[offset] = '\0';
    for(int i = 0; i < key_len-32; i++)
    {   
        memcpy(key, &key_test[i], 32);
        decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);
        for(int i = 0; i < decryptedtext_len; i++){
            ch = decryptedtext[i];
            // if(!(isalnum(ch) == 0 || isspace(ch) == 0 || ispunct(ch) == 0 || isprint(ch) == 0)){         
            // if(isascii(decryptedtext[i]) == 0){
            if(ch < 0 || ch > 226){
                alpha = false;
                break;
            }  
            alpha = true; 
        }
        if(alpha){
            printf("Key is: %s\n", key);
            snprintf(filebuff, sizeof(char) * offset, "message.plain");
            out = fopen(filebuff, "ab");
            fwrite (decryptedtext, 1, decryptedtext_len, out);
            fwrite ("\n", 1, 1, out);
            fwrite (key, 1, offset, out);
            fclose(out);
        }
    }
    /* Add a NULL terminator. We are expecting printable text */
    // decryptedtext[decryptedtext_len] = '\0';

    // decryptedtext_len = strlen(decryptedtext)+1;
    // out = fopen("01_bfabello.message.plain", "wb");
    // fwrite (decryptedtext, 1, decryptedtext_len, out);
    // fclose(out);
    // printf("Decrypted text is:\n");
    // BIO_dump_fp (stdout, (const char *)decryptedtext, decryptedtext_len);
    // printf("decrypt before %s\n", decryptedtext);
    // return decryptedtext_len;
    // fclose(key_open);
}

int main(int argc, char *argv[])
{
    unsigned char *decrypt_file = argv[1];
    unsigned char *key_file = argv[2];
    unsigned char *iv = argv[3];
    // int counter = atoi(argv[4]);
    // int counter = *(int *)argv[4];
    // printf("%d\n", counter);
    
    do_decrypt(decrypt_file, key_file, iv);

    // unsigned char *cipher_file = "";
    // do_encrypt(cipher_file, key, iv);


}
