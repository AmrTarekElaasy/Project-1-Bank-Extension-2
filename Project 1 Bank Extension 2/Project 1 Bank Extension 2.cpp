
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using  namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
const int encryptionCode = 900, decryptionCode = 900;
string ClientsComma = "#//#";
string UsersComma = "#//#";


int NumberOfClients(string FileName)
{
	string s1;
	int counter = 0;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		while (getline(File, s1))
		{
			if (s1 == "")
				break;
			counter++;
		}

	}

	File.close();
	return counter;

}
vector<string> SplitString(string S1, string Delimi)
{
	vector<string>vSplit;
	short pos = 0;
	string sWord = "";
	while ((pos = S1.find(Delimi)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vSplit.push_back(sWord);
		}
		S1.erase(0, pos + Delimi.length());
	}
	if (S1 != "")
	{
		vSplit.push_back(S1);
	}
	return vSplit;
}
void Encryption(string& s1, int encryptionCode = ::encryptionCode)
{

	for (short i = 0; i < s1.length(); i++)
	{
		s1[i] = char(s1[i] + encryptionCode);

	}

}
void Decryption(string& s1, int decryptionCode = ::decryptionCode)
{

	for (short i = 0; i < s1.length(); i++)
	{
		s1[i] = char(s1[i] - decryptionCode);

	}
}
struct sClient
{
	string AccounteNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool Delete = false;
};
struct sUser
{
	string UserName = "";
	string Password = "";
	short permission;

	bool Delete = false;
};
sUser User;
vector <sUser>VUsers;
vector <sClient>VClients;
void PrintNameOfScreen(string screenName, bool CLS = true)
{
	if (CLS)
	{
		system("cls");
	}

	cout << "=================================================\n";
	cout << "\t" << screenName << endl;
	cout << "=================================================\n";
}
short ReadShortNumber(string messeg, short from, short to)
{
	short input;
	cout << messeg;
	cin >> input;
	while (input<from || input>to || cin.fail())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		printf("Enter number from %d to %d : ", from, to);
		cin >> input;
	}
	return input;
}
bool SearchClient(vector <sClient>& vClients, string AccountNumber)
{

	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccounteNumber == AccountNumber)
		{

			return true;
		}

	}
	return false;
}
bool SearchUser(vector <sUser>& vUsers, sUser user)
{

	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == user.UserName)
		{

			return true;
		}

	}
	return false;
}
bool SearchUser(vector <sUser>& vUsers, string userName, int& index)
{

	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == userName)
		{
			index = i;
			return true;
		}

	}
	return false;
}
bool CheckLoginUser(vector <sUser>& vUsers, sUser& user)
{

	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == user.UserName)
		{
			if (vUsers[i].Password == user.Password)
			{
				user = vUsers[i];
				return true;
			}


		}

	}
	return false;
}
sClient ReadClient(vector <sClient>& clients, string AccounteNumber = "")
{
	sClient client;
	if (AccounteNumber != "")
	{
		client.AccounteNumber = AccounteNumber;
		cout << "Account Number " << client.AccounteNumber << endl;

	}
	else
	{
		cout << "Enter Account Number?";
		getline(cin >> ws, client.AccounteNumber);

		if (SearchClient(clients, client.AccounteNumber))
		{
			cout << "This Accounte Number Exists\n";
			return client;

		}
	}

	cout << "Enter PinCode?";
	getline(cin >> ws, client.PinCode);
	cout << "Enter Name?";
	getline(cin, client.Name);
	cout << "Enter Phone?";

	getline(cin, client.Phone);
	cout << "Enter Account Balance?";
	cin >> client.AccountBalance;



	return client;
}
void PrintClient(sClient& clients)
{
	printf("=========================================\n");
	cout << "Accounte Number : " << clients.AccounteNumber << endl;
	cout << "Pin Code        : " << clients.PinCode << endl;
	cout << "Name            : " << clients.Name << endl;
	cout << "Phone           : " << clients.Phone << endl;
	printf("Account Balance : %.*f \n", 2, clients.AccountBalance);
	printf("=========================================\n\n");

}
void PrintUser(sUser& user)
{
	printf("=========================================\n");
	cout << " User Name   : " << user.UserName << endl;
	cout << " Password    : " << user.Password << endl;
	cout << " permission  : " << user.permission << endl;
	printf("=========================================\n\n");


}
bool SearchClient(vector <sClient>& vClients, string AccountNumber, int& index)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccounteNumber == AccountNumber)
		{
			index = i;
			return true;
		}

	}
	return false;
}

