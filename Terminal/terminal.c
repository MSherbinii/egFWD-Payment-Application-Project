#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);
    strftime((char*)termData->transactionDate, 11, "%d/%m/%Y", localTime);

    return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
    char transDate[11];
    char expiryDate[6];
    char *token;
    int transMonth, transYear, expiryMonth, expiryYear;
    strcpy(transDate, (char *) termData->transactionDate);
    strcpy(expiryDate, (char *) cardData->cardExpirationDate);

// Extracting the transaction month and year
    token = strtok(transDate, "/");
    token = strtok(NULL, "/");
    transMonth = strtol(token, NULL, 10);
    token = strtok(NULL, "/");
    transYear = strtol(token + 2, NULL, 10)%100;

// Extracting the expiry month and year
    token = strtok(expiryDate, "/");
    expiryMonth = strtol(token, NULL, 10);
    token = strtok(NULL, "/");
    expiryYear = strtol(token, NULL, 10);

// Compare the expiry date with the transaction date
    if (transYear > expiryYear) {
        return EXPIRED_CARD;
    } else if (transYear == expiryYear) {
        if (transMonth > expiryMonth) {
            return EXPIRED_CARD;
        }
    }

    return TERMINAL_OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    printf("Please enter transaction amount: ");
    float transAmount;
    scanf("%f", &transAmount);

    if (transAmount <= 0) {
        return INVALID_AMOUNT;
    } else {
        termData->transAmount = transAmount;
        return TERMINAL_OK;
    }
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount) {
    if (maxAmount <= 0) {
        return INVALID_MAX_AMOUNT;
    } else {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    }
}

/*EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
    int sum = 0;
    size_t len = strlen((char*)cardData->primaryAccountNumber);
    bool isSecond = false;
    for (size_t i=len-1; i < len; i--) {
        int n = cardData->primaryAccountNumber[i] - '0';
        if (isSecond == true) n = n * 2;
        sum += n / 10;
        sum += n % 10;
        isSecond = !isSecond;
    }
    if (sum % 10 == 0) {
        return TERMINAL_OK;
    } else {
        return INVALID_CARD;
    }
}
*/
