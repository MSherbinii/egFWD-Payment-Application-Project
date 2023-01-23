#include "server.h"
#include "db.h"
/*
void receiveTransactionDataTest(void) {
    ST_transaction_t transData1 = {
            { "Mohamed El Sherbini", "4550746475531533", "12/25" },
            { 5000 },
            0
    };
    ST_transaction_t transData2 = {
            { "Mohamed El Sherbini", "1234567812345678", "12/25" },
            { 5000 },
            0
    };
    ST_transaction_t transData3 = {
            { "Mohamed El Sherbini", "4699094091899964", "12/25" },
            { 5000 },
            0
    };
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: receiveTransactionData\n");

    printf("Test Case 1:\n");
    printf("Input Data: Account number: 4550746475531533, Amount: 5000\n");
    printf("Expected Result: APPROVED\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData1));

    printf("Test Case 2:\n");
    printf("Input Data: Account number: 1234567812345678, Amount: 5000\n");
    printf("Expected Result: FRAUD_CARD\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData2));

    printf("Test Case 3:\n");
    printf("Input Data: Account number: 4699094091899964, Amount: 5000\n");
    printf("Expected Result: DECLINED_STOLEN_CARD\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData3));
}

void isValidAccountTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isValidAccount\n");
    ST_cardData_t cardData;
    ST_accountsDB_t accountReference;
    EN_serverError_t result;
    // Test Case 1: valid account
    strcpy(cardData.primaryAccountNumber, "4550746475531533");
    result = isValidAccount(&cardData);
    printf("Test Case 1:\n");
    printf("Input Data: PAN = %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", result);
    // Test Case 2: invalid account
    strcpy(cardData.primaryAccountNumber, "1234567812345678");
    result = isValidAccount(&cardData);
    printf("Test Case 2:\n");
    printf("Input Data: PAN = %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %d\n", result);
}
void isBlockedAccountTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isBlockedAccount\n");
    ST_accountsDB_t accountReference;
    EN_serverError_t result;
    // Test Case 1: running account
    accountReference = accountsDB[0];
    result = isBlockedAccount(&accountReference);
    printf("Test Case 1:\n");
    printf("Input Data: Account Reference = %d\n", accountReference.accountReference);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", result);
    // Test Case 2: blocked account
    accountReference = accountsDB[1];
    result = isBlockedAccount(&accountReference);
    printf("Test Case 2:\n");
    printf("Input Data: Account Reference = %d\n", accountReference.accountReference);
    printf("Expected Result: BLOCKED_ACCOUNT\n");
    printf("Actual Result: %d\n", result);
}
void isAmountAvailableTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isAmountAvailable\n");
    ST_terminalData_t termData = {2000};
    ST_accountsDB_t accountReference;
    EN_serverError_t result;
    // Test Case 1: sufficient balance
    accountReference = accountsDB[0];
    result = isAmountAvailable(&termData, &accountReference);
    printf("Test Case 1:\n");
    printf("Input Data: Account Reference = %d, Transaction Amount = %f\n", accountReference.accountReference, termData.transAmount);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", result);
    // Test Case 2: insufficient balance
    termData.transAmount = 20000;
    result = isAmountAvailable(&termData, &accountReference);
    printf("Test Case 2:\n");
    printf("Input Data: Account Reference = %d, Transaction Amount = %f\n", accountReference.accountReference, termData.transAmount);
    printf("Expected Result: LOW_BALANCE\n");
    printf("Actual Result: %d\n", result);
}
void saveTransactionTest(void) {
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: saveTransaction\n");
    ST_transaction_t transData1 = {
            { "Mohamed Ahmed Sherbini", "4550746475531533", "07/28", },
            { 200.0, 2500, "01/23/2023" },
            APPROVED, 0
    };
    ST_transaction_t transData2 = {
            { "Mohamed Ahmed Sherbini", "4683982334261711", "06/25" },
            { 1200.0, 2500.0, "01/23/2023" },
            DECLINED_INSUFFICIENT_FUND, 1
    };
    printf("Test Case 1:\n");
    printf("Input Data: transData1\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", saveTransaction(&transData1));
    printf("Test Case 2:\n");
    printf("Input Data: transData2\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", saveTransaction(&transData2));
    listSavedTransactions();
}
void receiveTransactionDataTest(void) {
    ST_transaction_t transData;
    // Test Case 1: Valid account, sufficient funds, and not blocked
    strcpy(transData.cardHolderData.primaryAccountNumber,"4550746475531533");
    transData.terminalData.transAmount = 500;
    printf("Test Case 1:\n");
    printf("Input Data: Valid account, sufficient funds, and not blocked\n");
    printf("Expected Result: APPROVED\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData));

    // Test Case 2: Invalid account
    strcpy(transData.cardHolderData.primaryAccountNumber,"0000000000000001");
    transData.terminalData.transAmount = 500;
    printf("Test Case 2:\n");
    printf("Input Data: Invalid account\n");
    printf("Expected Result: FRAUD_CARD\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData));

    // Test Case 3: Account blocked
    strcpy(transData.cardHolderData.primaryAccountNumber,"4699094091899964");
    transData.terminalData.transAmount = 500;
    printf("Test Case 3:\n");
    printf("Input Data: Account blocked\n");
    printf("Expected Result: DECLINED_STOLEN_CARD\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData));

    // Test Case 4: Insufficient funds
    strcpy(transData.cardHolderData.primaryAccountNumber,"4550746475531533");
    transData.terminalData.transAmount = 20000;
    printf("Test Case 4:\n");
    printf("Input Data: Insufficient funds\n");
    printf("Expected Result: DECLINED_INSUFFICIENT_FUND\n");
    printf("Actual Result: %d\n", receiveTransactionData(&transData));
}




/*
void isBlockedAccountTest(void) {
    ST_accountsDB_t accountReference2, accountReference3;
    memset(&accountReference2, 0, sizeof(ST_accountsDB_t));
    memset(&accountReference3, 0, sizeof(ST_accountsDB_t));
// Test Case 1: Account is Blocked
    printf("Test Case 2:\n");
    accountReference2.state = BLOCKED;
    printf("Input Data: accountReference2 = BLOCKED\nExpected Result: BLOCKED_ACCOUNT\nActual Result: ");
    EN_serverError_t result = isBlockedAccount(&accountReference2);
    printf("%d\n", result);

// Test Case 2: Account is Running
    printf("Test Case 3:\n");
    accountReference3.state = RUNNING;
    printf("Input Data: accountReference3 = RUNNING\nExpected Result: SERVER_OK\nActual Result: ");
    result = isBlockedAccount(&accountReference3);
    printf("%d\n", result);
}

void isAmountAvailableTest(void) {
    ST_terminalData_t termData1 = {5000};
    ST_accountsDB_t accountReference1 = {10000, RUNNING, "4550746475531533"};
    ST_terminalData_t termData2 = {20000};
    ST_accountsDB_t accountReference2 = {10000, RUNNING, "4550746475531533"};

    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isAmountAvailable\n");
    printf("Test Case 1:\n");
    printf("Input Data: termData1 = { 5000 }, accountReference1 = { 10000, RUNNING, \"4550746475531533\" }\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", isAmountAvailable(&termData1, &accountReference1));

    printf("Test Case 2:\n");
    printf("Input Data: termData2 = { 20000 }, accountReference2 = { 10000, RUNNING, \"4550746475531533\" }\n");
    printf("Expected Result: LOW_BALANCE\n");
    printf("Actual Result: %d\n");
}
void saveTransactionTest(void) {
    ST_transaction_t transData1 = {{"Mohamed El Sherbini", "4550746475531533", "12/25"}, {5000}, APPROVED, 0};
    ST_transaction_t transData2 = {{"Mohamed El Sherbini", "1234567812345678", "12/25"}, {5000}, ACCOUNT_NOT_FOUND, 0};
    ST_transaction_t transData3 = {{"Mohamed El Sherbini", "4699094091899964", "12/25"}, {5000}, APPROVED, 0};
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: saveTransaction\n");
    printf("Test Case 1:\n");
    printf("Input Data: transData1 = {{ \"Mohamed El Sherbini\", \"4550746475531533\", \"12/25\" }, { 5000 }, APPROVED, 0}\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", saveTransaction(&transData1));

    printf("Test Case 2:\n");
    printf("Input Data: transData2 = {{ \"Mohamed El Sherbini\", \"1234567812345678\", \"12/25\" }, { 5000 }, DECLINED, 0}\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", saveTransaction(&transData2));

    printf("Test Case 3:\n");
    printf("Input Data: transData3 = {{ \"Mohamed El Sherbini\", \"4699094091899964\", \"12/25\" }, { 5000 }, APPROVED, 0}\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", saveTransaction(&transData3));
}

void listSavedTransactionsTest(void) {
    ST_transaction_t transData1 = {
            { "Mohamed El Sherbini", "4550746475531533", "12/25" },
            { 5000, 10000, "12/25" },
            APPROVED
    };
    saveTransaction(&transData1);
    ST_transaction_t transData2 = {
            { "Mohamed El Sherbini", "4699094091899964", "12/25" },
            { 6000, 12000, "12/25" },
            BLOCKED_ACCOUNT
    };
    saveTransaction(&transData2);
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: listSavedTransactions\n");
    listSavedTransactions();
}
 */