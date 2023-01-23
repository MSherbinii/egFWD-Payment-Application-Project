#include "terminal.h"
void getTransactionDateTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: getTransactionDate\n\n");
    ST_terminalData_t termData;
    EN_terminalError_t result;

// Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: None\n");
    printf("Expected Result: TERMINAL_OK\n");
    result = getTransactionDate(&termData);
    if (result == TERMINAL_OK) {
        printf("Test Case 1: Passed\n");
        printf("Actual Result: %s\n", termData.transactionDate);
    } else {
        printf("Test Case 1: Failed\n");
    }
}

void isCardExpiredTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isCardExpired\n\n");
    ST_cardData_t cardData;
    strcpy(cardData.cardExpirationDate, "06/23");
    ST_terminalData_t termData;
    getTransactionDate(&termData);
    EN_terminalError_t result;
    // Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: card expiration date 06/23, current transaction date: %s\n", termData.transactionDate);
    printf("Expected Result: TERMINAL_OK\n");
    result = isCardExpired(&cardData, &termData);
    printf("Actual Result: %d\n",result);
    if (result == TERMINAL_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Expired Card
    printf("Test Case 2:\n");
    strcpy(cardData.cardExpirationDate, "06/22");
    printf("Input Data: card expiration date 06/22, current transaction date: %s\n", termData.transactionDate);
    printf("Expected Result: EXPIRED_CARD\n");
    result = isCardExpired(&cardData, &termData);
    printf("Actual Result: %d\n",result);
    if (result == EXPIRED_CARD) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }
}
void getTransactionAmountTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: getTransactionAmount\n\n");
    ST_terminalData_t termData;
    EN_terminalError_t result;
    // Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: 100\n");
    printf("Expected Result: TERMINAL_OK\n");
    result = getTransactionAmount(&termData);
    printf("Actual Result: %d\n", result);
    if (result == TERMINAL_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Invalid Amount
    printf("Test Case 2:\n");
    printf("Input Data: 0\n");
    printf("Expected Result: INVALID_AMOUNT\n");
    result = getTransactionAmount(&termData);
    printf("Actual Result: %d\n", result);
    if (result == INVALID_AMOUNT) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }

}
void setMaxAmountTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: setMaxAmount\n\n");
    ST_terminalData_t termData;
    EN_terminalError_t result;
    // Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: 100\n");
    printf("Expected Result: TERMINAL_OK\n");
    result = setMaxAmount(&termData, 100);
    printf("Actual Result: %d\n",result);
    if (result == TERMINAL_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Invalid max amount
    printf("\nTest Case 2:\n");
    printf("Input Data: 0\n");
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    result = setMaxAmount(&termData, 0);
    printf("Actual Result: %d\n",result);
    if (result == INVALID_MAX_AMOUNT) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }
}

/* void isValidCardPANTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isValidCardPAN\n\n");

    ST_cardData_t cardData;
    EN_terminalError_t result;

// Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: 4929091247672358\n");
    printf("Expected Result: TERMINAL_OK\n");
    memcpy(cardData.primaryAccountNumber, "4929091247672358", 16);
    result = isValidCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == TERMINAL_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Invalid Card
    printf("Test Case 2:\n");
    printf("Input Data: 4929091247672350\n");
    printf("Expected Result: INVALID_CARD\n");
    memcpy(cardData.primaryAccountNumber, "4929091247672350", 16);
    result = isValidCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == INVALID_CARD) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }
}
*/
void isBelowMaxAmountTest(void)
{
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isBelowMaxAmount\n\n");
    ST_terminalData_t termData;
    EN_terminalError_t result;

// Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: transAmount = 50, maxTransAmount = 100\n");
    printf("Expected Result: TERMINAL_OK\n");
    termData.transAmount = 50;
    termData.maxTransAmount = 100;
    result = isBelowMaxAmount(&termData);
    printf("Actual Result: %d\n",result);
    if (result == TERMINAL_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Worst Case
    printf("Test Case 2:\n");
    printf("Input Data: transAmount = 150, maxTransAmount = 100\n");
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    termData.transAmount = 150;
    termData.maxTransAmount = 100;
    result = isBelowMaxAmount(&termData);
    printf("Actual Result: %d\n",result);

    if (result == EXCEED_MAX_AMOUNT) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }
}



