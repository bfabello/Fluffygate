#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <crypt.h>

/*
 * Find the plain-text password PASSWD of length PWLEN for the user USERNAME 
 * given the encrypted password CRYPTPASSWD.
 */
void crackSingle(char *username, char *cryptPasswd, int pwlen, char *passwd) { 
	
  	const char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char salt[2 + 1] = {0};
	char key[14];

	for(int i = 0; i < 62; i++){
		for(int j = 0; j < 62; j++){
			for(int k = 0; k < 62; k++){
				for(int l = 0; l < 62; l++){
					passwd[0] = alphabet[i];
					passwd[1] = alphabet[j];
					passwd[2] = alphabet[k];
					passwd[3] = alphabet[l];

					strncpy(salt, username, 2);
					sprintf(key, "%s", crypt(passwd, salt));
                	printf("%s\n", key);
					bool passed = strcmp(key, cryptPasswd) == 0;

				    if (passed){
				        return;	
				    }
				}
			}
		}

	}
}

/*
 * Find the plain-text passwords PASSWDS of length PWLEN for the users found
 * in the old-style /etc/passwd format file at pathe FNAME.
 */
void crackMultiple(char *fname, int pwlen, char **passwds) { 
	
	char username[16];
	char cryptPasswd[14];;
	char line[64];

	FILE *fin = fopen(fname, "r");
	for (int i = 0; fgets(line, 64, fin) != NULL; i++) {
        sprintf(username, "%s", strtok(line, ":"));
        sprintf(cryptPasswd, "%s", strtok(strtok(NULL, ":"), "\n"));
        crackSingle(username, cryptPasswd, pwlen, passwds[i]);
    }
    fclose(fin);
} 

/*
 * Find the plain-text passwords PASSWDS of length PWLEN for the users found
 * in the old-style /etc/passwd format file at pathe FNAME.
 */
void crackSpeedy(char *fname, int pwlen, char **passwds) { 
	crackMultiple(fname, pwlen, passwds); 
}

/*
 * Find the plain-text password PASSWD of length PWLEN for the user USERNAME 
 * given the encrypted password CRYPTPASSWD withoiut using more than MAXCPU
 * percent of any processor.
 */
void crackStealthy(char *username, char *cryptPasswd, int pwlen, char *passwd, int maxCpu) { 
    crackSingle(username, cryptPasswd, pwlen, passwd);
}
