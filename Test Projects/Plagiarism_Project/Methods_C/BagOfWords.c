/*
Program : Bag Of Words
Author : A Vijay
Problem Description: Given n files, find the similarities between them using the common word matches.
 							similarity = arccos(dot product)/ magnitude 
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
/*
wordList structure -> Holds 1000 words each with 100 letters max.
The I'th word has the I'th frequency.
Variable totalcount stores the total number of words.
*/
struct wordsList{
	char word[1000][100];
	int frequency[1000],totalcount;
};
char const* path; //files path.
double res[100][100]; // stores the result.
int file_count; // stores the number of text files present.
char files[20][100]; // stores the text files.
/*
getindex function takes in 2 parameters -> 1. the wordList structure corresponding to each file, 
and 2. the word to find in the structure.
getindex returns the index of structure where word exists.
*/
int getindex(struct wordsList this,char* word){
	for (int i = 0; i < this.totalcount; ++i){
		if(strcmp(this.word[i],word) == 0) return i;
	}
	return -1;
}
//Takes a string and removes all characters except alphabets and numbers
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
collectFrequency takes a path and open the text file.
stores words in wordList structure.
*/
struct wordsList collectFrequency(char* path){
	FILE *fp;
	char words[1000][100]; // stores all possible words.
	char temp_word[100];
	struct wordsList word;
	word.totalcount = 0;
	int word_count = 0;
	fp=fopen(path,"r");
	while(!feof(fp)){
		fscanf(fp,"%s",temp_word);
		modify(temp_word);
		strcpy(words[word_count++],temp_word); // copies temp_word to words[word_count] and increments word_count
	}	
	fclose(fp);
	for (int i = 0; i < word_count; ++i){
	    	if(getindex(word,words[i]) == -1){
	    		word.frequency[word.totalcount] = 1;
	    		strcpy(word.word[word.totalcount++],words[i]);
	    	}
	    	else word.frequency[getindex(word,words[i])]++;

	}
   	return word;
}

/*
mod function takes a structure and returns the magnitude.
*/
int mod(struct wordsList this){
	int sum = 0;
	for (int i = 0; i < this.totalcount; ++i) sum += pow(this.frequency[i],2);
	return sum;
}
/*
		getSimilarity function finds the distance between the vectors of all files with each other.
		similarity = dot product / magnitude.
*/
void getSimilarity(){	
    for(int i = 0 ; i < file_count-1 ; i++){
    	for (int k = i+1; k < file_count; ++k){
    		int dotproduct = 0;
    		char* temp = (char*) malloc(100*sizeof(char));
    		strcpy(temp,path);
    		strcat(strcat(temp,"/"),files[i]);
    		struct wordsList f1 = collectFrequency(temp);
    		strcpy(temp,path);
    		strcat(strcat(temp,"/"),files[k]);
    		struct wordsList f2 = collectFrequency(temp);
    		for (int l = 0; l < f1.totalcount; ++l){
    			for (int m = 0; m < f2.totalcount; ++m){
    				if(strcmp(f1.word[l],f2.word[m]) == 0) dotproduct += f1.frequency[l]*f2.frequency[m];
    			}
    		}
    		double t = (dotproduct)/(sqrt(mod(f1)*mod(f2)))*100;
    		res[i][k] = t;
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
/*
Prints matrix format!
*/
void custom_print(){
	printf("%s\t\t", "Result");
	for (int i = 0; i < file_count; ++i) printf("%s\t\t",files[i] );
	printf("\n");
	for (int i = 0; i < file_count; ++i)
	{
		printf("%s\t\t",files[i]);
		for (int j = 0; j < file_count; ++j)
		{
			if(i == j) printf("same\t\t");
			else if(i < j)printf("%.2lf\t\t", res[i][j]);
			else printf("%.2lf\t\t",res[j][i] );
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]){
	path = (char*) malloc(100 * sizeof(char));
	path = argv[1]; // stores command line arguements in path
	getFiles(argc); //gets files
	getSimilarity(); // finds the similarity
	custom_print(); // prints matrix.
	logg(); // starts logging
	/*
			All display elements stored in txt file.
		*/
	printf("BAG OF WORDS\t\t");
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