bool SearchAndPrintClient(vector <sClient>& vClients, int& index)
{

	string search;
	cout << "Enter Account number ? ";
	cin >> search;

	if (SearchClient(vClients, search, index))
	{
		PrintClient(vClients[index]);
		return 1;

	}
	else
	{
		cout << "Not Found\n";
		return 0;
	}
}
bool SearchAndPrintUser(vector <sUser>& vUsers, int& index)
{

	string search;
	cout << " Enter User Number : ";
	cin >> search;
	if (SearchUser(vUsers, search, index))
	{
		if (::VUsers[index].UserName == "Admin" && ::User.UserName != "Admin")
		{
			std::cout << " This user cannot be shown or edited or deleted.\n";
			return 0;
		}
		else
		{
			PrintUser(vUsers[index]);
		}
		return 1;

	}
	else
	{
		cout << " Not Found\n";
		return 0;
	}
}
bool SearchAndPrintUser(vector <sUser>& vUsers, bool printNameOfScreen = true)
{
	int index;
	if (PrintNameOfScreen)
		PrintNameOfScreen("   Find User Screen");
	return SearchAndPrintUser(vUsers, index);
}
bool SearchAndPrintClient(vector <sClient>& vClients)
{

	string search; int index;
	system("cls");
	cout << "-----------------------------------------\n";
	cout << "\tClient Search screen\n";
	cout << "-----------------------------------------\n";
	cout << "Enter Account number ? ";
	cin >> search;
	if (SearchClient(vClients, search, index))
	{
		PrintClient(vClients[index]);
		cout << "Press any key to go back to Main Menue...";
		system("pause>0");
		return 1;

	}
	else
	{
		cout << "Is Not Found\n";

		cout << "Press any key to go back to Main Menue...";
		system("pause>0");
		return 0;
	}


}


string ConvertRecordClientsToLineWithEncryption(sClient client, string ClientsComma)
{
	string stClientRecord = "";
	stClientRecord += client.AccounteNumber + ClientsComma;
	stClientRecord += client.PinCode + ClientsComma;
	stClientRecord += client.Name + ClientsComma;
	stClientRecord += client.Phone + ClientsComma;
	stClientRecord += to_string(client.AccountBalance);
	Encryption(stClientRecord);
	return stClientRecord;
}

