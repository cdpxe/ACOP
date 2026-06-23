#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000 // number of characters for output
#define ts 40 // number of secret message symbols

void restart(unsigned int *freq,int size){
	for(int i=0;i<size;i++) freq[i] = 0;
}

// returns value in 0...39 if valid symbol, -1 otherwise
int check(char c){
	int result = -1;
	
	c = toupper(c);
	if(c == 32) result = 0;
	else
	if(c == 44) result = 1;
	else
	if(c == 46) result = 2;
	else
	if((c >= 48) && (c <= 57)) result = (int)c - 45;
	else
	if(c == 63) result = 13;
	else
	if((c >= 65) && (c <= 90)) result = (int)c - 51;
	
	return result;
}

// initialize zipf distribution
void initzipf(double* prob,int size){
double sum;

	for(int i=0;i<size;i++) prob[i]=1/(double)i;
	sum = 0;
	for(int i=size-1;i>=0;i--) sum += prob[i]; // sum from smaller to larger to avoid rounding if possible
	for(int i=0;i<size;i++) prob[i] = prob[i] / sum;
}

// Kullback-Leibler divergence
double computekldiv(double* pp,double* pq,int size){
	double result;
	
	for(int i=0;i<size;i++) result += pp[i] * log2(pp[i]/pq[i]);
	
	return result;
}


// for descending order
int cmpfunc(const void *a, const void *b) {
return ((int)*(unsigned int *)b - (int)*(unsigned int *)a);
}
}

// check how much actual distribution deviates from assumed zipf distribution
void checkfrequencies(unsigned int *freq,int size,int totalnum){
double probp[ts];
double probq[ts];
double kldiv;

	qsort(freq,size,sizeof(unsigned int),cmpfunc);
	for(int i=0;i<ts;i++) probq[i] = (double)freq[i]/(double)totalnum;
	initzipf(probp,ts);
	kldiv = computekldiv(probp,probq,ts);
	
	printf(stderr,"size Sigma_s = %d\n",size);
	printf(stderr,"Textsample of size %d has Kullback-Leibler divergence %lf from Zipf distribution\n",totalnum,kldiv);
	for(int i=0;i<ts;i++) printf(stderr,"%lf ",probq[i]);
	printf(stderr,"\n");
	
}

int main(int argc,char *argv[]){
FILE *fin;
FILE *fout;
char sym;
int symindex;
unsigned int frequencies[ts];
int cnt;

    restart(frequencies,ts)
	fin = stdin;
	fout = stdout;

	cnt = 0;
	while(!EOF(fin)){
		fscanf(fin,"%c",&sym);
		symindex = check(sym);
		if(symindex >= 0){
			frequencies[symindex]++;
			fprintf(fout,"%02d ",symindex);
			cnt++;
			if(!(cnt % 10)) fprintf(fout,"\n");
		}
		if(cnt == N) break;
	}
	fclose(fin);
	fclose(fout);
	
	checkfrequencies(frequencies,ts,cnt);

	return 0;
}
