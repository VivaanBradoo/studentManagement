#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    int prnNo;
    char name[50];
    char department[30];
    char section[10];
    char email[50];
    char mobile[20];
    float gpa;
};

#define FILE_NAME "students.txt"

void addStudent();
void viewStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add New Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by PRN No\n");
        printf("4. Modify Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: modifyStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    char temp[100];

    printf("Enter Roll No: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &s.rollNo);

    printf("Enter PRN No: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%d", &s.prnNo);

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Department: ");
    fgets(s.department, sizeof(s.department), stdin);
    s.department[strcspn(s.department, "\n")] = 0;

    printf("Enter Section: ");
    fgets(s.section, sizeof(s.section), stdin);
    s.section[strcspn(s.section, "\n")] = 0;

    printf("Enter Email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    printf("Enter Mobile: ");
    fgets(s.mobile, sizeof(s.mobile), stdin);
    s.mobile[strcspn(s.mobile, "\n")] = 0;

    printf("Enter GPA: ");
    fgets(temp, sizeof(temp), stdin);
    sscanf(temp, "%f", &s.gpa);

    fprintf(fp, "%d,%d,%s,%s,%s,%s,%s,%.2f\n",
            s.rollNo, s.prnNo, s.name, s.department,
            s.section, s.email, s.mobile, s.gpa);

    fclose(fp);
    printf("Student added successfully!\n");
}


void viewStudents() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No students found.\n");
        return;
    }

    struct Student s;
    printf("\n%-6s %-8s %-20s %-15s %-7s %-25s %-15s %-5s\n",
           "Roll", "PRN", "Name", "Dept", "Sec", "Email", "Mobile", "GPA");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    // printf("%d",fscanf(fp, "%d,%d,%49[^,],%29[^,],%5[^,],%49[^,],%19[^,],%f",
    //               &s.rollNo, &s.prnNo, s.name, s.department,
    //               s.section, s.email, s.mobile, &s.gpa));

    while (fscanf(fp, "%d,%d,%49[^,],%29[^,],%5[^,],%49[^,],%19[^,],%f",
                  &s.rollNo, &s.prnNo, s.name, s.department,
                  s.section, s.email, s.mobile, &s.gpa) == 8) {
        printf("%-6d %-8d %-20s %-15s %-7s %-25s %-15s %-5.2f\n",
               s.rollNo, s.prnNo, s.name, s.department,
               s.section, s.email, s.mobile, s.gpa);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No students found.\n");
        return;
    }

    int prn;
    int found = 0;
    struct Student s;

    printf("Enter PRN No to search: ");
    scanf("%d", &prn);

    while (fscanf(fp, "%d,%d,%49[^,],%29[^,],%1[^,],%49[^,],%19[^,],%f\n",
                  &s.rollNo, &s.prnNo, s.name, s.department,
                  s.section, s.email, s.mobile, &s.gpa) == 8) {
        if (s.prnNo == prn) {
            printf("\nStudent Found:\n");
            printf("Roll No: %d\n", s.rollNo);
            printf("PRN No: %d\n", s.prnNo);
            printf("Name: %s\n", s.name);
            printf("Department: %s\n", s.department);
            printf("Section: %s\n", s.section);
            printf("Email: %s\n", s.email);
            printf("Mobile: %s\n", s.mobile);
            printf("GPA: %.2f\n", s.gpa);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    fclose(fp);
}

void modifyStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No students found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    int roll, found = 0;
    struct Student s;

    printf("Enter Roll No to modify: ");
    scanf("%d", &roll);
    getchar();

    while (fscanf(fp, "%d,%d,%49[^,],%29[^,],%1[^,],%49[^,],%19[^,],%f\n",
                  &s.rollNo, &s.prnNo, s.name, s.department,
                  s.section, s.email, s.mobile, &s.gpa) == 8) {
        if (s.rollNo == roll) {
            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter New Department: ");
            fgets(s.department, sizeof(s.department), stdin);
            s.department[strcspn(s.department, "\n")] = 0;

            printf("Enter New Section: ");
            fgets(s.section, sizeof(s.section), stdin);
            s.section[strcspn(s.section, "\n")] = 0;

            printf("Enter New Email: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = 0;

            printf("Enter New Mobile: ");
            fgets(s.mobile, sizeof(s.mobile), stdin);
            s.mobile[strcspn(s.mobile, "\n")] = 0;

            printf("Enter New GPA: ");
            scanf("%f", &s.gpa);
            found = 1;
        }

        fprintf(temp, "%d,%d,%s,%s,%s,%s,%s,%.2f\n",
                s.rollNo, s.prnNo, s.name, s.department,
                s.section, s.email, s.mobile, s.gpa);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Student modified successfully.\n");
    else
        printf("Student not found.\n");
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No students found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    int prn, found = 0;
    struct Student s;

    printf("Enter Roll No to delete: ");
    scanf("%d", &prn);

    while (fscanf(fp, "%d,%d,%49[^,],%29[^,],%1[^,],%49[^,],%19[^,],%f\n",
                  &s.rollNo, &s.prnNo, s.name, s.department,
                  s.section, s.email, s.mobile, &s.gpa) == 8) {
        if (s.prnNo != prn) {
            fprintf(temp, "%d,%d,%s,%s,%s,%s,%s,%.2f\n",
                    s.rollNo, s.prnNo, s.name, s.department,
                    s.section, s.email, s.mobile, s.gpa);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}
