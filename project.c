#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the starting ID values for employees and customers
int lastEmployeeID = 1000;
int lastCustomerID = 1000;

typedef struct User {
    char id[9];
    char name[50];
    struct User *next;
} User;

typedef struct CustomerComplaint {
    char id[9];
    char name[50];
    char complaint[200];
    struct CustomerComplaint *next;
    struct CustomerComplaint *prev;
} CustomerComplaint;

// Linked lists for employees and customers
User *emplisthead = NULL;
User *custlisthead = NULL;

// Deque pointers for customer complaints
CustomerComplaint *front = NULL;
CustomerComplaint *rear = NULL;

// Function to create a new user
User* createUser(char *id, char *name) {
    User *newUser = (User *)malloc(sizeof(User));
    strcpy(newUser->id, id);
    strcpy(newUser->name, name);
    newUser->next = NULL;
    return newUser;
}

// Function to add a user to the list (employee or customer)
User* addUser(User *list, char *id, char *name) {
    User *newUser = createUser(id, name);
    newUser->next = list;
    list = newUser;
    printf("Account created successfully with ID: %s\n", id);
    return list;  // Return the updated list
}

// Function to create a new complaint
CustomerComplaint* createComplaintNode(char *id, char *name, char *complaint) {
    CustomerComplaint *newComplaint = (CustomerComplaint *)malloc(sizeof(CustomerComplaint));
    strcpy(newComplaint->id, id);
    strcpy(newComplaint->name, name);
    strcpy(newComplaint->complaint, complaint);
    newComplaint->next = NULL;
    newComplaint->prev = NULL;
    return newComplaint;
}

// Function to add a complaint at the front
void ProductComplaints(CustomerComplaint *newComplaint) {
    if (front == NULL) {
        front = rear = newComplaint;
    } else {
        newComplaint->next = front;
        front->prev = newComplaint;
        front = newComplaint;
    }
    printf("Complaint added to the front.\n\n");
}

// Function to add a complaint at the rear
void ServiceComplaint(CustomerComplaint *newComplaint) {
    if (rear == NULL) {
        front = rear = newComplaint;
    } else {
        newComplaint->prev = rear;
        rear->next = newComplaint;
        rear = newComplaint;
    }
    printf("Complaint added to the rear.\n\n");
}

// Display all complaints for a given customer ID
void displayComplaints(char *id) {
    CustomerComplaint *current = front;
    int found = 0;
    printf("\nComplaints for Customer ID %s:\n", id);
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            printf("Complaint: %s\n", current->complaint);
            found = 1;
        }
        current = current->next;
    }
    printf("\n");
    if (!found) printf("No complaints found for this customer ID.\n\n");
}

// Function to process a complaint from the front
void processComplaintFront() {
    if (front == NULL) {
        printf("No complaints to process.\n\n");
        return;
    }
    CustomerComplaint *processed = front;
    printf("Processing complaint for ID %s: %s\n\n", processed->id, processed->complaint);
    front = front->next;
    if (front) front->prev = NULL;
    else rear = NULL;
    free(processed);
}

// Function to process a complaint from the rear
void processComplaintRear() {
    if (rear == NULL) {
        printf("No complaints to process.\n\n");
        return;
    }
    CustomerComplaint *processed = rear;
    printf("Processing complaint for ID %s: %s\n\n", processed->id, processed->complaint);
    rear = rear->prev;
    if (rear) rear->next = NULL;
    else front = NULL;
    free(processed);
}

// Search for a user in the list by ID and Name
User* searchUser(User *head, char *id, char *name) {
    User *current = head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0 && strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int main() {
    int choice;
    char id[9], name[50], complaint[200];
    char ch;
    User *user;

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {  // Login
            printf("Enter your ID: ");
            scanf("%s", id);
            printf("Enter your name: ");
            scanf(" %[^\n]", name);  // to allow spaces in the name

            if (strncmp(id, "EMP-", 4) == 0) {  // Employee login
                user = searchUser(emplisthead, id, name);
                if (user) {
                    printf("Welcome, %s. (Employee)\n", user->name);
                    while (1) {
                        printf("1. Process Complaint from Front\n");
                        printf("2. Process Complaint from Rear\n");
                        printf("3. Search Customer Complaints by ID\n");
                        printf("4. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        if (choice == 1) processComplaintFront();
                        else if (choice == 2) processComplaintRear();
                        else if (choice == 3) {
                            printf("Enter Customer ID to search complaints: ");
                            scanf("%s", id);
                            displayComplaints(id);
                        } else if (choice == 4) {
                            printf("Logging out.\n");
                            break;
                        } else {
                            printf("Invalid choice. Try again.\n");
                        }
                    }
                } else {
                    printf("Employee ID and Name do not match.\n");
                }
            } else {  // Customer login
                user = searchUser(custlisthead, id, name);
                if (user) {
                    printf("Welcome, %s. (Customer)\n", user->name);
                    while(1){
                    printf("1. Add Product related Complaints\n");
                    printf("2. Add Service related Complaints\n");
                    printf("3. Display Your Complaints\n");
                    printf("4. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    if (choice == 1 || choice == 2) {
                        printf("Enter your complaint: ");
                        scanf(" %[^\n]", complaint);
                        CustomerComplaint *newComplaint = createComplaintNode(id, user->name, complaint);
                        if (choice == 1) ProductComplaints(newComplaint);
                        else ServiceComplaint(newComplaint);
                    } else if (choice == 3) {
                        displayComplaints(id);
                    } else if (choice == 4) {
                        printf("Logging out.\n");
                        break;
                    } else {
                        printf("Invalid choice. Try again.\n");
                    }}
                } else {
                    printf("Customer ID and Name do not match.\n");
                }
            }

        } else if (choice == 2) {  // Sign up
            printf("Are you an Employee? (Y/N): ");
            scanf(" %c", &ch);
            getchar();

            printf("Enter your name: ");
            scanf(" %[^\n]", name);

            if (ch == 'Y' || ch == 'y') {
                sprintf(id, "EMP-%d", lastEmployeeID++);
                emplisthead = addUser(emplisthead, id, name); // Get the updated list
            } else {
                sprintf(id, "%d", lastCustomerID++);
                custlisthead = addUser(custlisthead, id, name); // Get the updated list
            }

        } else if (choice == 3) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
