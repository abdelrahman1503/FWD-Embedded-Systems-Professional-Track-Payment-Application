#define _CRT_SECURE_NO_WARNINGS
#include "server.h"


ST_accountsDB_t validAccounts[MAX] = { {1500.0,"4533881188690219"}, {1200.0, "4433162236573165"}, {1200.0, "4556828140086780"}, {25000.0, "4485759705949193"}, {100000.0, "4532770207325744"}, {55.67, "4485306981729038"}, {0.42, "4539366677402635"}, {55015.78, "4929995741957790"}, {784521.44, "4532896747835197"}, {15550.12, "4705999483881101"}, {2.01, "4946098864618213"}, {700.45, "4127849449840214"}, {4123.00, "4728451712765286"}, {4076.22, "4834698526489062"}, {512.12, "5303613783769063"}, {1024.55, "5104384462681117"}, {87003.76, "5138835136225953"}, {77004, "5138832892529777"}, {750458.22, "5258369812233929"}, {38145.00, "5436267103862965"}, {4780.23,"5407871122593009"}, {90895.98, "5436809364852746"}, {11054.21, "5436804204583866"}, {74125.89, "5406065775410121"}, {96325.87, "5197378450974029"}, {78945.63, "5370239931638857"}, {15987.62, "5138836665193398"}, {12378.94, "5258364342504832"}, {75322.11,"5172177216600335"}, {78912.46, "5104989367679832"}, {40025.69,"5105207891965919"}, {16987.55, "5406061377354320"}, {4216.00, "5138833395349911"}, {421600.33, "5370237807153084"}};

ST_transaction_t transactionData[MAX];
int counter;



EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int x;
	for (counter =0; counter < MAX ; ++counter)
	{
		x = strcmp(validAccounts[counter].primaryAccountNumber, cardData->primaryAccountNumber);
		if (x == 0)
		{
			return Ok;
		}



	}
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if ((termData->transAmount) <= validAccounts[counter].balance)
		return Ok;
	else
		return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	static int count_i;
	strcpy(transactionData[count_i].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
	strcpy(transactionData[count_i].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
	strcpy(transactionData[count_i].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
	transactionData[count_i].terminalData.transAmount = transData->terminalData.transAmount;
	strcpy(transactionData[count_i].terminalData.transactionDate, transData->terminalData.transactionDate);
	transactionData[count_i].transState = transData->transState;
	transactionData[count_i].transactionSequenceNumber = count_i + 1;
	count_i++;
	return Ok;
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData) == DECLINED_STOLEN_CARD)
		return DECLINED_STOLEN_CARD;
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
		return LOW_BALANCE;
	else
	{
		validAccounts[counter].balance = validAccounts[counter].balance - transData->terminalData.transAmount;
		saveTransaction(&transData);
		printf("Successful Transaction\n");
	}
}





EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	int i;
	for (i = 0; i < MAX ; i++)
	{
		if (transactionSequenceNumber == transactionData[i].transactionSequenceNumber)
		{

			return Ok;
		}
	}
	return TRANSACTION_NOT_FOUND;
}


