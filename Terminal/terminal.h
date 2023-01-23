#include "../STD_Types.h"
#include "../Card/card.h"
#include <time.h>
#include <stdbool.h>



#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);  //Get current local date
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData); //checks if card expiry date inputted by user is lower than current date
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData); //Get the transaction amount to be paid by the user
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData); // checks if transaction amount is below the max amount of the terminal
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount); //set max transaction amount

// Test Functions
void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);




#endif // TERMINAL_H