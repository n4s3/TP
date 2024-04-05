
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
    struct Node* next;
};

// Function prototypes
void initialize_list(struct Node** head);
void read_accounts_from_file(struct Node** head, const char* filename);
void read_transactions_from_file(struct Node** head, const char* filename);
void add_account(struct Node** head, struct BankAccount new_account);
void delete_account(struct Node** head, int account_number);
void edit_account(struct Node** head, int account_number);
void display_accounts(struct Node* head);
void transfer_amount(struct Node** head, int sender_account, int receiver_account, double amount);
void deposit_fund(struct Node** head, int account_number, double amount);
void make_withdrawal(struct Node** head, int account_number, double amount);
double check_total_amount(struct Node* head, int account_number);
void check_transaction_history(struct Node* head, int account_number, char* start_date, char* end_date);
void admin_menu(struct Node** head);
void customer_menu(struct Node* head);
void free_list(struct Node** head);

#endif
