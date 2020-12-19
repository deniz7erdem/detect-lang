#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>


const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][8]={"english", "german"};

//�ngilizce dilinin frekans de�erleri
 const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
 //Almanca dilinin frekans de�erleri
 const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float calculated_frequencies[20];
float distances [2]={0,0};


void filter_str(char str[]);
void calculate_frequencies_bi(char str[]);
void calculate_frequencies_tri(char str[]);
void calculate_distances();
void detect_lang();

int main()
{

    printf("Lutfen metini giriniz:\n");
    char metin[1000];
    gets(metin);
    filter_str(metin);
    calculate_frequencies_bi(metin);
    calculate_frequencies_tri(metin);
    calculate_distances();
    detect_lang();

    return 0;
}

void filter_str(char str[]){
    puts("\n#########################################\n");
    puts("Metin islenmeye uygun hale getiriliyor...\n");
    puts("#########################################\n");
    for(int i = 0; i<strlen(str);i++){
        str[i]= tolower(str[i]);
        int c = str[i];
        if((c<97) || (c>122)){
            str[i]=32;
        }
    }
    str[strlen(str)+1]="\0";
    puts(str);
}

void calculate_frequencies_bi(char str[]){
    puts("\n#########################################\n");
    puts("Metin taraniyor...\n");
    puts("#########################################\n");
    puts("Bigram frekanslari\n");
    int sayac=0;
    sayac=sayac+1;

    for(int a=0; a<10;a++){

        for (int i = 0; i < strlen(str); ++i)
        {
            if (strncmp (&str[i], matrix_bigram_strings[a], strlen(matrix_bigram_strings)) == 0)
            {

                calculated_frequencies[a]=calculated_frequencies[a]+1;

                sayac=sayac+1;
            }
        }
    }
    for (int i = 0; i < 10; i++)
    {
        calculated_frequencies[i]=calculated_frequencies[i]/sayac*10;
        printf("%s bigraminin frekansi %.2f\n", matrix_bigram_strings[i], calculated_frequencies[i]);
    }
}


void calculate_frequencies_tri(char str[]){
    puts("\n#########################################\n");
    puts("Bigram frekanslari\n");
    int sayac=0;
    int tri= 10;
    int yaz=0;
    sayac=sayac+1;

    for(int a=0; a<10;a++){

        for (int i = 0; i < strlen(str); ++i)
        {
            if (strncmp (&str[i], matrix_trigram_strings[a], strlen(matrix_bigram_strings)) == 0)
            {

                calculated_frequencies[tri]=calculated_frequencies[tri]+1;

                sayac=sayac+1;
            }
        }
        tri++;
    }
    for (int i = 10; i < 20; i++)
    {
        calculated_frequencies[i]=calculated_frequencies[i]/sayac*10;
        printf("%s trigraminin frekansi %.2f\n", matrix_trigram_strings[yaz], calculated_frequencies[i]);
        yaz++;
    }
}

//###################################################################################
//###################################################################################
//###################################################################################
void calculate_distances(){

    for(int i=0;i<20;i++){

      distances[0]=distances[0]+fabs(calculated_frequencies[i]-frequency_eng[i]);
      distances[1]=distances[1]+fabs(calculated_frequencies[i]-frequency_germ[i]);
    }
        puts("\n#########################################");

       printf("\nIngilizce ile farki:%f\tAlmanca ile farki:%f",distances[0],distances[1]);
}


void detect_lang(){

    puts("\n#########################################\n");

 if(distances[0]>distances[1]){
    printf("Girdiginiz metin Almancadir.");
 }
 else if(distances[0]<distances[1]){
    printf("Girdiginiz metin Ingilizcedir.");
 }

 else{
    printf("Metin dili tanimlanamadi.");
 }
}
