
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  struct Node *head = NULL;

  // Initialize the linked list
  initialize_list(&head);

  // Read accounts from file
  read_accounts_from_file(&head, "accounts.txt");

  // Read transactions from file
  read_transactions_from_file(&head, "transactions.txt");

  // Display main menu
  printf("\n");
  printf("███████ ███████ ██     ██████   █████  ███    ██ ██   ██ \n");
  printf("██      ██      ██     ██   ██ ██   ██ ████   ██ ██  ██  \n");
  printf("█████   ███████ ██     ██████  ███████ ██ ██  ██ █████   \n");
  printf("██           ██ ██     ██   ██ ██   ██ ██  ██ ██ ██  ██  \n");
  printf("███████ ███████ ██     ██████  ██   ██ ██   ████ ██   ██ \n");
  printf("\n"); // Add an extra newline for better spacing
  printf("\n");

  printf("Creators: BELARBI ANES, ABDELMALEK, and NEKHOUL Mohamed ASSIL\n\n");

  // Display main menu options
  int choice;
  do {
    printf("Main Menu:\n");
    printf("1. Admin Menu\n");
    printf("2. Customer Menu\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      // Call Admin Menu function
      admin_menu(&head);
      break;
    case 2:
      // Call Customer Menu function
      customer_menu(head);
      break;
    case 3:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 3);

  // Free allocated memory
  free_list(&head);

  return 0;
}
