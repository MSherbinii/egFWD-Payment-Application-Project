#include "application.h"
void appStart(void) {
    ST_cardData_t cardData;
    ST_terminalData_t termData;
    ST_accountsDB_t accountReference;
    ST_transaction_t transData;
    EN_cardError_t cardError;
    EN_terminalError_t termError;
    EN_serverError_t serverError;
    EN_transState_t transState;

    // Get card holder name
    cardError = getCardHolderName(&cardData);
    if (cardError != CARD_OK) {
        printf("Declined: Invalid card holder name\n");
        return;
    }

    // Get card expiration date
    cardError = getCardExpiryDate(&cardData);
    if (cardError != CARD_OK) {
        printf("Declined: Invalid card expiration date\n");
        return;
    }

    // Get card PAN
    cardError = getCardPAN(&cardData);
    if (cardError != CARD_OK) {
        printf("Declined: Invalid card PAN\n");
        return;
    }

    // Get transaction date
    termError = getTransactionDate(&termData);
    if (termError != TERMINAL_OK) {
        printf("Declined: Invalid transaction date\n");
        return;
    }

    // Check if card is expired
    termError = isCardExpired(&cardData, &termData);
    if (termError == EXPIRED_CARD) {
        printf("Declined: Card expired\n");
        return;
    }

    // Get transaction amount
    termError = getTransactionAmount(&termData);
    if (termError != TERMINAL_OK) {
        printf("Declined: Invalid transaction amount\n");
        return;
    }
    termError = setMaxAmount(&termData, 25000);
    if (termError != TERMINAL_OK) {
        printf("Declined: Failed to set max amount\n");
        return;
    }

// Check if transaction amount is below max amount
    termError = isBelowMaxAmount(&termData);
    if (termError == EXCEED_MAX_AMOUNT) {
        printf("Declined: Amount exceeding limit\n");
        return;
    }
    transState = receiveTransactionData(&transData);
    if (transState == APPROVED) {
        printf("Transaction data sent successfully\n");
    } else {
        printf("Error sending transaction data\n");
        return;
    }


// Save transaction and update balance
    transData.cardHolderData = cardData;
    transData.terminalData = termData;
    transData.transState = APPROVED;
    saveTransaction(&transData);
    printf("Transaction complete\n");
    listSavedTransactions();
    printf("Current balance: %.2f\n", accountReference.balance);
}