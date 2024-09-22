
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using  namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
const int encryptionCode = 0, decryptionCode = 0;
string ClitesComma = "#//#";
string UsersComma = "#//#";
int NumberOfClientes(string FileName)
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
enum enPermission { All = -1, Normal };
struct sUser
{
	string UserName = "";
	string Password = "";
	short permission;

	bool Delete = false;
};
bool SearchCliente(vector <sClient>& vClientes, string AccountNumber)
{

	for (int i = 0; i < vClientes.size(); i++)
	{
		if (vClientes[i].AccounteNumber == AccountNumber)
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
		if (vUsers[i].UserName == user.UserName&& vUsers[i].Password== user.Password)
		{

			return true;
		}

	}
	return false;
}
sClient ReadClinte(vector <sClient>& clientes, string AccounteNumber = "")
{
	sClient clinte;
	if (AccounteNumber != "")
	{
		clinte.AccounteNumber = AccounteNumber;
		cout << "Account Number " << clinte.AccounteNumber << endl;

	}
	else
	{
		cout << "Enter Account Number?";
		getline(cin >> ws, clinte.AccounteNumber);

		if (SearchCliente(clientes, clinte.AccounteNumber))
		{
			cout << "This Accounte Number Exists\n";
			return clinte;

		}
	}

	cout << "Enter PinCode?";
	getline(cin >> ws, clinte.PinCode);
	cout << "Enter Name?";
	getline(cin, clinte.Name);
	cout << "Enter Phone?";

	getline(cin, clinte.Phone);
	cout << "Enter Account Balance?";
	cin >> clinte.AccountBalance;



	return clinte;
}
void PrintClint(sClient& clintes)
{
	printf("______________________________________________________\n");
	cout << "Accounte Number : " << clintes.AccounteNumber << endl;
	cout << "Pin Code        : " << clintes.PinCode << endl;
	cout << "Name            : " << clintes.Name << endl;
	cout << "Phone           : " << clintes.Phone << endl;
	printf("Account Balance : %.*f \n", 2, clintes.AccountBalance);
	printf("______________________________________________________\n\n");

}
bool SearchCliente(vector <sClient>& vClientes, string AccountNumber, int& index)
{
	for (int i = 0; i < vClientes.size(); i++)
	{
		if (vClientes[i].AccounteNumber == AccountNumber)
		{
			index = i;
			return true;
		}

	}
	return false;
}