string ConvertRecordUsersToLineWithEncryption(sUser user, string usersComma)
{
	if (user.Delete)
		return "";
	string stClientRecord = "";
	stClientRecord += user.UserName + usersComma;
	stClientRecord += user.Password + usersComma;
	stClientRecord += to_string(user.permission);

	Encryption(stClientRecord);
	return stClientRecord;
}
string ConvertRecordUsersToLineWithEncryption(sUser user)
{
	return ConvertRecordUsersToLineWithEncryption(user, ::UsersComma);
}
sClient LineClientsToRecordWithDecryption(string s1, string ClientsComma)
{
	sClient client;
	vector <string> vRecords;
	Decryption(s1);
	vRecords = SplitString(s1, ClientsComma);
	if (vRecords.size() > 3)
	{
		client.AccounteNumber = vRecords[0];
		client.PinCode = vRecords[1];
		client.Name = vRecords[2];
		client.Phone = vRecords[3];
		client.AccountBalance = stod(vRecords[4]);
	}
	else
	{
		cout << "Text Splitting problem\n";
	}



	return client;

}
sUser LineUsersToRecordWithDecryption(string s1, string usersComma)
{
	sUser user;
	vector <string> vRecords;
	Decryption(s1);
	vRecords = SplitString(s1, UsersComma);
	if (vRecords.size() >= 3)
	{
		user.UserName = vRecords[0];
		user.Password = vRecords[1];
		user.permission = stoi(vRecords[2]);

	}
	else
	{
		cout << "Text Splitting problem In Users File\n";
	}



	return user;

}
void PrintRecordOfClient(sClient client)
{
	cout << "Account Number : " << client.AccounteNumber << endl;
	cout << "PinCode: " << client.PinCode << endl;
	cout << "Name: " << client.Name << endl;
	cout << "Phone: " << client.Phone << endl;
	cout << "Account Balance: " << client.AccountBalance << endl;
}
void SaveStringInFile(string s1, bool saveOldString, string FileName)
{
	fstream file;
	if (saveOldString)
	{
		file.open(FileName, ios::out | ios::app);
	}
	else
	{
		file.open(FileName, ios::out);
	}


	if (file.is_open())
	{
		file << s1 << endl;
	}
	file.close();
}
void AddClient()
{

	string AddMore = "Y";
	string s1;

	do
	{
		system("cls");
		cout << "-----------------------------------------\n";
		cout << "\tAdd New Client screen\n";
		cout << "-----------------------------------------\n";

		::VClients.push_back(ReadClient(::VClients));
		if (::VClients.back().Name != "")
		{

			s1 = ConvertRecordClientsToLineWithEncryption(::VClients.back(), ::ClientsComma);
			SaveStringInFile(s1, 1, ::ClientsFileName);
		}



		cout << "Do you need add more client Y/N ? ";
		cin >> AddMore;


	} while (AddMore == "y" || AddMore == "Y");
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
}
enum enPermission { enAll = -1, enClientsList = 1, enAddClient = 2, enDeleteClient = 4, enUpdateClient = 8, enFindClient = 16, enTransactions = 32, enManageUsers = 64 };
bool checkPermission(sUser user, enPermission permisson)
{
	if ((user.permission & permisson) || (user.permission == enPermission::enAll))
	{
		return true;
	}
	return false;
}
bool checkPermissionAndPrint(sUser user, enPermission permisson)
{
	if (checkPermission(user, permisson))
		return true;

	cout << "You do not have a permission\n";
	system("pause");
	return false;

}
short ReadPermission(string userName)
{
	short permissions = 0;
	string yOrN = "";

	cout << "Do you want to give all the permissions y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		return enPermission::enAll;

	cout << "Do you want to give him permission to show Clients List y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		permissions += enPermission::enClientsList;

	cout << "Do you want to give him permission to Add Client y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		permissions += enPermission::enAddClient;

	cout << "Do you want to give him permission to Delete Client y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		permissions += enPermission::enDeleteClient;

	cout << "Do you want to give him permission to Update Client y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		permissions += enPermission::enUpdateClient;

	cout << "Do you want to give him permission to Find Client y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		permissions += enPermission::enFindClient;

	cout << "Do you want to give him permission to Transactions y/n ? ";
	cin >> yOrN;
	if (yOrN == "y" || yOrN == "Y")
		permissions += enPermission::enTransactions;

	if (userName == "Admin")
	{
		permissions += enPermission::enManageUsers;
	}
	else
	{
		cout << "Do you want to give him permission to Manage Users y/n ? ";
		cin >> yOrN;
		if (yOrN == "y" || yOrN == "Y")
			permissions += enPermission::enManageUsers;
	}

	return permissions;
}
sUser ReadUser(string userName = "")
{
	sUser user;
	if (userName == "")
	{
		cout << "Enter User Name : ";
		getline(cin >> ws, user.UserName);
		while (SearchUser(::VUsers, user))
		{
			cout << "The User Name Is Exist\n";
			cout << "Enter User Name : ";
			getline(cin >> ws, user.UserName);
		}
	}
	else
	{
		user.UserName = userName;
	}

	user.Password = "";
	while (user.Password == "")
	{
		cout << "Enter Password : ";
		getline(cin >> ws, user.Password);
	}
	user.permission = ReadPermission(userName);

	return user;

}
void AddNewUser()
{

	string AddMore = "Y";
	string s1;
	do
	{


		PrintNameOfScreen("  Add New User screen");
		::VUsers.push_back(ReadUser());
		if (::VUsers.back().UserName != "")
		{
			s1 = ConvertRecordUsersToLineWithEncryption(::VUsers.back());
			SaveStringInFile(s1, 1, ::UsersFileName);
			cout << "=================================================\n";
			cout << "\n Do you nead add more user Y/N ? ";
			cin >> AddMore;
		}


	} while (AddMore == "y" || AddMore == "Y");
}

