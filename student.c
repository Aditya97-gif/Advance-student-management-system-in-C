#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student{
    char name[20];
    int age;
    float sciencescore;
    float mathscore;
    float englishscore;
    float averagescore;
    int studentid;
    float balancefee;
};
void addstudent(){
    struct student s;
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter age: ");
    scanf("%d", &s.age);
    printf("Enter science score: ");
    scanf("%f", &s.sciencescore);
    printf("Enter math score: ");
    scanf("%f", &s.mathscore);
    printf("Enter english score: ");
    scanf("%f", &s.englishscore);
    s.averagescore = (s.sciencescore + s.mathscore + s.englishscore) / 3;
    printf("Enter student ID: ");
    scanf("%d", &s.studentid);
    printf("Enter balance fee: ");
    scanf("%f", &s.balancefee);
    
    FILE *fp = fopen("students.txt", "a");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s %d %.2f %.2f %.2f %.2f %d\n", s.name, s.age, s.sciencescore, s.mathscore, s.englishscore, s.averagescore, s.studentid);
    fclose(fp);
    printf("Student added successfully!\n");
}
void viewstudents(){
    struct student s;
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    printf("Name\tAge\tScience\tMath\tEnglish\tAverage\tID\n");
    while(fscanf(fp, "%s %d %f %f %f %f %d", s.name, &s.age, &s.sciencescore, &s.mathscore, &s.englishscore, &s.averagescore, &s.studentid) != EOF){
        printf("%s\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\n", s.name, s.age, s.sciencescore, s.mathscore, s.englishscore, s.averagescore, s.studentid);
    }
    fclose(fp);
}
void searchstudent(){
    char name[20];
    struct student s;
    int found = 0;
    int tempid;
    printf("Enter studentid to search: ");
    scanf("%d", &tempid);
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL){
        printf("Error opening file!\n");
        return; 
    }
    else{
        while(fscanf(fp, "%s %d %f %f %f %f %d", s.name, &s.age, &s.sciencescore, &s.mathscore, &s.englishscore, &s.averagescore, &s.studentid) != EOF){
            if(tempid == s.studentid){
                printf("Name: %s\nAge: %d\nScience Score: %.2f\nMath Score: %.2f\nEnglish Score: %.2f\nAverage Score: %.2f\nStudent ID: %d\n", s.name, s.age, s.sciencescore, s.mathscore, s.englishscore, s.averagescore, s.studentid);
                found = 1;
                break;
            }
        }
        if(!found){
            printf("Student not found!\n");
        }
    }
    fclose(fp);
}
void deletestudent(){
    char name[20];
    struct student s;
    int found = 0;
    printf("Enter name to delete: ");
    scanf("%s", name);
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL){
        printf("Error opening file!\n");
        fclose(fp);
        return;
    }
    while(fscanf(fp, "%s %d %f %f %f %f %d", s.name, &s.age, &s.sciencescore, &s.mathscore, &s.englishscore, &s.averagescore, &s.studentid) != EOF){
        if(strcmp(s.name, name) == 0){
            found = 1;
            continue;
        }
        fprintf(temp, "%s %d %.2f %.2f %.2f %.2f %d\n", s.name, s.age, s.sciencescore, s.mathscore, s.englishscore, s.averagescore, s.studentid);
    }
    fclose(fp);
    fclose(temp);
    if(found){
        remove("students.txt");
        rename("temp.txt", "students.txt");
        printf("Student deleted successfully!\n");
    }else{
        remove("temp.txt");
        printf("Student not found!\n");
    }
}


int main(){
    int p=1;
    while(p){
        int choice;
        printf("1. Add Student\n2. View Students\n3. Search Student\n4. Delete Student\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                addstudent();
                break;
            case 2:
                viewstudents();
                break;
            case 3:
                searchstudent();
                break;
            case 4:
                deletestudent();
                break;
            case 5:
                p=0;
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}