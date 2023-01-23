#include "application.h"
extern uint32_t accountRef;
void appStart(void) {
    ST_cardData_t cardData;
    ST_terminalData_t terminalData;
    ST_transaction_t trans;
    EN_cardError_t cardError;
    EN_terminalError_t terminalError;
    EN_transState_t transState;

    // Get cardholder name
    cardError = getCardHolderName(&cardData);
    if (cardError != CARD_OK) {
        printf("Declined Invalid Card\n");
        return;
    }

    // Get card expiration date
    cardError = getCardExpiryDate(&cardData);
    if (cardError != CARD_OK) {
        printf("Declined Expired Card\n");
        return;
    }

    // Get card PAN
    cardError = getCardPAN(&cardData);
    if (cardError != CARD_OK) {
        printf("Declined Invalid Card\n");
        return;
    }

    // Get transaction date
    terminalError = getTransactionDate(&terminalData);
    if (terminalError != TERMINAL_OK) {
        printf("Declined Invalid Date\n");
        return;
    }

    // Check if card is expired
    terminalError = isCardExpired(&cardData, &terminalData);
    if (terminalError != TERMINAL_OK) {
        printf("Declined Card Expired\n");
        return;
    }
    terminalError = setMaxAmount(&terminalData, 25000);
    if (terminalError != TERMINAL_OK) {
        printf("Declined Max Amount Value\n");
        return;
    }
    // Get transaction amount
    terminalError = getTransactionAmount(&terminalData);
    if (terminalError != TERMINAL_OK) {
        printf("Declined Invalid Amount\n");
        return;
    }

// Check if transaction amount is below max amount
    terminalError = isBelowMaxAmount(&terminalData);
    if (terminalError != TERMINAL_OK) {
        printf("Declined Amount Exceeding Limit\n");
        return;
    }

    trans.cardHolderData = cardData;
    trans.terminalData = terminalData;
    saveTransaction(&trans);
    transState = receiveTransactionData(&trans);
    if (transState == APPROVED) {
        printf("Transaction Complete\n");
        //print account balance after transaction
        printf("Account balance %.2f\n", accountsDB[accountRef].balance);
    } else if (transState == DECLINED_INSUFFICIENT_FUND) {
        printf("Declined Insufficient Funds\n");
        return;
    } else if (transState == DECLINED_STOLEN_CARD) {
        printf("Declined Stolen Card\n");
        return;
    } else if (transState == FRAUD_CARD) {
        printf("Declined Invalid Account\n");
        return;
    } else {
        printf("Declined Internal Server Error\n");
        return;
    }
    listSavedTransactions();
}