#define _CRT_SECURE_NO_WARNINGS
#include "app.h"
#include "server.h"


void appStart(void)
{
	while (1)
	{
		ST_cardData_t cardData;
		ST_terminalData_t termData;
		ST_transaction_t transData;

		if (setMaxAmount(&transData.terminalData) == INVALID_MAX_AMOUNT)
		{
			printf("Invalid\n");
			return 0;
		}
		if (getCardHolderName(&transData.cardHolderData) == WRONG_NAME)
		{
			printf("Wrong name\n");
			return 0;
		}
		if (getCardExpiryDate(&transData.cardHolderData) == WRONG_EXP_DATE)
		{
			printf("Wrong date format\n");
			return 0;
		}
		if (getCardPAN(&transData.cardHolderData) == WRONG_PAN)
		{
			printf("Wrong PAN\n");
			return 0;
		}

		if (getTransactionDate(&transData.terminalData) == WRONG_DATE)
		{
			printf("Wrong Date");
			return 0;
		}
		if (isCardExpired(transData.cardHolderData, transData.terminalData) == EXPIRED_CARD)
		{
			printf("Expired Card\n");
			return 0;
		}
		if (getTransactionAmount(&transData.terminalData) == INVALID_AMOUNT)
		{
			printf("Invalid Amount.\n");
			return 0;
		}
		if (isBelowMaxAmount(&transData.terminalData) == EXCEED_MAX_AMOUNT)
		{
			printf("Maximum Amount Exceeded");
			return 0;
		}
		if (isValidAccount(&transData.cardHolderData) == DECLINED_STOLEN_CARD)
		{
			printf("Invalid Account\n");
			return 0;
		}
		else if (isAmountAvailable(&transData.terminalData) == LOW_BALANCE)
		{
			printf("Insufficient Money\n");
			return 0;
		}
		
		printf("Successful Transaction\n");
		validAccounts[counter].balance -= transData.terminalData.transAmount;
		printf("Your new balance is: %f\n", validAccounts[counter].balance);
		
		return 0;
		

	}
}