vector <sClient> ReadFileClientsToRecord(string comma, string fileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(fileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{


			vClients.push_back(LineClientsToRecordWithDecryption(Line, comma));
		}
		MyFile.close();
	}
	return vClients;
}
vector <sUser> ReadFileUsersToRecord(string FileName = UsersFileName, string usersComma = ::UsersComma)
{
	vector <sUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{


			vUsers.push_back(LineUsersToRecordWithDecryption(Line, usersComma));
		}
		MyFile.close();
	}
	return vUsers;
}
void ClearFileUsersAndFileClients(string FileUsersName, string FileClientsName, bool AreYouSure, bool AreYouSure2, bool AreYouSure3)
{
	if (AreYouSure && AreYouSure2 && AreYouSure3)
	{
		FileUsersName.clear();
		FileClientsName.clear();
		fstream file, file2;
		file.open(FileUsersName, ios::out);
		file2.open(FileClientsName, ios::out);
		file.close();
		file2.close();
	}
}
void PrintClints()
{
	system("cls");
	printf("                                  Clients LIST (%d) Client(s).                       \n", ::VClients.size());
	printf("_____________________________________________________________________________________________\n\n");
	printf("Accounte Numbe  |PinCode  |Name                               |Phone         |Account Balance\n");
	printf("_____________________________________________________________________________________________\n\n");

	for (sClient& client : ::VClients)
	{
		if (client.AccounteNumber != "")
		{
			cout << setw(16) << left << client.AccounteNumber << "|";
			cout << setw(9) << left << client.PinCode << "|";
			cout << setw(35) << left << client.Name << "|";
			cout << setw(14) << left << client.Phone << "|";

			printf("%.*f", 2, (double)client.AccountBalance);
			cout << "\n";
		}

	}
	printf("_____________________________________________________________________________________________\n\n");
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
}
void ListUsers(vector <sUser>& vUsers)
{
	int NumberOfUsers = vUsers.size();
	if (::User.UserName != "Admin")
	{
		NumberOfUsers -= 1;
	}
	printf("\n                       Users LIST (%d) User(s).                       \n", NumberOfUsers);
	printf("=====================================================================\n");
	printf(" User Name                          |Password       | Permission\n");
	printf("=====================================================================\n");

	for (sUser& user : vUsers)
	{
		if (user.UserName != "")
		{
			if ((user.UserName == "Admin" && ::User.UserName != "Admin"))
			{
				continue;
			}
			cout << " " << setw(35) << left << user.UserName << "|";
			cout << " " << setw(14) << left << user.Password << "|";
			cout << " " << setw(14) << left << user.permission << "\n";
		}

	}
	printf("=====================================================================\n");

}



