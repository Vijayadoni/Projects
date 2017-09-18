/*
Program : Fingerprinting
Author : A Vijay
Problem Description: Given n files, find the similarities between them using the Fingerprinting. 
							similarity = 2*(Matching hashes)/Total length. 
File Path: ../Text_Files.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <math.h>
#include "logger.h"
#include <time.h>
// stores hash values in value and total number of hashes in total count 
struct hash{
	long value[1000],totalcount;
};
char const* path;
double res[10][10];
int file_count,k = 1;
char files[20][100];
/*
checkVal function takes a structure has and a value and returns 0 if value exists in the structure.
*/
int checkVal(struct hash this, long val){
	for (int i = 0; i < this.totalcount; ++i){
		if(this.value[i] == val) return 0;
	}
	return 1;
}
/*
makes hash values for each word according to the formula 
	value = k^p * ascii(letter 0) + k^p-1 * ascii(letter 1) + ...
	and stores unique values in structure.
*/
struct hash makeHash(char file[]){
	struct hash this;
	this.totalcount = 0;
	int j = 0;
	for (int i = 0; i < strlen(file)-k; ++i)
	{
		int count = 0;
		this.value[i] = 0;
		long temp = 0;
		while(count < k){
			temp = (long)(pow(k,count)*(int)file[i+count]); 
			count++;
		}		
		if(checkVal(this,temp)){
			this.value[j++] = temp;
			this.totalcount++;
		}
	}
	return this;
}
/*
modify function takes in a string and keeps the alphabets and numbers
*/
void modify(char* word){
	for (int i = 0; i < strlen(word); ++i) word[i] = tolower(word[i]);
	for (int i = 0; i < strlen(word); ++i){
		if(word[i] > 64 && word[i] < 91) word[i] = word[i] + 32;
		if(!((word[i] > 96 && word[i] < 123)||(word[i] > 47 && word[i] < 58))){
			if(word[i] == 32){
				for(int j = i ; j < strlen(word);j++) word[j] = word[j+1];
			}else{
				for(int j = i ; j < strlen(word);j++) word[j] = word[j+2];
			}
		}
	}
}
/*
get_text function takes in a path and puts contents of file into text_contents 
array and returns it.
*/
char* get_text(char* path,char text_contents[]){
	FILE *fp;
	long lSize;
	fp = fopen ( path , "r" );
	if( !fp ) perror(path);
	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );
	fread( text_contents , lSize, 1 , fp);
	text_contents[lSize] = '\0'; 
	fclose(fp);
	modify(text_contents);
   	return text_contents;
}
/*
getSimilarity() finds all files in a path and for each file with the other finds matches in 
hash values.
similarity = 2*matches/total * 100.
*/
void getSimilarity(){	
	char* temp = (char*) malloc(100*sizeof(char));
    char* ptr = (char*) malloc(10000*sizeof(char));
    for(int i = 0 ; i < file_count-1 ; i++){
    	for (int k = i+1; k < file_count; ++k){    		
		    char file1[10000];
		    char file2[10000];
		    char text_contents[10000];
    		strcpy(temp,path);
    		strcat(strcat(temp,"/"),files[i]);
    		strcpy(file1,get_text(temp,text_contents));
			struct hash f1 = makeHash(file1);
    		strcpy(temp,path);
    		strcat(strcat(temp,"/"),files[k]);
    		strcpy(file2 ,get_text(temp,text_contents));    
    		struct hash f2 = makeHash(file2);
    		int match = 0,total = (f1.totalcount+f2.totalcount);
    		for (int l = 0; l < f1.totalcount; ++l){
    			for (int m = 0; m < f2.totalcount; ++m){
    				if(f1.value[l] == f2.value[m] && f1.value[l] != 0) match += 1;	
    			}
    		}
    		res[i][k] = (double)2*match/total*100;
    	}
    }
}
/*
getFiles takes in the number of arguements and stores all files
*/
void getFiles(int argc){
	DIR *d;
    struct dirent *dir;
    if ( argc != 2 ) d   = opendir(".");
    else d = opendir(path);
	if (d)
	{
        while ((dir = readdir(d)) != NULL)
        {
            char* point;
            if((point = strrchr(dir->d_name,'.')) != NULL ) {
   				if(strcmp(point,".txt") == 0) {
   					strcpy(files[file_count] , dir->d_name);
          			file_count++;  
				}
  			}

        }
	}
	if(file_count == 0) printf("no files found\n");
	closedir(d);
}
// prints matrix form of result 
void custom_print(){
	printf("%s\t\t", "Result");
	for (int i = 0; i < file_count; ++i) printf("%s\t\t",files[i] );
	printf("\n");
	for (int i = 0; i < file_count; ++i){
		printf("%s\t\t",files[i]);
		for (int j = 0; j < file_count; ++j){
			if(i == j) printf("same\t\t");
			else if(i < j)printf("%.2lf\t\t", res[i][j]);
			else printf("%.2lf\t\t",res[j][i] );

		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]){
	path = (char*) malloc(100 * sizeof(char));
	path = argv[1];
	getFiles(argc); // gets files 
	getSimilarity();// finds similarity 
	custom_print(); // prints matrix
	logg(); //starts logging 
	printf("Fingerprint\t\t");
	// timestamp.
	time_t timer;
    char buffer[26];
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);
	custom_print();
	return 0;
}