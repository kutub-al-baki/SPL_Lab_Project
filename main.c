#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct customer{
    char name[50];
    int age;
    char mobile[15];
    int numOfTicket;
    int seats[4];
};
struct customer cust[61];
int seatArrangment[31];
int custNum = 1, total = 30, booked = 0, deletedIDs[30], delpos = 0;
void titleScreen(), showSeats(), takeBooking(), editBooking(), deleteBooking(), showCustDetails(int), returnToMenu(), showCustIdName();
int menu(), depart();
int main() {
    titleScreen();
    for (int i = 1; i <= 30; i++) seatArrangment[i] = i;
    while (menu());
    return 0;
}
void titleScreen() {
    printf("--- Bus Ticket Booking System ---\n\n");
}
int menu() {
    printf("1. Show seats\n2. Take booking\n3. Edit booking\n4. Delete booking\n5. Show Customer Details\n6. Depart bus\n7. Exit\nEnter your option: ");
    int opt, ID; scanf("%d", &opt); getchar();
    switch (opt) {
        case 1: showSeats(); returnToMenu(); break;
        case 2: takeBooking(); returnToMenu(); break;
        case 3: editBooking(); returnToMenu(); break;
        case 4: deleteBooking(); returnToMenu(); break;
        case 5: showCustIdName();
                printf("Enter Customer ID: ");
                scanf("%d", &ID); getchar();
                showCustDetails(ID); returnToMenu(); break;
        case 6: return depart();
        case 7: return 0;
        default: printf("Invalid option.\n");
    }
    return 1;
}
void showSeats() {
    printf("Seat Arrangement:\n");
    for (int i = 1; i <= 30; i++) {
        printf("%s%02d ", seatArrangment[i] == -1 ? "XX" : "", seatArrangment[i]);
        if (i % 5 == 0) printf("\n");
    }
    printf("Total: %d, Booked: %d, Available: %d\n\n", total, booked, total - booked);
}
void takeBooking() {
    showSeats();
    printf("Enter Name: ");
    fgets(cust[custNum].name, 50, stdin);
    cust[custNum].name[strcspn(cust[custNum].name, "\n")] = '\0';
    printf("Enter Age: ");
    scanf("%d", &cust[custNum].age); getchar();
    printf("Enter Mobile: ");
    scanf("%s", cust[custNum].mobile); getchar();
    printf("How many tickets? ");
    scanf("%d", &cust[custNum].numOfTicket); getchar();
    for (int i = 0; i < cust[custNum].numOfTicket; i++) {
        int seat;
        printf("Select seat %d: ", i + 1);
        scanf("%d", &seat); getchar();
        if (seatArrangment[seat] != -1) {
            seatArrangment[seat] = -1;
            cust[custNum].seats[i] = seat;
            booked++;
        } else {
            printf("Seat %d is already booked.\n", seat);
            i--;
        }
    }
    printf("Your Customer ID is %d\n", custNum++);
}
void editBooking() {
    int ID;
    showCustIdName();
    printf("Enter Customer ID: ");
    scanf("%d", &ID); getchar();
    printf("1. Name\n2. Age\n3. Mobile\n4. Change seats\nSelect option: ");
    int opt; scanf("%d", &opt); getchar();
    if (opt == 1) {
        printf("Enter new Name: ");
        fgets(cust[ID].name, 50, stdin);
        cust[ID].name[strcspn(cust[ID].name, "\n")] = '\0';
    } else if (opt == 2) {
        printf("Enter new Age: ");
        scanf("%d", &cust[ID].age); getchar();
    } else if (opt == 3) {
        printf("Enter new Mobile: ");
        scanf("%s", cust[ID].mobile); getchar();
    } else if (opt == 4) {
        for (int i = 0; i < cust[ID].numOfTicket; i++)
            seatArrangment[cust[ID].seats[i]] = cust[ID].seats[i], booked--;
        printf("How many tickets? ");
        scanf("%d", &cust[ID].numOfTicket); getchar();
        for (int i = 0; i < cust[ID].numOfTicket; i++) {
            int seat;
            printf("Select seat %d: ", i + 1);
            scanf("%d", &seat); getchar();
            if (seatArrangment[seat] != -1) {
                seatArrangment[seat] = -1;
                cust[ID].seats[i] = seat;
                booked++;
            } else {
                printf("Seat %d is already booked.\n", seat);
                i--;
            }
        }
    }
}
void deleteBooking() {
    int ID;
    showCustIdName();
    printf("Enter Customer ID to delete: ");
    scanf("%d", &ID); getchar();
    deletedIDs[delpos++] = ID;
    for (int i = 0; i < cust[ID].numOfTicket; i++)
        seatArrangment[cust[ID].seats[i]] = cust[ID].seats[i], booked--;
    printf("Customer ID %d deleted.\n", ID);
}
void showCustDetails(int id) {
    printf("Name: %s, Age: %d, Mobile: %s, Seats: ",
           cust[id].name, cust[id].age, cust[id].mobile);
    for (int i = 0; i < cust[id].numOfTicket; i++)
        printf("%d ", cust[id].seats[i]);
    printf("\n");
}
int depart() {
    FILE *fp = fopen("output.txt", "w");
    if (!fp) { printf("Error creating file.\n"); return 0; }
    fprintf(fp, "--- Bus Booking Details ---\n");
    for (int i = 1; i < custNum; i++) {
        int deleted = 0;
        for (int j = 0; j < delpos; j++)
            if (deletedIDs[j] == i) { deleted = 1; break; }
        if (!deleted) {
            fprintf(fp, "ID: %d, Name: %s, Age: %d, Mobile: %s, Seats: ",
                    i, cust[i].name, cust[i].age, cust[i].mobile);
            for (int k = 0; k < cust[i].numOfTicket; k++)
                fprintf(fp, "%d ", cust[i].seats[k]);
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    printf("Bus departed. Details saved to output.txt.\nRestart for another bus? (y/n): ");
    char choice; scanf(" %c", &choice);
    return choice == 'y';
}
void returnToMenu() { printf("Press Enter to continue..."); getchar(); }
void showCustIdName() {
    for (int i = 1; i < custNum; i++) {
        int deleted = 0;
        for (int j = 0; j < delpos; j++)
            if (deletedIDs[j] == i) { deleted = 1; break; }
        if (!deleted)
            printf("Customer ID %d: %s\n", i, cust[i].name);
    }
}
