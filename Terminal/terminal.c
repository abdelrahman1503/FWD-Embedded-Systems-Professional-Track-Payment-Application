#define _CRT_SECURE_NO_WARNINGS
#include "terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)	
{
	SYSTEMTIME T;
	GetLocalTime(&T);									
	printf("your transaction date is ");				 
	printf("%d/%d/%d\n", (T.wDay), (T.wMonth), (T.wYear));		

	if (T.wDay < 10) {										
		termData->transactionDate[0] = '0';					 
		termData->transactionDate[1] = T.wDay + '0';		
	}
	else {
		termData->transactionDate[0] = T.wDay / 10 + '0';		 
		termData->transactionDate[1] = T.wDay % 10 + '0';		 
	}
	termData->transactionDate[2] = '/';
	if (T.wMonth < 10) {
		termData->transactionDate[3] = '0';		
		termData->transactionDate[4] = T.wMonth + '0';		
	}
	else {
		termData->transactionDate[3] = T.wMonth / 10 + '0';		
		termData->transactionDate[4] = T.wMonth % 10 + '0';		
	}
	termData->transactionDate[5] = '/';
	termData->transactionDate[9] = T.wYear % 10 + '0';						 
	termData->transactionDate[8] = (T.wYear % 100) / 10 + '0';				 
	termData->transactionDate[7] = (T.wYear % 1000) / 100 + '0';			 
	termData->transactionDate[6] = T.wYear / 1000 + '0';					
}





EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)	
{
	if (cardData.cardExpirationDate[3] < termData.transactionDate[8])				
	{
		return EXPIRED_CARD;
	}
	else if (cardData.cardExpirationDate[3] > termData.transactionDate[8])
	{
		return ok;
	}
	else {
		if (cardData.cardExpirationDate[4] < termData.transactionDate[9])		
		{
			return EXPIRED_CARD;
		}
		else if (cardData.cardExpirationDate[4] > termData.transactionDate[9])
		{
			return ok;
		}
		else {
			if (cardData.cardExpirationDate[0] < termData.transactionDate[3])					
			{
				return EXPIRED_CARD;
			}
			else if (cardData.cardExpirationDate[0] > termData.transactionDate[3])
			{
				return ok;
			}
			else {
				if (cardData.cardExpirationDate[1] < termData.transactionDate[4])
				{
					return EXPIRED_CARD;
				}
				else if (cardData.cardExpirationDate[1] >= termData.transactionDate[4])
				{
					return ok;
				}
			}
		}
	}
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please enter the max trans amount:");
	scanf("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else
		return ok;

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the transaction amount: ");
	scanf("%f", &termData->transAmount);

	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return ok;
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
		return ok;
	}
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	if (cardData->primaryAccountNumber == NULL || strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
	{
		return WRONG_PAN;
	}
	else
	{
		return ok;
	}
}