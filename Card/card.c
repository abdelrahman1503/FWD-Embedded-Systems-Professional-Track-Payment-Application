
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter the card holder name: ");
	getchar();
	gets(cardData->cardHolderName);
	int x = strlen(cardData->cardHolderName);
	if (x >= 20 && x <= 24)
	{
		return OK;
	}
	else
	{
		return WRONG_NAME;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter the card expiry date in the format MM/YY: ");
	gets(cardData->cardExpirationDate);
	int x = strlen(cardData->cardExpirationDate);
	if (x == 5 && cardData->cardExpirationDate[2]=='/' && cardData->cardExpirationDate[0]<'2')
	{
		if (cardData->cardExpirationDate[0] == '1')
		{
			if (cardData->cardExpirationDate[1] == '0' || cardData->cardExpirationDate[1] == '1' || cardData->cardExpirationDate[1] == '2')
				return OK;
			else
				return WRONG_EXP_DATE;
		}
			
		else if (cardData->cardExpirationDate[0] == '0')
		{
			if (cardData->cardExpirationDate[1] > '0')
				return OK;
			else
				return WRONG_EXP_DATE;
		}
		
	}
	else
	{
		return WRONG_EXP_DATE;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter the card PAN: ");
	gets(cardData->primaryAccountNumber);
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++)
	{
		if (cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i]>'9')
			return WRONG_PAN;
	}
	int x = strlen(cardData->primaryAccountNumber);
	if (x >= 16 && x <= 19)
	{
		return OK;
	}
	else
	{
		return WRONG_PAN;
	}
}
