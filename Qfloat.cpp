#include <iostream>
#include <string>
using namespace std;
#define MAX 128

typedef struct
{
	uint32_t data[4];
}QFloat;

char numToString(int n)     // chuyen so sang char
{
	return (char)(n + 48);
}
int stringToNum(char c)     // chuyen char sang so
{
	return c - '0';
}
string operator * (string bigNumber, int x)
{
	string res = "";
	int len = bigNumber.length();
	int tmp = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (bigNumber[i] == '.')
		{
			res.insert(0, 1, '.');
		}
		else
		{
			tmp += stringToNum(bigNumber[i]) * x;
			res.insert(0, 1, numToString(tmp % 10));//lay phan don vi cho vao string
			tmp /= 10;// lay phan chuc de tinh tiep
		}
	}

	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}

string remove0(const string& number)
{
	string res = number;
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] != '0')//Vi tri khac 0 dau tien
		{
			res.erase(0, i);
			break;
		}
	}
	return res;
}
string chia2(string bigInt)
{

	string tmp;
	string soChia = remove0(bigInt);

	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(bigInt.length());
	if (stringToNum(soChia[0]) < 2)
	{
		i = 1;
		j = 10;
	}
	for (; i < soChia.length(); i++)
	{
		tmp[k++] = ((soChia[i] - '0' + j) / 2 + '0');
		j = ((soChia[i] - 48 + j) % 2) * 10;
	}
	tmp.resize(k);
	return tmp;
}

string reverse(string a)
{
	string rev_arr;
	for (int i = 0; i < a.length(); i++)
	{
		rev_arr.push_back(a[a.length() - i - 1]);
	}
	return rev_arr;
}


string DecToBin(string userInputStr)
{
	string binary(MAX, '0');


	// chia userInputStr cho 2 r lay so du bo vao binary
	for (int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary[i] = '1';
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary[i] = '0';
		userInputStr = chia2(userInputStr);
	}

	//Dao chuoi lai
	binary = reverse(binary);
	binary = remove0(binary);
	
	return binary;

}

int SoPhanTuSauDauCham(string phanThapPhan)
{
	int dauCham = phanThapPhan.find_first_of('.');
	return phanThapPhan.length() - dauCham - 1;
}
string Float_1(int n)
{
	string res = "1.";
	for (int i = 0; i < n; i++)
	{
		res.push_back('0');
	}
	return res;
}
void canBang2Chuoi(string& a, string& b)
{
	int a_len = a.length(), b_len = b.length();
	if (a_len > b_len)
	{
		b.insert(0, a_len - b_len, '0');
	}
	else
	{
		a.insert(0, b_len - a_len, '0');
	}
}
string CongBit(string a,string b)
{
	canBang2Chuoi(a, b);
	int n = a.size();
	int temp = 0;
	string res(n, '0');
	for (int i = n-1 ; i >= 0; i--)
	{
		temp = stringToNum(a[i]) + stringToNum(b[i]) + temp;
		if (temp == 2)
		{
			temp = 1;
		}
		else if (temp == 3)
		{
			res[i] = '1';
			temp = 1;
		}
		else if (temp == 1)
		{
			res[i] = '1';
			temp = 0;
		}
	}
	return res;
}

string DecToBin_phanThapPhan(string phanThapPhan)
{
	string res;
	int k= 0;
	int len_sauDauCham;
	string so1;
	while (k<112)
	{
		phanThapPhan = phanThapPhan * 2;
		len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
		so1 = Float_1(len_sauDauCham);
		if (phanThapPhan == so1)
		{
			res.push_back('1');
			break;
		}
		else if (phanThapPhan > so1)
		{
			res.push_back('1');
			int DauCham = phanThapPhan.find_first_of('.');
			for (int i = 0; i < DauCham; i++)
			{
				phanThapPhan[i] = '0';
			}
		}
		else
		{
			res.push_back('0');
		}
		k++;
	}
	phanThapPhan = phanThapPhan * 2;
	len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
	so1 = Float_1(len_sauDauCham);
	if (phanThapPhan == so1 || phanThapPhan > so1)
	{
		res=CongBit(res, "1");
	}
	return res;
}
string DecToBin_QFloat(string bigFloat)
{
	return 0;
}

void tachFloat(string number, string &phanNguyen, string &phanThapPhan)
{
	int len = number.size();
	int dauCham = number.find_first_of('.');
	phanNguyen.assign(number, 0, dauCham);
	phanThapPhan.assign(number, dauCham, len-phanNguyen.size());
	phanThapPhan.insert(0, 1, '0');
}

int main()
{
	string s = "3232.1";
	string a, b;
	tachFloat(s, a, b);
	a = DecToBin(a);
	string c=DecToBin_phanThapPhan(b);
	cout <<a<<  " " <<c;
	//cout << a << " " << b << endl;
	system("pause");
	return 0;
}