#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent(FILE *fp);
void viewStudents(FILE *fp);
void searchStudent(FILE *fp);
void deleteStudent(FILE *fp);

int main() {
    FILE *fp;
    int choice;

    while(1) {
        printf("\n--- Student Record Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        fp = fopen("students.dat", "ab+");

        switch(choice) {
            case 1:
                addStudent(fp);
                break;
            case 2:
                viewStudents(fp);
                break;
            case 3:
                searchStudent(fp);
                break;
            case 4:
                deleteStudent(fp);
                break;
            case 5:
                fclose(fp);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }

        fclose(fp);
    }

    return 0;
}

void addStudent(FILE *fp) {
    struct Student s;
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(s), 1, fp);
    printf("Student added successfully!\n");
}

void viewStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    printf("\n--- All Student Records ---\n");

    while(fread(&s, sizeof(s), 1, fp) == 1) {
        printf("Roll No: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
    }
}

void searchStudent(FILE *fp) {
    struct Student s;
    int roll, found = 0;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);
    rewind(fp);

    while(fread(&s, sizeof(s), 1, fp) == 1) {
        if(s.roll == roll) {
            printf("Student Found!\n");
            printf("Roll No: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found.\n");
}

void deleteStudent(FILE *fp) {
    struct Student s;
    FILE *temp;
    int roll, found = 0;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    temp = fopen("temp.dat", "wb");
    rewind(fp);

    while(fread(&s, sizeof(s), 1, fp) == 1) {
        if(s.roll != roll)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Record deleted successfully.\n");
    else
        printf("Record not found.\n");
}

