// Mesin ATM yang dapat melakukan :
// a. transaksi penyimpanan, 
// b. penarikan
// c. transfer 
// Pecahan yang ditangani adalah 20.000, 50.000,
// 75.000 dan 100.000

/*
a.	Yang harus ada dalam program
 Array
 Abtrack Data Type
 Stack
 !Queue
 Sorting
 Searching
b.	Materi Pilihan dalam Program
 !Tree
 Graph
c.	Point Tambahan
 Linked list
 Recursion
 Hashing
*/

/*
    1. Jangan dikosongin saldonya, (Minimal : 50.000)
    2. Bodoamat pecahannya berapa, yang penting saldo totalnya
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define size 2

int hash[size]; //array untuk menyimpan nilai hash
int i, j, counter = 0; //variabel bantuan
int t = 0, t1 = 0; //variabel bantuan
int keyTemp, keyTemp2, key;//variabel bantuan untuk hash
int u = 0; //variabel bantuan
int temp1, temp2;

struct stackNode{ //stack
    int data;
    struct stackNode *next;
};

struct tempHistory{ //dipakai menyimpan nilai riwayat yang nantinya disorting pada fungsi specificHistory
    int fake1;
    int fake2;
} tempHistory[50];

struct userData{ //menyimpan data user
    int pinTemp, pin;
    int temp1, temp2;
    int balance;
    long long id;
    int historyTemp, history;
} userData[50];

struct llist{ //linked list
    int data;
    struct llist *next;
} *head = NULL, *tail = NULL, *curr;

struct stackNode *newNode(int);
int isEmpty(struct stackNode *);
void push(struct stackNode **, int);
int pop(struct stackNode **);
int pushBack(int);

void initHash();
void insertHash(int);

void begin();
void search(int);
void insertPin();

void deposit();

void withdraw();

void transfer();
void destinationAccount();
void searchDestination(int);

void changePin();
void newPin();

void checkBalance();

void history();
void recentHistory();
void allHistory();
void specificHistory();

void main(){
    int cardNumber;
    FILE *fp, *fw;
    fp = fopen("data.txt", "r");
    while(!feof(fp)){
        fscanf(fp, "%lld %d %d", &userData[i].id, &userData[i].pinTemp, &userData[i].balance);
        i++;
    }
    fclose(fp);
    initHash();
    for(i = 0; i < size; i++){
        insertHash(userData[i].id); //untuk menyimpan nilai hash
    }
    system("cls");
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("======================================================\n");
    printf(" Insert your card number to continue : "); scanf("%d", &cardNumber); fflush(stdin);
    search(cardNumber);
    begin();
    fw = fopen("dataTemp.txt", "w");
    for(i = 0; i < size; i++){
        fprintf(fw, "%lld %d %d\n", userData[i].id, userData[i].pinTemp, userData[i].balance);
    }
    fclose(fw);
    remove("data.txt");
    rename("dataTemp.txt", "data.txt");
    system("cls");
    printf("======================================================\n");
    printf("         Group D6 - Final Project - ATM Program       \n");
    printf("======================================================\n");
    printf(" Member : \n");
    printf(" 1. Ni Luh Eka Suryaningsih              (2108561096)\n");
    printf(" 2. Anak Agung Ngurah Frady Cakra Negara (2108561097)\n");
    printf(" 3. I Made Sudarsana Taksa Wibawa        (2108561109)\n");
    printf("======================================================\n\n");
}

void begin(){
    int choice;
    enum choice{
        DEPOSIT = 1,
        WITHDRAW,
        TRANSFER,
        CHECKBALANCE,
        CHANGEPIN,
        HISTORY,
        EXIT
    };
    do{
        system("cls");
        printf("======================================================\n");
        printf("       ATM Program (Data Structure Final Project)     \n");
        printf("======================================================\n");
        printf(" 1. Deposit\n");
        printf(" 2. Withdraw\n");
        printf(" 3. Transfer\n");
        printf(" 4. Check Balance\n");
        printf(" 5. Change Pin\n");
        printf(" 6. Transfer History\n");
        printf(" 7. Exit\n");
        printf("======================================================\n");
        printf(" Enter your choice (1 - 7): "); scanf("%d", &choice); fflush(stdin);
        system("cls");
        switch(choice){
            case DEPOSIT:
                deposit();
                break;
            case WITHDRAW:
                withdraw();
                break;
            case TRANSFER:
                transfer();
                break;
            case CHECKBALANCE:
                checkBalance();
                break;
            case CHANGEPIN:
                changePin();
                break;
            case HISTORY:
                for(t = 0; t < t1; t++){
                    pushBack(userData[t].history);
                }
                history();
                break;
            case EXIT:
                return;
                break;
            default:
                break;
        }
        if(choice >= 1 && choice < 7){
            printf("\n "); 
            system("pause");
        }
    }while(choice < '1' || choice > '7');
}

void deposit(){
    int choice, amount, totalDeposit;
    do{
        system("cls");
        printf("======================================================\n");
        printf("       ATM Program (Data Structure Final Project)     \n");
        printf("                       [Deposit]                      \n");
        printf("======================================================\n");
        printf(" Choose the nominal amount to deposit :\n");
        printf(" 1. 20.000\n");
        printf(" 2. 50.000\n");
        printf(" 3. 75.000\n");
        printf(" 4. 100.000\n");
        printf(" 5. Back\n");
        printf("======================================================\n");
        printf(" Enter your choice (1 - 5): "); scanf("%d", &choice); fflush(stdin);
        if(choice < 5 && choice > 0){
            printf("\n Enter the amount of money to deposit : "); scanf("%d", &amount); fflush(stdin);
        }
        switch(choice){
            case 1:
                totalDeposit = 20000 * amount;
                break;
            case 2:
                totalDeposit = 50000 * amount;
                break;
            case 3:
                totalDeposit = 75000 * amount;
                break;
            case 4:
                totalDeposit = 100000 * amount;
                break;
            case 5:
                return begin();
                break;
            default:
                break;
        }
    } while(choice < 1 || choice > 4);
    system("cls");
    userData[keyTemp].balance += totalDeposit;
    // p = 0;
    insertPin();
    printf("======================================================\n");
    printf("                Transaction Successful!               \n");
    printf("======================================================\n");
    printf(" Your new balance is : %d\n", userData[keyTemp].balance);
    userData[keyTemp].history = totalDeposit;
    userData[keyTemp].historyTemp = 1;
    t++, t1++;
}

void insertPin(){
    int counter = 1;
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("======================================================\n");
    printf(" Enter your PIN to continue : ");
    do{
        scanf("%d", &userData->pin); fflush(stdin);
        if(userData->pin == userData[keyTemp].pinTemp){
            printf(" PIN is correct!\n");
            break;
        }
        else{
            counter++;
            printf(" PIN is incorrect!\n");
            printf("\n Attempt of %d : ", counter);
        }
    } while(counter <= 3);
    if(counter >= 3){
        system("cls");
        printf("======================================================\n");
        printf("                  Transaction failed!                 \n");
        printf("======================================================\n");
        printf("\n Your account has been locked!\n\n");
        exit(0);
    }
    system("cls");
}

void withdraw(){
    int amount, choice;
    do{
        system("cls");
        printf("======================================================\n");
        printf("       ATM Program (Data Structure Final Project)     \n");
        printf("                       [Withdraw]                     \n");
        printf("======================================================\n");
        printf(" Choose the nominal amount to withdraw :\n");
        printf(" 1. 100.000\n");
        printf(" 2. 200.000\n");
        printf(" 3. 500.000\n");
        printf(" 4. 1.000.000\n");
        printf(" 5. Back\n");
        printf("======================================================\n");
        printf(" Enter your choice (1 - 5): "); scanf("%d", &choice); fflush(stdin);
        printf("\n");
        switch(choice){
            case 1:
                if(userData[keyTemp].balance < 100000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return withdraw();
                }
                userData[keyTemp].balance -= 100000;
                amount = 100000;
                break;
            case 2:
                if(userData[keyTemp].balance < 200000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return withdraw();
                }
                userData[keyTemp].balance -= 200000;
                amount = 200000;
                break;
            case 3:
                if(userData[keyTemp].balance < 500000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return withdraw();
                }
                userData[keyTemp].balance -= 500000;
                amount = 500000;
                break;
            case 4:
                if(userData[keyTemp].balance < 1000000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return withdraw();
                }
                userData[keyTemp].balance -= 1000000;
                amount = 1000000;
                break;
            case 5:
                return begin();
                break;
            default:
                break;
        }
    } while(choice < 1 || choice > 5);
    system("cls");
    insertPin();
    printf("======================================================\n");
    printf("                Transaction Successful!               \n");
    printf("======================================================\n");
    printf(" Your new balance is : %d\n", userData[keyTemp].balance);
    userData[t].history = amount;
    userData[t].historyTemp = 2;
    t++, t1++;
}

void transfer(){
    int amount, choice, key;
    do{
        system("cls");
        printf("======================================================\n");
        printf("       ATM Program (Data Structure Final Project)     \n");
        printf("                       [Transfer]                     \n");
        printf("======================================================\n");
        printf(" Choose the nominal amount to transfer :\n");
        printf(" 1. 100.000\n");
        printf(" 2. 200.000\n");
        printf(" 3. 500.000\n");
        printf(" 4. 1.000.000\n");
        printf(" 5. Back\n");
        printf("======================================================\n");
        printf(" Enter your choice (1 - 5): "); scanf("%d", &choice); fflush(stdin);
        printf("\n");
        switch(choice){
            case 1:
                if(userData[keyTemp].balance < 100000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return transfer();
                }
                userData[keyTemp].balance -= 100000;
                amount = 100000;
                break;
            case 2:
                if(userData[keyTemp].balance < 200000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return transfer();
                }
                userData[keyTemp].balance -= 200000;
                amount = 200000;
                break;
            case 3:
                if(userData[keyTemp].balance < 500000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return transfer();
                }
                userData[keyTemp].balance -= 500000;
                amount = 500000;
                break;
            case 4:
                if(userData[keyTemp].balance < 1000000){
                    printf(" You don't have enough money!\n");
                    printf("\n "); 
                    system("pause");
                    return transfer();
                }
                userData[keyTemp].balance -= 1000000;
                amount = 1000000;
                break;
            case 5:
                return begin();
                break;
            default:
                break;
        }
    } while(choice < 1 || choice > 5);
    destinationAccount();
    userData[keyTemp2].balance += amount;
    system("cls");
    insertPin();
    printf("======================================================\n");
    printf("                Transaction Successful!               \n");
    printf("======================================================\n");
    printf(" Your new balance is : %d\n", userData[keyTemp].balance);
    userData[t].history = amount;
    userData[t].historyTemp = 3;
    t++, t1++;
}

void destinationAccount(){
    int desId;
    printf(" Enter the destination account ID : "); scanf("%d", &desId); fflush(stdin);
    searchDestination(desId);
}

void searchDestination(int value){
    fflush(stdin);
    key = value % size;
    if(hash[key] == value){
        printf(" Card Number is Verified!\n");
        keyTemp2 = key;
    }
    else{
        printf(" Card Number is not Verified!\n");
        return destinationAccount();
    }
}

void checkBalance(){
    system("cls");
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("                     [Check Balance]                  \n");
    printf("======================================================\n");
    printf(" Your current balance is : %d\n", userData[keyTemp].balance);
}

void changePin(){
    system("cls");
    insertPin();
    system("cls");
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("                     [Change PIN]                     \n");
    printf("======================================================\n");
    printf(" Enter your new PIN : "); scanf("%d", &userData->temp1); fflush(stdin);
    printf(" Confirm your new PIN : "); scanf("%d", &userData->temp2); fflush(stdin);
    system("cls");
    if(userData->temp1 == userData->temp2){
        printf("======================================================\n");
        printf("                PIN Changed Successfully!            \n");
        printf("======================================================\n");
        userData->pinTemp = userData->temp1;
        printf(" Your new PIN is : %d\n", userData->pinTemp);
    }
    else{
        printf("======================================================\n");
        printf("               PIN Changed Unsuccessfully!            \n");
        printf("======================================================\n");
        return begin();
    }
    FILE *fw;
    fw = fopen("dataTemp.txt", "w");
    for(i = 0; i < size; i++){
        fprintf(fw, "%lld %d %d\n", userData[i].id, userData[i].pinTemp, userData[i].balance);
    }
    fclose(fw);
    remove("data.txt");
    rename("dataTemp.txt", "data.txt");
}

void history(){
    int choice;
    do{
        system("cls");
        printf("======================================================\n");
        printf("       ATM Program (Data Structure Final Project)     \n");
        printf("                       [History]                      \n");
        printf("======================================================\n");
        printf(" 1. View Recent Transaction History\n");
        printf(" 2. View All Transaction History\n");
        printf(" 3. Search Transaction History\n");
        printf(" 4. Back\n");
        printf("======================================================\n");
        printf("Enter your choice (1 - 4): "); scanf("%d", &choice); fflush(stdin);
        switch(choice){
            case 1:
                recentHistory();
                break;
            case 2:
                allHistory();
                break;
            case 3:
                specificHistory();
                break;
            case 4:
                return begin();
                break;
            default:
                break;
        }
    } while(choice < 1 || choice > 4);
}

void recentHistory(){
    struct stackNode *root = NULL;
    system("cls");
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("                    [Recent History]                  \n");
    printf("======================================================\n");
    for(t = 0; t < t1; t++){
        push(&root, userData[t].history);
    }
    for(t = t1; t > t1 - 4; t--){
        if(userData[t].historyTemp == 1){
            printf(" Deposit : %d\n", pop(&root));
        }
        else if(userData[t].historyTemp == 2){
            printf(" Withdraw : %d\n", pop(&root));
        }
        else if(userData[t].historyTemp == 3){
            printf(" Transfer : %d\n", pop(&root));
        }
    }
}

void allHistory(){
    system("cls");
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("                      [All History]                   \n");
    printf("======================================================\n");
    for(t = 0; t < t1; t++){
        printf(" Transaction %d\n", t + 1);
        if(userData[t].historyTemp == 1){
            printf(" Deposit : %d\n", userData[t].history);
        }
        else if(userData[t].historyTemp == 2){
            printf(" Withdraw : %d\n", userData[t].history);
        }
        else if(userData[t].historyTemp == 3){
            printf(" Transfer : %d\n", userData[t].history);
        }
        printf("\n");
    }
}

void specificHistory(){
    int category, amount;
    system("cls");
    printf("======================================================\n");
    printf("       ATM Program (Data Structure Final Project)     \n");
    printf("                       [History]                      \n");
    printf("======================================================\n");
    for(i = 0; i < t1; i++){
        tempHistory[i].fake1 = userData[i].historyTemp;
        tempHistory[i].fake2 = userData[i].history;
    }
    for(i = 1; i < t1; i++){
        for(j = 0; j < t1; j++){
            if(tempHistory[j].fake1 > tempHistory[j+1].fake1){
                temp1 = tempHistory[j].fake1;
                tempHistory[j].fake1 = tempHistory[j+1].fake1;
                tempHistory[j+1].fake1 = temp1;

                temp2 = tempHistory[j].fake2;
                tempHistory[j].fake2 = tempHistory[j+1].fake2;
                tempHistory[j+1].fake2 = temp2;
            }
        }
    }
    for(i = 0; i < t1; i++){
        if(tempHistory[i].fake1 == 1){
            printf(" Deposit : %d\n", tempHistory[i].fake2);
        }
        else if(tempHistory[i].fake1 == 2){
            printf(" Withdraw : %d\n", tempHistory[i].fake2);
        }
        else if(tempHistory[i].fake1 == 3){
            printf(" Transfer : %d\n", tempHistory[i].fake2);
        }
    }
    printf("\n");
    printf(" Input history number to search\n");
    printf(" Deposit : 1\n");
    printf(" Withdraw : 2\n");
    printf(" Transfer : 3\n");
    printf(" Example : 1 100000 (Deposit with amount of 100000\n");
    printf(" Enter your choice : "); scanf("%d %d", &category, &amount); fflush(stdin);
    for(i = 0; i < t1; i++){
        if(category == userData[i].historyTemp && amount == userData[i].history){
            printf(" Transaction is made on the %d transaction\n", i+1);
        }
    }
}

struct stackNode *newNode(int data)
{
	struct stackNode *node = (struct stackNode*)malloc(sizeof(struct stackNode));
	node->data = data;
	node->next = NULL;
	return node;
}

int isEmpty(struct stackNode *root){
	return !root;
}

void push(struct stackNode **root, int data){
	struct stackNode *node = newNode(data);
	node->next = *root;
	*root = node;
}

int pop(struct stackNode **root){
	if (isEmpty(*root)){
	    return INT_MIN;
    }
	struct stackNode *temp = *root;
	*root = (*root)->next;
	int popped = temp->data;
	free(temp);
	return popped;
}

int pushBack(int value){
    curr = (struct llist*)malloc(sizeof(struct llist));
    curr->data = value;
    if(head == NULL){
        head = tail = curr;
    }
    else{
        tail->next = curr;
        tail = curr;
    }
    tail->next = NULL;
}

void initHash(){
    for(i = 0; i < size; i++){
        hash[i] = -1;
    }
}

void insertHash(int value){
    key = value % size;
    if(hash[key] == -1){
        hash[key] = value;
        printf("\n");
    }
    else{
        printf(" Hash Collision!\n hash[%d] has element %d already!\n", key, hash[key]);
        printf(" Unable to insert %d\n", value);
    }
}

void search(int value){
    key = value % size;
    if(hash[key] == value){
        printf(" Card Number is Verified!\n\n ");
        keyTemp = key;
        system("pause");
    }
    else{
        printf(" Card Number is not Verified!\n\n ");
        system("pause");
        return main();
    }
}