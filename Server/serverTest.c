#include "server.h"

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
    ST_cardData_t cardData1 = { "Mohamed El Sherbini", "4683982334261711", "12/25" };
    ST_cardData_t cardData2 = { "Mohamed El Sherbini", "1234567812345678", "12/25" };
    ST_accountsDB_t accountReference1;
    ST_accountsDB_t accountReference2;
    printf("Tester Name: Mohamed El Sherbini\n");
    printf("Function Name: isValidAccount\n");
    printf("Test Case 1:\n");
    printf("Input Data: cardData1 = { \"4550746475531533\", \"Mohamed El Sherbini\", \"12/25\" }\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %d\n", isValidAccount(&cardData1, &accountReference1));

    printf("Test Case 2:\n");
    printf("Input Data: cardData2 = { \"1234567812345678\", \"Mohamed El Sherbini\", \"12/25\" }\n");
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %d\n", isValidAccount(&cardData2, &accountReference2));
}

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