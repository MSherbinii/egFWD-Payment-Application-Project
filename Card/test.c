#include "card.h"
void getCardHolderNameTest(void) {
    EN_cardError_t result;
    ST_cardData_t cardData;

    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: getCardHolderName\n\n");

    // Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: Mohamed Ahmed Sherbini\n");
    printf("Expected Result: CARD_OK\n");
    result = getCardHolderName(&cardData);
    if (result == CARD_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

    // Test Case 2: Invalid Name (contains digits)
    printf("\nTest Case 2:\n");
    printf("Input Data: M0hamedM0hamedM0hamed\n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(&cardData);
    if (result == WRONG_NAME) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }

    // Test Case 3: Name too short
    printf("\nTest Case 3:\n");
    printf("Input Data: Mohamed\n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(&cardData);
    if (result == WRONG_NAME) {
        printf("Test Case 3: Passed\n");
    } else {
        printf("Test Case 3: Failed\n");
    }

    // Test Case 4: Name too long
    printf("\nTest Case 4:\n");
    printf("Input Data: MohamedMohamedMohamedMohamed\n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(&cardData);
    if (result == WRONG_NAME) {
        printf("Test Case 4: Passed\n");
    } else {
        printf("Test Case 4: Failed\n");
    }

    // Test Case 5: Empty input
    printf("\nTest Case 5:\n");
    printf("Input Data: \n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(NULL);
    if (result == WRONG_NAME) {
        printf("Test Case 5: Passed\n");
    } else {
        printf("Test Case 5: Failed\n");
    }
}
void getCardExpiryDateTest(void) {
    EN_cardError_t result;
    ST_cardData_t cardData;
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: getCardExpiryDate\n\n");

// Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: 05/25\n");
    printf("Expected Result: CARD_OK\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == CARD_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Invalid month (month > 12)
    printf("\nTest Case 2:\n");
    printf("Input Data: 15/25\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_EXP_DATE) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }

// Test Case 3: Invalid year (year < 23)
    printf("\nTest Case 3:\n");
    printf("Input Data: 05/19\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_EXP_DATE) {
        printf ("Test Case 3: Passed\n");
    } else {
        printf("Test Case 3: Failed\n");
    }

// Test Case 4: Invalid format (missing '/')
    printf("\nTest Case 4:\n");
    printf("Input Data: 0525\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_EXP_DATE) {
        printf("Test Case 4: Passed\n");
    } else {
        printf("Test Case 4: Failed\n");
    }

// Test Case 5: Empty input
    printf("\nTest Case 5:\n");
    printf("Input Data: \n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_EXP_DATE) {
        printf("Test Case 5: Passed\n");
    } else {
        printf("Test Case 5: Failed\n");
    }
    // Test Case 6: More than 5
    printf("\nTest Case 5:\n");
    printf("Input Data: 05/255\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_EXP_DATE) {
        printf("Test Case 5: Passed\n");
    } else {
        printf("Test Case 5: Failed\n");
    }
}


void getCardPANTest(void) {
    ST_cardData_t cardData;
    EN_cardError_t result;
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: getCardPAN\n\n");

// Test Case 1: Happy Case
    printf("Test Case 1:\n");
    printf("Input Data: 12345678901234567\n");
    printf("Expected Result: CARD_OK\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == CARD_OK) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

// Test Case 2: Invalid PAN (less than 16 characters)
    printf("\nTest Case 2:\n");
    printf("Input Data: 123456789012345\n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_PAN) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }

// Test Case 3: Invalid PAN (more than 19 characters)
    printf("\nTest Case 3:\n");
    printf("Input Data: 12345678901234567890\n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_PAN) {
        printf("Test Case 3: Passed\n");
    } else {
        printf("Test Case 3: Failed\n");
    }

// Test Case 4: Invalid PAN (contains non-numeric characters)
    getchar();
    printf("\nTest Case 4:\n");
    printf("Input Data: 1234567890123456a\n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_PAN) {
        printf("Test Case 4: Passed\n");
    } else {
        printf("Test Case 4: Failed\n");
    }

// Test Case 5: Empty input
    printf("\nTest Case 5:\n");
    printf("Input Data: \n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %d\n",result);
    if (result == WRONG_PAN) {
        printf("Test Case 5: Passed\n");
    } else {
        printf("Test Case 5: Failed\n");
    }
}