vector <string> vClientsTovStrings(vector <sClient>& vClients, string comma)
{
	vector <string> vStrings;
	for (sClient client : vClients)
	{
		if (client.Name != "")
		{
			vStrings.push_back(ConvertRecordClientsToLineWithEncryption(client, comma));
		}
	}
	return vStrings;
}
vector <string> vUsersTovStrings(vector <sUser>& vUsers)
{
	vector <string> vStrings;
	for (sUser user : vUsers)
	{
		if (user.UserName != "" && user.Password != "" && user.Delete != true)
		{
			vStrings.push_back(ConvertRecordUsersToLineWithEncryption(user, ::UsersComma));
		}
	}
	return vStrings;
}
void SaveVectorInFile(vector <string> vStrings, bool SaveOldStrings, string FileName)
{

	fstream file;
	if (SaveOldStrings)
	{
		file.open(FileName, ios::out | ios::app);
	}
	else
	{
		file.open(FileName, ios::out);
	}

	for (string& s : vStrings)
	{
		if (file.is_open())
		{
			file << s << endl;
		}
	}

	file.close();

}
void DelateClient(vector <sClient>& vClients, string clienteComma, string clientFileName)
{
	int index;
	string YesOrNo;
	vector <sClient>::iterator iterClients = vClients.begin();
	system("cls");
	system("color 74");
	cout << "-----------------------------------------\n";
	cout << "\tDelate Clients Screen\n";
	cout << "-----------------------------------------\n";
	if (SearchAndPrintClient(vClients, index))
	{
		cout << "\a";
		cout << " Do you nead delete the client Y/N ?";
		cin >> YesOrNo;
		if (YesOrNo == "Y" || YesOrNo == "y")
		{
			vClients.erase(iterClients + index);
			SaveVectorInFile(vClientsTovStrings(vClients, clienteComma), false, clientFileName);
			cout << "Deleted Successfully\n";
		}

	}

	cout << " Press any key to go back to Main Menue...";
	system("pause>0");

}


