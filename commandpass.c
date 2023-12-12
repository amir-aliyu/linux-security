#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<CommonCrypto/CommonDigest.h>
#include<sodium.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>

#define SALT "RandomSalt123"
#define PEPPER "ThisIsASecretPepper"

char realpass[31];

const char *prefixes[] = {"Case", "CaseWest", "CaseWestern"}; 

void compute_hash(const char *password, const char *salt, const char *pepper, char *hashed_password);
void pickPassword(const char *command);
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
void pickPassword(const char *command) {
	srand((unsigned int)time(NULL)); // random number generator based on current time

	int prefix_index;
	int num_letters;

	// highest to lowest dangerosity meter
	if(strcmp(command, "kill")==0 || strcmp(command, "rm") == 0 || strcmp(command, "chmod")== 0) {
		prefix_index = 2;
		num_letters = 11;
	} else if(strcmp(command, "cp")==0 || strcmp(command, "pwd") == 0 || strcmp(command, "wget") ==0 || strcmp(command, "ps")==0) {
		prefix_index = 1;
		num_letters = 8;
	} else if(strcmp(command, "ls")==0 || strcmp(command, "cat")==0 || strcmp(command, "mv") == 0) {
		prefix_index = 0;
		num_letters = 4;
	} else {
		num_letters = 8;
		prefix_index = 1;
	}
	
	printf("Give me the first %d letters of your password, buster!!\n", num_letters);
	strcpy(realpass, prefixes[prefix_index]);

}

void commandpass(const char *command) {
        int attempts = 0; // store number of attempts 
	
	while (attempts < 3) {
		char pass[50];
	
		pickPassword(command);
        
		printf("Enter a password: ");
		fgets(pass, sizeof(pass), stdin);
		pass[strcspn(pass, "\n")] = '\0';  // Remove the trailing newline	
	
		char hashed_pass[crypto_pwhash_STRBYTES];
	    	compute_hash(pass, SALT, PEPPER, hashed_pass);
		
	        // compare the stored hashed password with the real password........... 
		if (crypto_pwhash_str_verify(hashed_pass, realpass, strlen(realpass)) == 0) {
		        printf("correct \n");
			
			// Handle specific commands that require additional input
			 if (strcmp(command, "kill") == 0) {
				printf("Enter the PID to kill: ");
       		     		int pid;
            			scanf("%d", &pid);
		                kill(pid, SIGKILL);
      		  	} else if (strcmp(command, "cat") == 0) {
            			printf("Enter the file to display: ");
            			char file[256];
            			scanf("%s", file);
            			execlp(command, command, file, NULL);
			} else if (strcmp(command, "wget") == 0) {
            			printf("Enter the URL to download: ");
            			char url[256];
            			scanf("%s", url);
            			execlp(command, command, url, NULL);
        		} else if (strcmp(command, "rm") == 0) {
            			printf("Enter the file or directory to remove: ");
            			char target[256];
            			scanf("%s", target);
            			execlp(command, command, target, NULL);
        		} else if (strcmp(command, "mv") == 0) {
            			printf("Enter the source and destination files/directories: ");
            			char source[256], dest[256];
            			scanf("%s %s", source, dest);
            			execlp(command, command, source, dest, NULL);
       		 	} else {
        	    		// For other commands, simply execute the command
        	    		execlp(command, command, NULL);
	        	}
		return;

		} else {
			printf("incorrect, please try again\n");
			attempts++;	
		}
	} 
	printf("Too many incorrect attempts. Prepare for destruction. \n");
	kill(getppid(), SIGKILL);
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <command>\n", argv[0]);
	}
	if (sodium_init() < 0) {
	        // The library couldn't be initialized, it is not safe to use.
        	fprintf(stderr, "Sodium initialization failed\n");
        	return 1;
    	}

	commandpass(argv[1]);
	return 0;
}
