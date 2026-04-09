#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
    char name[50];
    char phone[15];
};

// Function declarations
void addContact();
void displayContacts();
void searchContact();
void deleteContact();

int main() {
    int choice;

    while (1) {
        printf("\n===== Contact Management System =====\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

// Add contact
void addContact() {
    FILE *fp = fopen("contacts.dat", "ab");
    struct contact c;

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter Phone: ");
    scanf("%s", c.phone);

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("Contact added successfully!\n");
}

// Display all contacts
void displayContacts() {
    FILE *fp = fopen("contacts.dat", "rb");
    struct contact c;

    if (fp == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (fread(&c, sizeof(c), 1, fp)) {
        printf("Name: %s | Phone: %s\n", c.name, c.phone);
    }

    fclose(fp);
}

// Search contact
void searchContact() {
    FILE *fp = fopen("contacts.dat", "rb");
    struct contact c;
    char name[50];
    int found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) == 0) {
            printf("Found: %s | %s\n", c.name, c.phone);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    fclose(fp);
}

// Delete contact
void deleteContact() {
    FILE *fp = fopen("contacts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct contact c;
    char name[50];
    int found = 0;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) != 0) {
            fwrite(&c, sizeof(c), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found)
        printf("Contact deleted successfully!\n");
    else
        printf("Contact not found!\n");
}