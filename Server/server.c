#include "server.h"

ST_accountsDB_t accountsDB[255]={
        {10000,RUNNING,"4550746475531533"},
        {5000,BLOCKED,"4699094091899964"},
{1000,RUNNING,"4683982334261711"},
{20000,BLOCKED,"4684895000385128"},
{16000,RUNNING,"4315503473726102"}
};
ST_transaction_t transactionsDB[255] = {0};
uint32_t sequence_number =0;

EN_transState_t receiveTransactionData(ST_transaction_t* transData) {
    ST_accountsDB_t accountReference = {0};
    EN_serverError_t isValid = isValidAccount(&transData->cardHolderData, &accountReference);
    if (isValid == SERVER_OK) {
        EN_serverError_t isBlocked = isBlockedAccount(&accountReference);
        if (isBlocked == SERVER_OK) {
            EN_serverError_t isAvailable = isAmountAvailable(&transData->terminalData, &accountReference);
            if (isAvailable == SERVER_OK) {
                // update the account balance
                accountReference.balance -= transData->terminalData.transAmount;
                transData->transState = APPROVED;
                // save the transaction
                EN_serverError_t saveResult = saveTransaction(transData);
                if (saveResult == SERVER_OK) {
                    return APPROVED;
                } else {
                    return INTERNAL_SERVER_ERROR;
                }
            } else {
                return DECLINED_INSUFFICIENT_FUND;
            }
        } else {
            return DECLINED_STOLEN_CARD;
        }
    } else {
        return FRAUD_CARD;
    }
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData,ST_accountsDB_t* accountReference) {
    for (int i = 0; i < 255; i++) {
        if (strncmp((char *) cardData->primaryAccountNumber, (char *) accountsDB[i].primaryAccountNumber, sizeof(cardData->primaryAccountNumber)) == 0) {
            *accountReference = accountsDB[i];
            return SERVER_OK;
        }
    }
    memset(accountReference, 0, sizeof(ST_accountsDB_t));
    return ACCOUNT_NOT_FOUND;
}



EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountReference)
{
    if(accountReference->state == BLOCKED)
        return BLOCKED_ACCOUNT;
    else
        return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference) {
    if (termData->transAmount > accountReference->balance) {
        return LOW_BALANCE;
    }
    else {
        return SERVER_OK;
    }
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    transactionsDB[sequence_number].cardHolderData = transData->cardHolderData;
    transactionsDB[sequence_number].terminalData = transData->terminalData;
    transactionsDB[sequence_number].transState = transData->transState;
    transactionsDB[sequence_number].transactionSequenceNumber = sequence_number;
    sequence_number++;
    return SERVER_OK;
}

void listSavedTransactions() {
    for (int i = 0; i < sequence_number; i++) {
        printf("#########################\n");
        printf("Transaction Sequence Number: %lu\n", transactionsDB[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", transactionsDB[i].terminalData.transAmount);
        printf("Transaction State: %d\n", transactionsDB[i].transState);
        printf("Terminal Max Amount: %d\n", (int)transactionsDB[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
    }
}
