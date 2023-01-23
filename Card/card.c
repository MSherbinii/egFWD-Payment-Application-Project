#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    printf("Please enter card holder's name : ");

    char name[26];
    if (fgets(name, sizeof(name), stdin) != NULL)
    {
        size_t len = strlen(name);
        if (name[len-1] == '\n')
        {
            name[len-1] = '\0';
            len--;
        }
        if ((len >= 20) && (len <= 24))
        {
            for (size_t i = 0; i < len; i++)
            {
                if (isdigit(name[i]))
                {
                    return WRONG_NAME;
                }
            }
            strncpy((char*)cardData->cardHolderName, name,len);
            cardData->cardHolderName[len] = '\0';
            return CARD_OK;
        }
    }
    return WRONG_NAME;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    printf("Please enter card expiry date in the format MM/YY: ");

    char expiryDate[7];
    int monthNum, yearNum;
    char input[7];
    fgets(input, sizeof(input), stdin);
    if (input[0] == '\n') {
        return WRONG_EXP_DATE;
    }
    char *pEnd;
    monthNum = (int) strtol(strtok(input, "/"), &pEnd, 10);
    yearNum = (int) strtol(strtok(NULL, "/"), &pEnd, 10);
    if ((monthNum >= 1) && (monthNum <= 12) && (yearNum >= 23) && (yearNum <= 99)) {
        sprintf(expiryDate, "%d/%d", monthNum, yearNum);
        strncpy((char *) cardData->cardExpirationDate, expiryDate, 6);
        return CARD_OK;
    }
    return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    printf("Please enter card's Primary Account Number: ");

    char PAN[21];
    if (fgets(PAN, sizeof(PAN), stdin) != NULL)
    {
        size_t len = strlen(PAN);
        if (PAN[len-1] == '\n')
        {
            PAN[len-1] = '\0';
            len--;
        }
        if ((len >= 16) && (len <= 19))
        {
            for (size_t i = 0; i < len; i++)
            {
                if (!isdigit(PAN[i]))
                {
                    return WRONG_PAN;
                }
            }
            strncpy((char*)cardData->primaryAccountNumber, PAN,len);
            cardData->primaryAccountNumber[len] = '\0';
            return CARD_OK;
        }
    }
    return WRONG_PAN;
}
