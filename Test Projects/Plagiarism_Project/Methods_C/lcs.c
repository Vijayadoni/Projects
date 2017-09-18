/*
Program : LCS
Author : A Vijay
Problem Description: Given n files, find the similarities between them using the longest common
sequence. 
							similarity = 2*(LCS)/Total length. 
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
char const* path;
double res[10][10];
int file_count;
char files[20][100];
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
char* get_text(char* path,char text_contents[5000]){
	FILE *fp;
	long lSize;
	fp = fopen ( path , "r" );
	if( !fp ) perror(path);
	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );
	fread( text_contents , lSize, 1 , fp); 
	text_contents[lSize] = '\0';
	modify(text_contents);
   	return text_contents;
}
/*
getSimilarity function finds all files and checks if all possible substrings of one file
exists in another file.
*/
void getSimilarity(){	
	char temp[50];
    for(int i = 0 ; i < file_count-1 ; i++){
    	for (int k = i+1; k < file_count; ++k){    		
    		char* ptr = (char*) malloc(sizeof(char)*2000);
		    char file1[5000];
		    char file2[5000];
		    char text_contents[5000];
    		strcpy(temp,path);
    		strcat(strcat(temp,"/"),files[i]);
    		strcpy(file1,get_text(temp,text_contents));
    		strcpy(temp,path);
    		strcat(strcat(temp,"/"),files[k]);
    		strcpy(file2 ,get_text(temp,text_contents));    
    		int max = 0,total = strlen(file1)+strlen(file2);
    		for(int l = 0; l < strlen(file1); ++l){
    			for (int m = strlen(file1); m > l; --m){
    				ptr = file1 + l;
    				ptr[m] = '\0';
    				if(strstr(file2,ptr) && max < strlen(ptr)) max = strlen(ptr);  //strstr(s1,s2) checks
    																			   //if s1 in s2
    			}
    		}
    		res[i][k] = (double)(2*max)/(total)*100;
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
//prints matrix form of result
void custom_print(){
	printf("Result\t\t");
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
	getFiles(argc); // gets all files
	getSimilarity(); // finds similarity between them
	custom_print(); // prints matrix
	logg();
	printf("LCS\t\t");
	/*print time stamp. */
	time_t timer;
    char buffer[26];
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);
    // -----------------//
	custom_print();
	return 0;
}