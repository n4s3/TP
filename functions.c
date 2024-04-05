
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to initialize the linked list
void initialize_list(struct Node **head) { *head = NULL; }

// Function to read accounts from file
void read_accounts_from_file(struct Node **head, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Failed to open file.\n");
    return;
  }

  struct BankAccount new_account;
  while (fscanf(file, "%d %d %s %lf", &new_account.account_number,
                &new_account.code, new_account.customer,
                &new_account.balance) == 4) {
    add_account(head, new_account);
  }

  fclose(file);
}

// Function to read transactions from file
void read_transactions_from_file(struct Node **head, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Failed to open file.\n");
    return;
  }

  struct Node *current = *head;
  while (current != NULL) {
    fscanf(file, "%s %s %lf", current->transaction.operation_code,
           current->transaction.date, &current->transaction.amount);
    current = current->next;
  }

  fclose(file);
}

// Function to add a new account to the linked list
void add_account(struct Node **head, struct BankAccount new_account) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  if (new_node == NULL) {
    printf("Memory allocation failed.\n");
    return;
  }

  new_node->account = new_account;
  new_node->next = *head;
  *head = new_node;
}

// Function to delete an account from the linked list
void delete_account(struct Node **head, int account_number) {
  struct Node *temp = *head, *prev = NULL;
  if (temp != NULL && temp->account.account_number == account_number) {
    *head = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && temp->account.account_number != account_number) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL)
    return;

  prev->next = temp->next;
  free(temp);
}

// Function to edit an account in the linked list
void edit_account(struct Node **head, int account_number) {
  struct Node *current = *head;
  while (current != NULL) {
    if (current->account.account_number == account_number) {
      printf("Enter new account number: ");
      scanf("%d", &current->account.account_number);
      printf("Enter new code: ");
      scanf("%d", &current->account.code);
      printf("Enter new customer name: ");
      scanf("%s", current->account.customer);
      printf("Enter new balance: ");
      scanf("%lf", &current->account.balance);
      return;
    }
    current = current->next;
  }
  printf("Account not found.\n");
}

// Function to display all accounts in the linked list
void display_accounts(struct Node *head) {
  printf("Accounts:\n");
  printf("Account Number\tCode\tCustomer\tBalance\n");
  struct Node *current = head;
  while (current != NULL) {
    printf("%d\t\t%d\t%s\t%.2f\n", current->account.account_number,
           current->account.code, current->account.customer,
           current->account.balance);
    current = current->next;
  }
}

// Function to transfer amount from one account to another
void transfer_amount(struct Node **head, int sender_account,
                     int receiver_account, double amount) {
  struct Node *sender = *head;
  struct Node *receiver = *head;
  while (sender != NULL && sender->account.account_number != sender_account)
    sender = sender->next;
  while (receiver != NULL &&
         receiver->account.account_number != receiver_account)
    receiver = receiver->next;
  if (sender == NULL || receiver == NULL) {
    printf("Invalid account numbers.\n");
    return;
  }
  if (sender->account.balance < amount) {
    printf("Insufficient balance in the sender's account.\n");
    return;
  }
  sender->account.balance -= amount;
  receiver->account.balance += amount;
  printf("Amount transferred successfully.\n");
}

// Function to deposit fund to an account
void deposit_fund(struct Node **head, int account_number, double amount) {
  struct Node *current = *head;
  while (current != NULL) {
    if (current->account.account_number == account_number) {
      current->account.balance += amount;
      printf("Deposit successful.\n");
      return;
    }
    current = current->next;
  }
  printf("Account not found.\n");
}

// Function to make a withdrawal of funds
void make_withdrawal(struct Node **head, int account_number, double amount) {
  struct Node *current = *head;
  while (current != NULL) {
    if (current->account.account_number == account_number) {
      if (current->account.balance < amount) {
        printf("Insufficient balance.\n");
        return;
      }
      current->account.balance -= amount;
      printf("Withdrawal successful.\n");
      return;
    }
    current = current->next;
  }
  printf("Account not found.\n");
}

// Function to check the total amount in an account
double check_total_amount(struct Node *head, int account_number) {
  struct Node *current = head;
  while (current != NULL) {
    if (current->account.account_number == account_number)
      return current->account.balance;
    current = current->next;
  }
  return -1;
}

