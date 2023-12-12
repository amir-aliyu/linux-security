#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<CommonCrypto/CommonDigest.h>
#include<sodium.h>
#include<time.h>

#define SALT "RandomSalt123"
#define PEPPER "ThisIsASecretPepper"

char realpass[31];

void compute_hash(const char *password, const char *salt, const char *pepper, char *hashed_password);
void pickPassword(void);
void password(void);


void compute_hash(const char *password, const char *salt, const char *pepper, char *hashed_password) {
	char hashed[crypto_pwhash_STRBYTES];
	if (crypto_pwhash_str(hashed, password, strlen(password), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        // Handle error
        fprintf(stderr, "Error hashing password\n");
        exit(EXIT_FAILURE);
    }

    // Copy the hashed password to the output
    strcpy(hashed_password, hashed);

}
void pickPassword() {
	srand((unsigned int)time(NULL)); // random number generator based on current time
	int num = rand() % 4;
	char shortpass[5] = "CWRU";
	char medpass[15] = "CaseWestern";
	char longpass[31] = "CaseWesternReserveUniversity";
	// generate random number between 0 and 2 
	if (num == 4) {
		printf("its long btw \n");
		strcpy(realpass,longpass);
	} else if (num ==3) {
		printf("its medium btw \n");
		strcpy(realpass,medpass);
	} else {
		printf("its short btw \n");
		strcpy(realpass,shortpass);
	}
}

void password() {
        sleep(3);
        char pass[50];
	printf("picking a password...");
	
	pickPassword();
        
	printf("Enter a password: ");
	fgets(pass, sizeof(pass), stdin);
	pass[strcspn(pass, "\n")] = '\0';  // Remove the trailing newline	
	
	char hashed_pass[crypto_pwhash_STRBYTES];
    	compute_hash(pass, SALT, PEPPER, hashed_pass);
	
//	printf("Hashed Password: %s\n", hashed_pass);

        // compare the stored hashed password with the real password........... 
	if (crypto_pwhash_str_verify(hashed_pass, realpass, strlen(realpass)) == 0) {
	        printf("correct \n");
	} else {
		printf("incorrect, prepare for destruction \n");
		kill(getppid(), SIGKILL);
	} 

}

int main() {
	if (sodium_init() < 0) {
        // The library couldn't be initialized, it is not safe to use.
        fprintf(stderr, "Sodium initialization failed\n");
        return 1;
    }

	password();
	return 0;
}