bool SearchAndPrintCliente(vector <sClient>& vClientes, int& index)
{

	string search;
	cout << "Enter Account number ? ";
	cin >> search;
	if (SearchCliente(vClientes, search, index))
	{
		PrintClint(vClientes[index]);
		return 1;

	}
	else
	{
		cout << "Not Found\n";
		return 0;
	}
}
bool SearchAndPrintCliente(vector <sClient>& vClientes)
{

	string search; int index;
	cout << "-----------------------------------------\n";
	cout << "\tClientes Search screen\n";
	cout << "-----------------------------------------\n";
	cout << "Enter Account number ? ";
	cin >> search;
	if (SearchCliente(vClientes, search, index))
	{
		PrintClint(vClientes[index]);
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


string ConvertRecordClintesToLineWithEncryption(sClient clinte, string ClitesComma )
{
	string stClientRecord = "";
	stClientRecord += clinte.AccounteNumber + ClitesComma;
	stClientRecord += clinte.PinCode + ClitesComma;
	stClientRecord += clinte.Name + ClitesComma;
	stClientRecord += clinte.Phone + ClitesComma;
	stClientRecord += to_string(clinte.AccountBalance);
	Encryption(stClientRecord);
	return stClientRecord;
}
string ConvertRecordUsersToLineWithEncryption(sUser user, string usersComma )
{
	string stClientRecord = "";
	stClientRecord += user.UserName+ usersComma;
	stClientRecord += user.Password + usersComma;
	stClientRecord += to_string(user.permission) + usersComma;
	
	Encryption(stClientRecord);
	return stClientRecord;
}
sClient LineClintesToRecordWithDecryption(string s1, string ClitesComma )
{
	sClient clinte;
	vector <string> vRecords;
	Decryption(s1);
	vRecords = SplitString(s1, ClitesComma);
	if (vRecords.size() > 3)
	{
		clinte.AccounteNumber = vRecords[0];
		clinte.PinCode = vRecords[1];
		clinte.Name = vRecords[2];
		clinte.Phone = vRecords[3];
		clinte.AccountBalance = stod(vRecords[4]);
	}
	else
	{
		cout << "Text Splitting problem\n";
	}



	return clinte;

}
sUser LineUsersToRecordWithDecryption(string s1, string usersComma )
{
	sUser user;
	vector <string> vRecords;
	Decryption(s1);
	vRecords = SplitString(s1, UsersComma);
	if (vRecords.size() >=3)
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
void PrintRecord(sClient clime)
{
	cout << "Account Number : " << clime.AccounteNumber << endl;
	cout << "PinCode: " << clime.PinCode << endl;
	cout << "Name: " << clime.Name << endl;
	cout << "Phone: " << clime.Phone << endl;
	cout << "Account Balance: " << clime.AccountBalance << endl;
}
void SaveStringInFile(string s1, bool saveOldString ,string FileName)
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
void AddClint(vector <sClient>& clintes, string ClitesComma,string FileName )
{

	string AddMore = "Y";
	string s1;

	do
	{
		system("cls");
		cout << "-----------------------------------------\n";
		cout << "\tAdd New Clients screen\n";
		cout << "-----------------------------------------\n";

		clintes.push_back(ReadClinte(clintes));
		if (clintes.back().Name != "")
		{

			s1 = ConvertRecordClintesToLineWithEncryption(clintes.back(), ClitesComma);
			SaveStringInFile(s1,1,FileName);
		}



		cout << "Do you nead add more clinte Y/N ? ";
		cin >> AddMore;


	} while (AddMore == "y" || AddMore == "Y");
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
}

vector <sClient> ReadFileClientsToRecord(string comma,string fileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(fileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{


			vClients.push_back(LineClintesToRecordWithDecryption(Line, comma));
		}
		MyFile.close();
	}
	return vClients;
}vector <sUser> ReadFileUsersToRecord(string FileName=UsersFileName,string usersComma=::UsersComma)
{
	vector <sUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{


			vUsers.push_back(LineUsersToRecordWithDecryption(Line,usersComma));
		}
		MyFile.close();
	}
	return vUsers;
}

void PrintClints(vector <sClient>& clintes)
{
	system("cls");
	printf("                                  Client LISt (%d) Client(s).                       \n", clintes.size());
	printf("_____________________________________________________________________________________________\n\n");
	printf("Accounte Numbe  |PinCode  |Name                               |Phone         |Account Balance\n");
	printf("_____________________________________________________________________________________________\n\n");

	for (sClient& clint : clintes)
	{
		if (clint.AccounteNumber != "")
		{
			cout << setw(16) << left << clint.AccounteNumber << "|";
			cout << setw(9) << left << clint.PinCode << "|";
			cout << setw(35) << left << clint.Name << "|";
			cout << setw(14) << left << clint.Phone << "|";

			printf("%.*f", 2, (double)clint.AccountBalance);
			cout << "\n";
		}

	}
	printf("_____________________________________________________________________________________________\n\n");
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
}



vector <string> vClientesTovStrings(vector <sClient>& vClientes,string comma)
{
	vector <string> vStrings;
	for (sClient cliente : vClientes)
	{
		if (cliente.Name != "")
		{
			vStrings.push_back(ConvertRecordClintesToLineWithEncryption(cliente, comma));
		}
	}
	return vStrings;
}
vector <string> vUsersTovStrings(vector <sUser>& vUsers,string usersFileName ,string usersComma)
{
	vector <string> vStrings;
	for (sUser user : vUsers)
	{
		if (user.UserName != "" && user.Password != "")
		{
			vStrings.push_back(ConvertRecordUsersToLineWithEncryption(user,UsersComma));
		}
	}
	return vStrings;
}
void SaveVectorInFile(vector <string> vStrings, bool SaveOldStrings , string FileName )
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
void DelateCliente(vector <sClient>& vClientes,string clienteComma, string clienteFileName)
{
	int index;
	string YesOrNo;
	vector <sClient>::iterator iterClientes = vClientes.begin();
	system("color 40");
	cout << "-----------------------------------------\n";
	cout << "\tDelate Clients screen\n";
	cout << "-----------------------------------------\n";
	if (SearchAndPrintCliente(vClientes, index))
	{
		cout << "\a";
		cout << "Do you nead delete the cliente Y/N ?";
		cin >> YesOrNo;
		if (YesOrNo == "Y" || YesOrNo == "y")
		{
			vClientes.erase(iterClientes + index);
			SaveVectorInFile(vClientesTovStrings(vClientes, clienteComma), false, clienteFileName);
			cout << "Deleted Successfully\n";
		}

	}

	cout << "Press any key to go back to Main Menue...";
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
void UpdateClienteByAccountNumber(vector <sClient>& vClientes,string clienteComma,string clienteFileName)
{

	int index;
	string YesOrNo;
	vector <sClient>::iterator iterClientes = vClientes.begin();

	cout << "-----------------------------------------\n";
	cout << "\tUpdate Clients screen\n";
	cout << "-----------------------------------------\n";
	if (SearchAndPrintCliente(vClientes, index))
	{
		cout << "Do you nead Update the cliente Y/N ?";
		cin >> YesOrNo;
		if (YesOrNo == "Y" || YesOrNo == "y")
		{
			string AccountNumber = vClientes[index].AccounteNumber;

			ReadForUpdateClient(vClientes[index]);
			SaveVectorInFile(vClientesTovStrings(vClientes,clienteComma), false, clienteFileName);

			system("cls");
			cout << "\tUpdated Successfully\n";
			PrintClint(vClientes[index]);

		}

	}
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
}
bool ReadAccountNumberAndGetIndex(vector <sClient>& vClientes, int& Index)
{

	string tryAgain = "N";
	do
	{

		if (!SearchAndPrintCliente(vClientes, Index))
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
void Deposit(vector <sClient>& vClientes,string comma, string FileName , int DepositFrom = 0, int DepositTo = 1000000)
{
	int Index;
	double depositAmount = 0;
	string ToBeSure;
	system("cls");
	cout << "============================================\n";
	cout << "               Deposit Screen               \n";
	cout << "============================================\n";
	if (ReadAccountNumberAndGetIndex(vClientes, Index))
	{

		depositAmount = DepositAmount(DepositFrom, DepositTo);
		if (depositAmount != 0)
		{
			cout << "Are you sure you want perform this transaction y/n ?";
			cin >> ToBeSure;


			if (ToBeSure == "y" | ToBeSure == "Y")
			{
				vClientes[Index].AccountBalance += (double)depositAmount;
				SaveVectorInFile(vClientesTovStrings(vClientes, comma), false, FileName);
				cout << "Account Number : " << vClientes[Index].AccounteNumber << endl;
				printf("New Balance is : %.*f \n", 2, vClientes[Index].AccountBalance);
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
void Withdraw(vector <sClient>& vClientes,string comma, string FileName , int WithdrawFrom = 0, int WithdrawTo = 1000000)
{
	int Index;
	double withdrawAmount = 0;
	string ToBeSure = "";
	system("cls");
	cout << "============================================\n";
	cout << "              Withdraw Screen               \n";
	cout << "============================================\n";
	if (ReadAccountNumberAndGetIndex(vClientes, Index))
	{
		withdrawAmount = WithdrawAmount(vClientes[Index].AccountBalance, WithdrawFrom, WithdrawTo);
		if (withdrawAmount != 0)
		{
			cout << "Are you sure you want perform this transaction y/n ?";
			getline(cin >> ws, ToBeSure);


			if (ToBeSure == "y" | ToBeSure == "Y")
			{

				vClientes[Index].AccountBalance -= withdrawAmount;
				SaveVectorInFile(vClientesTovStrings(vClientes,comma), false, FileName);
				cout << "Account Number : " << vClientes[Index].AccounteNumber << endl;
				printf("New Balance is : %.*f \n", 2, vClientes[Index].AccountBalance);
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
void TotalBalancesScreen(vector <sClient>& clintes)
{
	system("cls");
	printf("                                  Client LISt (%d) Client(s).                       \n", clintes.size());
	printf("___________________________________________________________________________________________\n\n");
	printf("Accounte Numbe  |Name                               |Account Balance   \n");
	printf("___________________________________________________________________________________________\n\n");

	for (sClient& clint : clintes)
	{
		if (clint.AccounteNumber != "")
		{
			cout << setw(16) << left << clint.AccounteNumber << "|";
			cout << setw(35) << left << clint.Name << "|";
			printf("%.*f", 2, (double)clint.AccountBalance);
			cout << "\n";
		}

	}
	printf("___________________________________________________________________________________________\n\n");
	printf("\t\tTotal Balances Is : %.*f\n\n", 2, CountTotalBalances(clintes));
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
bool Transactions(vector <sClient>& vClientes,string comma, string FileName )
{
	short Choose;
	while (true)
	{
		TransactionsMenue();
		cout << "Choose what do you want to do ? [1 to 4] ? ";
		cin >> Choose;
		switch (Choose)
		{
		case 1:
			Deposit(vClientes, comma, FileName);
			break;

		case 2:
			Withdraw(vClientes, comma, FileName);
			break;
		case 3:
			TotalBalancesScreen(vClientes);
			break;
		default:
			cout << "Press any key to go back to Transactions Menue...";
			system("pause>0");
			return 0;

		}
	}



}

void RefreshClintes(vector <sClient>& clintes,string comma,string fileName)
{
	clintes = ReadFileClientsToRecord(comma,fileName);
	SaveVectorInFile(vClientesTovStrings(clintes,comma),false,fileName);
}
void RefreshUsers(vector <sUser>& users,string FileName)
{
	users = ReadFileUsersToRecord(FileName);
	vector <string> vs = vUsersTovStrings(users, FileName, UsersComma);
	SaveVectorInFile(vs,false,FileName);
	
}

void ShowMenueScreen()
{
	system("cls");
	system("color 71");

	cout << "============================================\n";
	cout << "               Main Menue Screen            \n";
	cout << "============================================\n";
	cout << "        [1] Show Client List.\n";
	cout << "        [2] Add New Client.\n";
	cout << "        [3] Delete Client.\n";
	cout << "        [4] Update Client Info.\n";
	cout << "        [5] Find Client.\n";
	cout << "        [6] Transactions.\n";
	cout << "        [7] Refresh.\n";
	cout << "        [8] Exit.\n";
	cout << "============================================\n";
}
enum enMenueScreen { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, eFindClient = 5, eTransactions = 6, eRefresh = 7, eExit = 8 };

sUser ReadLoginUser(vector <sUser>& vUsers)
{
	sUser user;
	system("cls");
	system("color 0");
	cout << "Enter UserName : ";
	getline(std::cin>>ws, user.UserName);
	cout << "Enter Password : ";
	getline(std::cin>>ws, user.Password);

	while (!SearchUser(vUsers,user))
	{
		cout << "Username and password error\n";
		cout << "Enter UserName : ";
		getline(std::cin >> ws, user.UserName);
		cout << "Enter Password : ";
		getline(std::cin >> ws, user.Password);
	}
	return user;
}
bool Menue(vector <sUser>& vUsers, vector<sClient> & vClintes, string comma,string clientsFileName)
{
	short Choose = 1;

	while (true)
	{
		
		ShowMenueScreen();
		cout << "Choose what do you want to do? [1 to 8]? ";
		cin >> Choose;
		system("cls");
		switch (Choose)
		{
		case enMenueScreen::eShowClientList:
			PrintClints(vClintes);
			break;
		case enMenueScreen::eAddNewClient:
			AddClint(vClintes, comma, clientsFileName);
			break;
		case enMenueScreen::eDeleteClient:
			DelateCliente(vClintes, comma,clientsFileName);
			break;
		case enMenueScreen::eUpdateClientInfo:
			UpdateClienteByAccountNumber(vClintes,comma,clientsFileName);
			break;
		case enMenueScreen::eFindClient:
			SearchAndPrintCliente(vClintes);

			break;

		case enMenueScreen::eTransactions:
			Transactions(vClintes,comma,clientsFileName);
			break;
		case eRefresh:
			RefreshClintes(vClintes,comma,clientsFileName);
			break;
		case enMenueScreen::eExit:

			return 0;
		default:
			RefreshClintes(vClintes,comma,clientsFileName);
			break;
		}

	}
}
bool Bank()
{
	vector <sClient> clientes;
	vector <sUser> users;
	string clientesComma=::ClitesComma, clientesFileName=::ClientsFileName;
	while (true)
	{
		system("color F");
		RefreshUsers(users,UsersFileName);
		ReadLoginUser(users);
		RefreshClintes(clientes,clientesComma,clientesFileName);
		Menue(users, clientes, clientesComma, clientesFileName);
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