void ReadForUpdateClient(sClient& client)
{
	string YesOrNo = "N";
	cout << "Account Number " << client.AccounteNumber << endl;

	cout << "Do You Need Edit PinCode Y/N ? ";
	cin >> YesOrNo;
	if (YesOrNo == "y" | YesOrNo == "Y")
	{
		cout << "Enter PinCode?";
		getline(cin >> ws, client.PinCode);
	}

	cout << "Do You Need Edit Name Y/N ? ";
	cin >> YesOrNo;
	if (YesOrNo == "y" | YesOrNo == "Y")
	{
		cout << "Enter Name?";
		getline(cin >> ws, client.Name);
	}

	cout << "Do You Need Edit Phone Number Y/N ? ";
	cin >> YesOrNo;
	if (YesOrNo == "y" | YesOrNo == "Y")
	{
		cout << "Enter Phone?";
		getline(cin >> ws, client.Phone);
	}

	cout << "Do You Need Edit Account Balance Y/N ? ";
	cin >> YesOrNo;
	if (YesOrNo == "y" | YesOrNo == "Y")
	{
		cout << "Enter Account Balance?";
		cin >> client.AccountBalance;
	}

}
void UpdateClientByAccountNumber(vector <sClient>& vClients, string clientComma, string clientFileName)
{

	int index;
	string YesOrNo;
	vector <sClient>::iterator iterClientes = vClients.begin();
	system("cls");
	cout << "-----------------------------------------\n";
	cout << "\tUpdate Clients screen\n";
	cout << "-----------------------------------------\n";
	if (SearchAndPrintClient(vClients, index))
	{
		cout << "Do you nead Update the client Y/N ?";
		cin >> YesOrNo;
		if (YesOrNo == "Y" || YesOrNo == "y")
		{
			string AccountNumber = vClients[index].AccounteNumber;

			ReadForUpdateClient(vClients[index]);
			SaveVectorInFile(vClientsTovStrings(vClients, clientComma), false, clientFileName);

			system("cls");
			cout << "\tUpdated Successfully\n";
			PrintClient(vClients[index]);

		}

	}
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
}
bool ReadAccountNumberAndGetIndex(vector <sClient>& vClients, int& Index)
{

	string tryAgain = "N";
	do
	{

		if (!SearchAndPrintClient(vClients, Index))
		{

			cout << "Do you want to try again Y/N ? ";
			cin >> tryAgain;
		}
		else
		{
			return 1;
		}
	} while (tryAgain == "Y" | tryAgain == "y");

	return false;
}
double DepositAmount(double From, double To)
{
	double depositAmount;
	do
	{
		printf("Please enter deposit amount [%.*f ~ %.*f] ? ", 2, From, 2, To);
		cin >> depositAmount;
	} while (depositAmount<From || depositAmount>To);
	return depositAmount;
}
void Deposit(vector <sClient>& vClients, string comma, string FileName, int DepositFrom = 0, int DepositTo = 1000000)
{
	int Index;
	double depositAmount = 0;
	string ToBeSure;
	system("cls");
	cout << "============================================\n";
	cout << "               Deposit Screen               \n";
	cout << "============================================\n";
	if (ReadAccountNumberAndGetIndex(vClients, Index))
	{

		depositAmount = DepositAmount(DepositFrom, DepositTo);
		if (depositAmount != 0)
		{
			cout << "Are you sure you want perform this transaction y/n ?";
			cin >> ToBeSure;


			if (ToBeSure == "y" | ToBeSure == "Y")
			{
				vClients[Index].AccountBalance += (double)depositAmount;
				SaveVectorInFile(vClientsTovStrings(vClients, comma), false, FileName);
				cout << "Account Number : " << vClients[Index].AccounteNumber << endl;
				printf("New Balance is : %.*f \n", 2, vClients[Index].AccountBalance);
			}
		}
	}

	cout << "Press any key to go back to Transactions Menue...";
	system("pause>0");

}
double WithdrawAmount(double Balance, double From, double To)
{
	if (Balance <= To)
	{
		To = Balance;
	}
	double depositAmount;
	do
	{
		printf("Please enter withdraw amount [%.*f ~ %.*f] ? ", 2, From, 2, To);
		cin >> depositAmount;
	} while (depositAmount < From || depositAmount>To);
	return depositAmount;
}
void Withdraw(vector <sClient>& vClients, string comma, string FileName, int WithdrawFrom = 0, int WithdrawTo = 1000000)
{
	int Index;
	double withdrawAmount = 0;
	string ToBeSure = "";
	system("cls");
	cout << "============================================\n";
	cout << "              Withdraw Screen               \n";
	cout << "============================================\n";
	if (ReadAccountNumberAndGetIndex(vClients, Index))
	{
		withdrawAmount = WithdrawAmount(vClients[Index].AccountBalance, WithdrawFrom, WithdrawTo);
		if (withdrawAmount != 0)
		{
			cout << "Are you sure you want perform this transaction y/n ?";
			getline(cin >> ws, ToBeSure);


			if (ToBeSure == "y" | ToBeSure == "Y")
			{

				vClients[Index].AccountBalance -= withdrawAmount;
				SaveVectorInFile(vClientsTovStrings(vClients, comma), false, FileName);
				cout << "Account Number : " << vClients[Index].AccounteNumber << endl;
				printf("New Balance is : %.*f \n", 2, vClients[Index].AccountBalance);
			}
		}
	}
	cout << "Press any key to go back to Transactions Menue...";
	system("pause>0");

}
double CountTotalBalances(vector <sClient>& clintes)
{
	double sum = 0;
	for (sClient clinet : clintes)
	{
		sum += clinet.AccountBalance;
	}
	return sum;
}
void TotalBalancesScreen(vector <sClient>& clients)
{
	system("cls");
	printf("                                  Client LIST (%d) Client(s).                       \n", clients.size());
	printf("___________________________________________________________________________________________\n\n");
	printf("Accounte Numbe  |Name                               |Account Balance   \n");
	printf("___________________________________________________________________________________________\n\n");

	for (sClient& client : clients)
	{
		if (client.AccounteNumber != "")
		{
			cout << setw(16) << left << client.AccounteNumber << "|";
			cout << setw(35) << left << client.Name << "|";
			printf("%.*f", 2, (double)client.AccountBalance);
			cout << "\n";
		}

	}
	printf("___________________________________________________________________________________________\n\n");
	printf("\t\tTotal Balances Is : %.*f\n\n", 2, CountTotalBalances(clients));
	cout << "Press any key to go back to Transactions Menue...";
	system("pause>0");
}

