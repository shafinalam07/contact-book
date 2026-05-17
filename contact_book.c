#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    int id;
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
    char category[20];
};

void addContact(FILE *fp) {
    struct Contact c;
    fseek(fp, 0, SEEK_END);

    printf("\n--- Add New Contact ---\n");
    printf("Enter ID: ");
    scanf("%d", &c.id);
    getchar();
    printf("Enter Name: ");
    fgets(c.name, 50, stdin);
    c.name[strcspn(c.name, "\n")] = 0;
    printf("Enter Phone: ");
    fgets(c.phone, 15, stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;
    printf("Enter Email: ");
    fgets(c.email, 50, stdin);
    c.email[strcspn(c.email, "\n")] = 0;
    printf("Enter Address: ");
    fgets(c.address, 100, stdin);
    c.address[strcspn(c.address, "\n")] = 0;
    printf("Category (Friend/Family/Work/Other): ");
    fgets(c.category, 20, stdin);
    c.category[strcspn(c.category, "\n")] = 0;

    fwrite(&c, sizeof(c), 1, fp);
    printf("Contact added successfully!\n");
}

void displayAll(FILE *fp) {
    struct Contact c;
    rewind(fp);
    int found = 0;

    printf("\n%-5s %-20s %-15s %-25s %-10s\n",
           "ID", "Name", "Phone", "Email", "Category");
    printf("-----------------------------------------------------------------------\n");

    while(fread(&c, sizeof(c), 1, fp)) {
        printf("%-5d %-20s %-15s %-25s %-10s\n",
               c.id, c.name, c.phone, c.email, c.category);
        found = 1;
    }
    if(!found) printf("No contacts found!\n");
}

void searchContact(FILE *fp) {
    char query[50];
    struct Contact c;
    int found = 0;

    getchar();
    printf("Enter name or phone to search: ");
    fgets(query, 50, stdin);
    query[strcspn(query, "\n")] = 0;

    rewind(fp);
    while(fread(&c, sizeof(c), 1, fp)) {
        if(strstr(c.name, query) || strstr(c.phone, query)) {
            printf("\n--- Contact Found ---\n");
            printf("ID       : %d\n", c.id);
            printf("Name     : %s\n", c.name);
            printf("Phone    : %s\n", c.phone);
            printf("Email    : %s\n", c.email);
            printf("Address  : %s\n", c.address);
            printf("Category : %s\n", c.category);
            found = 1;
        }
    }
    if(!found) printf("Contact not found!\n");
}

void updateContact(FILE *fp) {
    int id;
    struct Contact c;
    long pos;
    int found = 0;

    printf("Enter Contact ID to update: ");
    scanf("%d", &id);
    getchar();

    rewind(fp);
    while(fread(&c, sizeof(c), 1, fp)) {
        if(c.id == id) {
            printf("Current Name: %s\n", c.name);
            printf("Current Phone: %s\n", c.phone);
            printf("Current Email: %s\n", c.email);

            printf("\nEnter new Phone: ");
            fgets(c.phone, 15, stdin);
            c.phone[strcspn(c.phone, "\n")] = 0;
            printf("Enter new Email: ");
            fgets(c.email, 50, stdin);
            c.email[strcspn(c.email, "\n")] = 0;
            printf("Enter new Address: ");
            fgets(c.address, 100, stdin);
            c.address[strcspn(c.address, "\n")] = 0;

            pos = ftell(fp) - sizeof(c);
            fseek(fp, pos, SEEK_SET);
            fwrite(&c, sizeof(c), 1, fp);
            printf("Contact updated successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found) printf("Contact not found!\n");
}

void deleteContact(FILE *fp) {
    int id;
    struct Contact c;
    FILE *temp;
    int found = 0;

    printf("Enter Contact ID to delete: ");
    scanf("%d", &id);

    temp = fopen("temp.dat", "wb");
    rewind(fp);

    while(fread(&c, sizeof(c), 1, fp)) {
        if(c.id == id) {
            found = 1;
            printf("Contact deleted successfully!\n");
        } else {
            fwrite(&c, sizeof(c), 1, temp);
        }
    }

    fclose(temp);
    fclose(fp);
    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");
    fp = fopen("contacts.dat", "rb+");

    if(!found) printf("Contact not found!\n");
}

void displayByCategory(FILE *fp) {
    char category[20];
    struct Contact c;
    int found = 0;

    getchar();
    printf("Enter category (Friend/Family/Work/Other): ");
    fgets(category, 20, stdin);
    category[strcspn(category, "\n")] = 0;

    printf("\n--- Contacts in %s ---\n", category);
    printf("%-5s %-20s %-15s %-25s\n",
           "ID", "Name", "Phone", "Email");
    printf("----------------------------------------------------------\n");

    rewind(fp);
    while(fread(&c, sizeof(c), 1, fp)) {
        if(strcmp(c.category, category) == 0) {
            printf("%-5d %-20s %-15s %-25s\n",
                   c.id, c.name, c.phone, c.email);
            found = 1;
        }
    }
    if(!found) printf("No contacts in this category!\n");
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("contacts.dat", "rb+");
    if(!fp) {
        fp = fopen("contacts.dat", "wb+");
        if(!fp) {
            printf("Error opening file!\n");
            return 1;
        }
    }

    do {
        printf("\n=== Contact Book System ===\n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Display by Category\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addContact(fp); break;
            case 2: displayAll(fp); break;
            case 3: searchContact(fp); break;
            case 4: updateContact(fp); break;
            case 5: deleteContact(fp); break;
            case 6: displayByCategory(fp); break;
            case 7: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 7);

    fclose(fp);
    return 0;
}