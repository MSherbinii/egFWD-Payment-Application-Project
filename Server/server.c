#include "server.h"
#include "db.h"

uint32_t lastSequenceNumber=0;
uint32_t accountRef;
EN_transState_t receiveTransactionData(ST_transaction_t *transData) {
    ST_accountsDB_t account;
    // Check if the account is valid
    EN_serverError_t error = isValidAccount(&transData->cardHolderData, &account);
    if (error == ACCOUNT_NOT_FOUND) {
        return FRAUD_CARD;
    }
    // Check if the account is blocked
    error = isBlockedAccount(&account);
    if (error == BLOCKED_ACCOUNT) {
        return DECLINED_STOLEN_CARD;
    }
    // Check if the amount is available
    error = isAmountAvailable(&transData->terminalData, &account);
    if (error == LOW_BALANCE) {
        return DECLINED_INSUFFICIENT_FUND;
    }
    // Update the account balance
    accountsDB[accountRef].balance -= transData->terminalData.transAmount;
    transData->transState = APPROVED;
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountReference) {
    // Iterate through the server's database and check if the PAN exists
    for (int i = 0; i < 255; i++) {
        if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
            // PAN exists, return reference to the account
            *accountReference = accountsDB[i];
            uint32_t accountRef=i;
            return SERVER_OK;
        }
    }
    // PAN not found in the database, return ACCOUNT_NOT_FOUND error
    accountReference = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountReference) {
    // Check if the account is blocked
    if (accountReference->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    }
    // Account is running
    return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountReference) {
    // Check if the transaction amount is greater than the balance
    if (termData->transAmount > accountReference->balance) {
        return LOW_BALANCE;
    }
    // Account has sufficient balance
    return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    transactionsDB[lastSequenceNumber].cardHolderData = transData->cardHolderData;
    transactionsDB[lastSequenceNumber].terminalData = transData->terminalData;
    transactionsDB[lastSequenceNumber].transState = transData->transState;
    transData->transactionSequenceNumber = lastSequenceNumber++;
    return SERVER_OK;
}



void listSavedTransactions(void) {
    printf("List of Saved Transactions:\n");
    for (uint32_t i = 1; i <= lastSequenceNumber; i++) {
        printf("#########################\n");
        printf("Transaction Sequence Number: %lu\n", transactionsDB[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n", transactionsDB[i].terminalData.transAmount);
        printf("Transaction State: %d\n", transactionsDB[i].transState);
        printf("Terminal Max Amount: %.2f\n", transactionsDB[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s \n", transactionsDB[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
    }
}



