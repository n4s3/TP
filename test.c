#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define bank account structure
struct BankAccount {
  int account_number;
  int code;
  char customer[100];
  double balance;
};

// Define transaction structure
struct Transaction {
  char operation_code[20];
  char date[20];
  double amount;
};

// Define linked list node structure
struct Node {
  struct BankAccount account;
  struct Transaction transaction;
  struct Node *next;
};

// Function prototypes
void initialize_list(struct Node **head);
void read_accounts_from_file(struct Node **head, const char *filename);
void read_transactions_from_file(struct Node **head, const char *filename);
void add_account(struct Node **head, struct BankAccount new_account);
void display_accounts(struct Node *head);
void display_transactions(struct Node *head);
void free_list(struct Node *head);
void transfer_amount(struct Node **head, int sender_account,
                     int receiver_account, double amount);
void deposit_fund(struct Node **head, int account_number, double amount);
void make_withdrawal(struct Node **head, int account_number, double amount);
double check_total_amount(struct Node *head, int account_number);
void check_transaction_history(struct Node *head, int account_number,
                               char *start_date, char *end_date);

int main() {
  struct Node *head = NULL;

  // Initialize the linked list
  initialize_list(&head);

  // Read accounts from file
  read_accounts_from_file(&head, "accounts.txt");

  // Read transactions from file
  read_transactions_from_file(&head, "transactions.txt");

  // Example usage of functionalities
  printf("Initial State:\n");
  display_accounts(head);
  display_transactions(head);

  // Example usage of functionalities
  transfer_amount(&head, 123456, 234567, 200.0);
  deposit_fund(&head, 123456, 300.0);
  make_withdrawal(&head, 234567,
                  1000.0); // Attempting to withdraw more than balance
  make_withdrawal(&head, 234567, 100.0); // Valid withdrawal
  double total_balance = check_total_amount(head, 123456);
  printf("\nTotal Balance for Account 123456: %.2f\n", total_balance);
  check_transaction_history(head, 123456, "2024-01-01", "2024-12-31");

  // Free allocated memory
  free_list(head);

  return 0;
}

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

// Function to display all transactions in the linked list
void display_transactions(struct Node *head) {
  printf("\nTransactions:\n");
  printf("Account Number\tOperation\tDate\tAmount\n");
  struct Node *current = head;
  while (current != NULL) {
    printf("%d\t\t%s\t%s\t%.2f\n", current->account.account_number,
           current->transaction.operation_code, current->transaction.date,
           current->transaction.amount);
    current = current->next;
  }
}

// Function to free allocated memory
void free_list(struct Node *head) {
  struct Node *current = head;
  while (current != NULL) {
    struct Node *temp = current;
    current = current->next;
    free(temp);
  }
}

// Function to transfer amount from one account to another
void transfer_amount(struct Node **head, int sender_account,
                     int receiver_account, double amount) {
  struct Node *sender = *head;
  struct Node *receiver = *head;

  // Find the sender and receiver nodes
  while (sender != NULL && sender->account.account_number != sender_account) {
    sender = sender->next;
  }
  while (receiver != NULL &&
         receiver->account.account_number != receiver_account) {
    receiver = receiver->next;
  }

  // Check if sender and receiver accounts exist
  if (sender == NULL) {
    printf("Sender account with account number %d not found.\n",
           sender_account);
    return;
  }
  if (receiver == NULL) {
    printf("Receiver account with account number %d not found.\n",
           receiver_account);
    return;
  }

  // Check if sender has sufficient balance
  if (sender->account.balance < amount) {
    printf("Transfer failed: Insufficient balance in sender account.\n");
    return;
  }

  // Update balances
  sender->account.balance -= amount;
  receiver->account.balance += amount;

  // Update transaction history (not implemented in this example)
  printf(
      "Transfer successful: %.2f transferred from account %d to account %d.\n",
      amount, sender_account, receiver_account);
}

// Function to deposit fund to an account
void deposit_fund(struct Node **head, int account_number, double amount) {
  struct Node *account = *head;

  // Find the account node
  while (account != NULL && account->account.account_number != account_number) {
    account = account->next;
  }

  // Check if account exists
  if (account == NULL) {
    printf("Account with account number %d not found.\n", account_number);
    return;
  }

  // Update balance
  account->account.balance += amount;

  // Update transaction history (not implemented in this example)
  printf(
      "Deposit successful: %.2f deposited to account %d. New balance: %.2f\n",
      amount, account_number, account->account.balance);
}

// Function to make a withdrawal of funds
void make_withdrawal(struct Node **head, int account_number, double amount) {
  struct Node *account = *head;

  // Find the account node
  while (account != NULL && account->account.account_number != account_number) {
    account = account->next;
  }

  // Check if account exists
  if (account == NULL) {
    printf("Account with account number %d not found.\n", account_number);
    return;
  }

  // Check if account has sufficient balance
  if (account->account.balance < amount) {
    printf("Withdrawal failed: Insufficient balance in account.\n");
    return;
  }

  // Update balance
  account->account.balance -= amount;

  // Update transaction history (not implemented in this example)
  printf("Withdrawal successful: %.2f withdrawn from account %d. New balance: "
         "%.2f\n",
         amount, account_number, account->account.balance);
}

// Function to check the total amount in an account
double check_total_amount(struct Node *head, int account_number) {
  struct Node *account = head;

  // Find the account node
  while (account != NULL && account->account.account_number != account_number) {
    account = account->next;
  }

  // Check if account exists
  if (account == NULL) {
    printf("Account with account number %d not found.\n", account_number);
    return -1.0;
  }

  return account->account.balance;
}

// Function to check transaction history within a given date range
void check_transaction_history(struct Node *head, int account_number,
                               char *start_date, char *end_date) {
  // Implementation
  printf("Transaction history for account %d between %s and %s:\n",
         account_number, start_date, end_date);
}