void TransactionsMenue()
{
	system("cls");

	cout << "============================================\n";
	cout << "           Transactions Menue Screen        \n";
	cout << "============================================\n";
	cout << "        [1] Deposit.\n";
	cout << "        [2] Withdraw.\n";
	cout << "        [3] Total Balances.\n";
	cout << "        [4] Main Menue.\n";
	cout << "============================================\n";
}
bool Transactions(vector <sClient>& vClients, string comma, string FileName)
{
	short Choose;
	while (true)
	{
		TransactionsMenue();
		Choose = ReadShortNumber("Choose what do you want to do ? [1 to 4] ? ", 1, 4);
		switch (Choose)
		{
		case 1:
			Deposit(vClients, comma, FileName);
			break;

		case 2:
			Withdraw(vClients, comma, FileName);
			break;
		case 3:
			TotalBalancesScreen(vClients);
			break;
		default:
			cout << "Press any key to go back to Transactions Menue...";
			system("pause>0");
			return 0;

		}
	}



}

void RefreshClients(vector <sClient>& clients)
{
	clients = ReadFileClientsToRecord(::ClientsComma, ::ClientsFileName);
	SaveVectorInFile(vClientsTovStrings(clients, ::ClientsComma), false, ClientsFileName);
}

void FactoryResetWhenAdminIsNotPresent()
{
	int tempIndex;
	if (!SearchUser(::VUsers, "Admin", tempIndex))
	{
		ClearFileUsersAndFileClients(::UsersFileName, ::ClientsFileName, true, true, true);
		sUser tempUser;
		tempUser.UserName = "Admin";
		tempUser.Password = "0000";
		tempUser.permission = enPermission::enAll;
		SaveStringInFile(ConvertRecordUsersToLineWithEncryption(tempUser), false, ::UsersFileName);
		::VUsers = ReadFileUsersToRecord(::UsersFileName);
		cout << "\nMain User Name Is : " << ::VUsers.front().UserName << " And Main Password Is : " << ::VUsers.front().Password << "\n\n";
	}
}
void ShowMenueScreen()
{
	system("cls");
	system("color 71");

	cout << "============================================\n";
	cout << "               Main Menue Screen            \n";
	cout << "============================================\n";
	cout << "        [1] Show Clients List.\n";
	cout << "        [2] Add New Client.\n";
	cout << "        [3] Delete Client.\n";
	cout << "        [4] Update Client Info.\n";
	cout << "        [5] Find Client.\n";
	cout << "        [6] Transactions.\n";
	cout << "        [7] Manage User.\n";
	cout << "        [8] Refresh.\n";
	cout << "        [9] Logout.\n";
	cout << "============================================\n";
}
enum enMenueScreen { eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eRefresh = 8, eLogout = 9 };

