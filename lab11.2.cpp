#include <stdio.h>
#include <stdlib.h>

#define NO_SCORE 5
#define NO_STUDENT 10 

typedef struct {
    char name[16];
    char surname[20];
    int score[NO_SCORE];
    float total;
} Student;

void readStudentData(Student *);
void findTotalScore(Student *);
float findAverage(Student);
void findLessThanTen(Student);

int main() {
    Student std[NO_STUDENT];
    int i;
    FILE *fp;
    for (i = 0; i < NO_STUDENT; i++) {
        printf("\n--- Student #%d ---\n", i + 1);
        readStudentData(&std[i]);
    }
    fp = fopen(".\\lab11\\no2\\lab11.2.cpp", "wb"); 
    if (fp == NULL) {
        printf("\nError: Cannot create file! (Check if folder exists)\n");
        return 1;
    }
    fwrite(std, sizeof(Student), NO_STUDENT, fp);
    fclose(fp);
    printf("\n[System] Data saved to lab11.2.cpp successfully.\n");
    Student readStd[NO_STUDENT];
    fp = fopen(".\\lab11\\no2\\lab11.2.cpp", "rb");
    if (fp != NULL) {
        fread(readStd, sizeof(Student), NO_STUDENT, fp);
        fclose(fp);
        printf("\n======= SHOWING STUDENT DATA FROM FILE =======");
        for (i = 0; i < NO_STUDENT; i++) {
            findTotalScore(&readStd[i]); 
            float avg = findAverage(readStd[i]);
            printf("\n\tAverage score is %.2f", avg);
            findLessThanTen(readStd[i]);
            printf("\n--------------------------------------------");
        }
    }
    return 0;
}

void readStudentData(Student *pStd) {
    int i;
    printf("\tName : ");
    scanf("%s", pStd->name);
    printf("\tSurname : ");
    scanf("%s", pStd->surname);
    for (i = 0; i < NO_SCORE; i++) {
        printf("\tScore %d : ", i + 1);
        scanf("%d", &pStd->score[i]);
    }
}

void findTotalScore(Student *pStd) {
    int i;
    printf("\n\n%s %s", pStd->name, pStd->surname);
    printf("\n\tScores: ");
    pStd->total = 0.0;
    for (i = 0; i < NO_SCORE; i++) {
        printf("%4d", pStd->score[i]);
        pStd->total += pStd->score[i];
    }
    printf("\n\tTotal Score: %.2f", pStd->total);
}

float findAverage(Student s) {
    return (s.total / NO_SCORE);
}

void findLessThanTen(Student s) {
    int i, count = 0;
    printf("\n\tScore less than 10:");
    for (i = 0; i < NO_SCORE; i++) {
        if (s.score[i] < 10) {
            printf(" [Test %d: %d]", i + 1, s.score[i]);
            count++;
        }
    }
    if (count == 0) printf(" None");
}

