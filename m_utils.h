#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define pInt(a) printf("%d", a);
#define pFloat(a) printf("%f", a);
#define nl printf("\n");
#define m_array(length, type) calloc(length, sizeof(type))

#define BSIZE 1
#define SSIZE 2
#define ISIZE 4
#define FSIZE 4
#define DSIZE 8
#define UBSIZE 1
#define USSIZE 4
#define UISIZE 8

#ifndef M_PI
#define M_PI 3.14159
#endif

char * strplus(char * a, char * b){
	if(a == NULL){
		a = (char*)calloc(1, sizeof(char));
	}

	char * ret = (char*)calloc(strlen(a) + strlen(b), sizeof(char));
	strcat(ret, a);
	strcat(ret, b);

	return ret;
}

char * ReadLine(FILE * f){
	char * ret = NULL;
	unsigned int i = 1;
	char c = 0;
	int pos = ftell(f);
	while(c != '\n'){
		c = fgetc(f);
		i++;
	}
	fseek(f, pos, SEEK_SET);
	ret = (char*)calloc(i, sizeof(char));
	fgets(ret, i, f);
	return ret;
}

float degree(float radians){
	return radians * 180 / M_PI;
}

float radians(float degree){
	return degree * M_PI / 180;
}

char * ReadFile(const char * fileName){
	FILE * f = fopen(fileName, "r");
	if(f == NULL){
		printf("File %s was not founded", fileName);nl;
		return NULL;
	}
	char * text = NULL;
	char c = 0;
	unsigned int counter = 0;
	while(c != EOF){
		counter++;
		c = fgetc(f);
		text = (char*)realloc(text, sizeof(char)*counter);
		text[counter-1] = c;
	}
	fclose(f);
	return text;
}