// Function to check transaction history within a given date range
void check_transaction_history(struct Node *head, int account_number,
                               char *start_date, char *end_date) {
  struct Node *current = head;
  printf("Transaction History:\n");
  while (current != NULL) {
    if (current->account.account_number == account_number &&
        strcmp(current->transaction.date, start_date) >= 0 &&
        strcmp(current->transaction.date, end_date) <= 0) {
      printf("Operation: %s, Date: %s, Amount: %.2f\n",
             current->transaction.operation_code, current->transaction.date,
             current->transaction.amount);
    }
    current = current->next;
  }
}

// Function to free allocated memory
void free_list(struct Node **head) {
  struct Node *current = *head;
  while (current != NULL) {
    struct Node *temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}

void admin_menu(struct Node **head) {
  int choice;
  do {
    printf("\nAdmin Menu:\n");
    printf("+-------------------------------------+\n");
    printf("| 1. Add Account                     |\n");
    printf("| 2. Delete Account                  |\n");
    printf("| 3. Edit Account                    |\n");
    printf("| 4. Display Accounts                |\n");
    printf("| 5. Back to Main Menu               |\n");
    printf("+-------------------------------------+\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
      struct BankAccount new_account;
      printf("Enter account number: ");
      scanf("%d", &new_account.account_number);
      printf("Enter code: ");
      scanf("%d", &new_account.code);
      printf("Enter customer name: ");
      scanf("%s", new_account.customer);
      printf("Enter balance: ");
      scanf("%lf", &new_account.balance);
      add_account(head, new_account);
      printf("Account added successfully.\n");
      break;
    }
    case 2: {
      int account_number;
      printf("Enter account number to delete: ");
      scanf("%d", &account_number);
      delete_account(head, account_number);
      printf("Account deleted successfully.\n");
      break;
    }
    case 3: {
      int account_number;
      printf("Enter account number to edit: ");
      scanf("%d", &account_number);
      edit_account(head, account_number);
      printf("Account edited successfully.\n");
      break;
    }
    case 4:
      display_accounts(*head);
      break;
    case 5:
      printf("Returning to Main Menu...\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 5);
}

// Function to display customer menu options
void customer_menu(struct Node *head) {
  int choice;
  do {
    printf("\nCustomer Menu:\n");
    printf("+------------------------------------+\n");
    printf("| 1. Transfer Amount                 |\n");
    printf("| 2. Deposit Fund                    |\n");
    printf("| 3. Make Withdrawal                 |\n");
    printf("| 4. Check Total Amount              |\n");
    printf("| 5. Check Transaction History       |\n");
    printf("| 6. Back to Main Menu               |\n");
    printf("+------------------------------------+\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
      int sender_account, receiver_account;
      double amount;
      printf("Enter sender account number: ");
      scanf("%d", &sender_account);
      printf("Enter receiver account number: ");
      scanf("%d", &receiver_account);
      printf("Enter amount to transfer: ");
      scanf("%lf", &amount);
      transfer_amount(&head, sender_account, receiver_account, amount);
      break;
    }
    case 2: {
      int account_number;
      double amount;
      printf("Enter account number to deposit: ");
      scanf("%d", &account_number);
      printf("Enter amount to deposit: ");
      scanf("%lf", &amount);
      deposit_fund(&head, account_number, amount);
      break;
    }
    case 3: {
      int account_number;
      double amount;
      printf("Enter account number to withdraw from: ");
      scanf("%d", &account_number);
      printf("Enter amount to withdraw: ");
      scanf("%lf", &amount);
      make_withdrawal(&head, account_number, amount);
      break;
    }
    case 4: {
      int account_number;
      printf("Enter account number to check balance: ");
      scanf("%d", &account_number);
      double balance = check_total_amount(head, account_number);
      if (balance != -1) {
        printf("Total amount in account %d: %.2f\n", account_number, balance);
      } else {
        printf("Account not found.\n");
      }
      break;
    }
    case 5: {
      int account_number;
      char start_date[20], end_date[20];
      printf("Enter account number: ");
      scanf("%d", &account_number);
      printf("Enter start date (YYYY-MM-DD): ");
      scanf("%s", start_date);
      printf("Enter end date (YYYY-MM-DD): ");
      scanf("%s", end_date);
      check_transaction_history(head, account_number, start_date, end_date);
      break;
    }
    case 6:
      printf("Returning to Main Menu...\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 6);
}