sUser ReadLoginUser(vector <sUser>& vUsers)
{
	sUser user;
	system("color 0");
	PrintNameOfScreen("\tLogin Screen", false);
	cout << "Enter UserName : ";
	getline(std::cin >> ws, user.UserName);
	cout << "Enter Password : ";
	getline(std::cin >> ws, user.Password);

	while (!CheckLoginUser(vUsers, user))
	{
		cout << "Username or password error\n";
		cout << "Enter UserName : ";
		getline(std::cin >> ws, user.UserName);
		cout << "Enter Password : ";
		getline(std::cin >> ws, user.Password);
	}
	return user;
}
void DeleteUser()
{
	int index;
	string yOrN = "n", userName = "";
	PrintNameOfScreen("  Delete User Screen ");
	std::cout << " Enter User Name : ";
	getline(cin >> ws, userName);
	if (SearchUser(::VUsers, userName, index))
	{
		if (::VUsers[index].UserName == "Admin")
		{
			std::cout << " This user cannot be shown or edited or deleted.\n";
		}
		else
		{
			PrintUser(::VUsers[index]);
			std::cout << " Are you shore do you nead Delete this user y/n : ";
			cin >> yOrN;
			if (yOrN == "y" || yOrN == "Y")
			{
				::VUsers[index].Delete = true;
				SaveVectorInFile(vUsersTovStrings(::VUsers), false, ::UsersFileName);
				::VUsers = ReadFileUsersToRecord(::UsersFileName);
			}
		}
	}

}
void UpdateUser()
{
	string userName = "";
	int index;
	PrintNameOfScreen("\tUpdate User Screen ");
	if (SearchAndPrintUser(::VUsers, index))
	{
		::VUsers[index] = ReadUser(::VUsers[index].UserName);
		SaveVectorInFile(vUsersTovStrings(::VUsers), false, ::UsersFileName);

	}
}
void PrintManageUsersMenue()
{
	system("cls");
	system("color 71");
	PrintNameOfScreen("Manage Users Screen");
	cout << "\t[1] List Users.\n\t[2] Add New User.\n\t[3] Delete User.\n\t[4] Update User.\n\t[5] Find User.\n\t[6] Main Menue.\n";
	cout << "================================================\n";

}
bool ManageUsers()
{
	short choose;
	while (true)
	{
		PrintManageUsersMenue();
		choose = ReadShortNumber("Choose from 1 to 6 : ", 1, 6);
		//[1]ListUsers. [2]AddNewUser. [3]DeleteUser [4]UpdateUser [5]FindUser [6]MainMenue
		if (choose <= 5)
			system("cls");
		switch (choose)
		{
		case 1:
			ListUsers(::VUsers);
			break;
		case 2:
			AddNewUser();
			break;
		case 3:
			system("color 74");
			DeleteUser();
			break;
		case 4:
			UpdateUser();
			break;
		case 5:
			SearchAndPrintUser(::VUsers, true);
			break;
		case 6:
			return 0;
			break;

		}
		cout << " Press any key to go back to Manage Users Menue...";
		system("pause>0");
	}


}
bool Menue(vector <sUser>& vUsers, vector<sClient>& vClients)
{
	short Choose = 0;

	while (true)
	{

		ShowMenueScreen();
		Choose = ReadShortNumber("Enter number from 1 to 9 : ", 1, 9);
		switch (Choose)
		{
		case enMenueScreen::eShowClientsList:
			if (checkPermissionAndPrint(::User, enPermission::enClientsList))
				PrintClints();
			break;
		case enMenueScreen::eAddNewClient:
			if (checkPermissionAndPrint(::User, enPermission::enAddClient))
				AddClient();
			break;
		case enMenueScreen::eDeleteClient:
			if (checkPermissionAndPrint(::User, enPermission::enDeleteClient))
				DelateClient(vClients, ::ClientsComma, ::ClientsFileName);
			break;
		case enMenueScreen::eUpdateClientInfo:
			if (checkPermissionAndPrint(::User, enPermission::enUpdateClient))
				UpdateClientByAccountNumber(vClients, ::ClientsComma, ::ClientsFileName);
			break;
		case enMenueScreen::eFindClient:
			if (checkPermissionAndPrint(::User, enPermission::enFindClient))
				SearchAndPrintClient(vClients);
			break;

		case enMenueScreen::eTransactions:
			if (checkPermissionAndPrint(::User, enPermission::enTransactions))
				Transactions(vClients, ::ClientsComma, ::ClientsFileName);
			break;
		case eRefresh:
			RefreshClients(vClients);
			break;
		case enMenueScreen::eManageUsers:
			if (checkPermissionAndPrint(::User, enPermission::enManageUsers))
				ManageUsers();
			break;
		case enMenueScreen::eLogout:

			return 0;

		}

	}
}

bool Bank()
{

	while (true)
	{
		system("color F");
		system("cls");
		::VUsers = ReadFileUsersToRecord(::UsersFileName);
		//FactoryResetWhenAdminIsNotPresent();
		::User = ReadLoginUser(::VUsers);
		::VClients = ReadFileClientsToRecord(::ClientsComma, ::ClientsFileName);
		Menue(::VUsers, ::VClients);
	}
	return 0;
}
int main()
{

	while (true)
	{

		Bank();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
