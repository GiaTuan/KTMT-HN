#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
using namespace std;

#define MAX 128

struct QInt {
	unsigned int data[4] = {0};
};

//char String_Mod_2(string str)
//{
//	int so = stoi(str);
//	int ketqua = so % 2;
//
//}


char Int_Sang_Char(int x)
{
	if (x == 1)
	{
		return '1';
	}
	else if (x == 2)
	{
		return '2';
	}
	else if (x == 3)
	{
		return '3';
	}
	else if (x == 4)
	{
		return '4';
	}
	else if (x == 5)
	{
		return '5';
	}
	else if (x == 6)
	{
		return '6';
	}
	else if (x == 7)
	{
		return '7';
	}
	else if (x == 8)
	{
		return '8';
	}
	else if (x == 9)
	{
		return '9';
	}
	else if (x == 0)
	{
		return '0';
	}
}

void String_Chia_2(string str,string &phanDu,string &phanNguyen)
{
	
	int n =str.size();
	if (n == 1 && str[n-1] == '1')
	{
		phanNguyen = "0";
		phanDu = "1";
		return;
	}
	else
	{
		// tìm phần dư của phép chia
		string soCuoiString;
		soCuoiString.push_back(str[n - 1]);  //lấy giá trị cuối cùng của chuổi string để kiểm tra
		int soCuoi = stoi(soCuoiString); //chuyển sang số nguyên 
		if (soCuoi % 2 == 0)
		{
			phanDu.push_back('0');
		}
		else
		{
			phanDu.push_back('1');
		}

		//tìm phần nguyên của phép chia
		string soBiChia_Str;
		int soBiChia_Int;
		int i = 0;
		int max = n;
		int soDu = 0, soNguyen = 0;
		soBiChia_Str.push_back(str[i]);
		soBiChia_Int = stoi(soBiChia_Str);
		while (i<n)
		{
			if (soBiChia_Int == 1 && i==0)
			{
				i++;
				soBiChia_Str.push_back(str[i]);
				soBiChia_Int = stoi(soBiChia_Str);
			}
			else if (soBiChia_Int >= 2)
			{
				soNguyen = soBiChia_Int / 2;
				soDu = soBiChia_Int % 2;
				char songuyen = Int_Sang_Char(soNguyen);
				phanNguyen.push_back(songuyen);
				soBiChia_Str.clear();
				i++;
				if (soDu == 0&& str[i] != '1'&& str[i] != '0')
				{
					soBiChia_Str.push_back(str[i]);
				}
				else if (soDu == 0 && str[i] == '1')
				{
					phanNguyen.push_back('0');
					soBiChia_Str.push_back('1');
					i++;
					soBiChia_Str.push_back(str[i]);
				}
				else if (soDu == 0 && str[i] == '0')
				{
					phanNguyen.push_back('0');
					i++;
					soBiChia_Str.push_back(str[i]);
				}
				else if(soDu != 0)
				{
					soBiChia_Str.push_back('1');
					soBiChia_Str.push_back(str[i]);
				}
				if (i < n)
				{
					soBiChia_Int = stoi(soBiChia_Str);
				}
			}
			else if (soBiChia_Int < 2)
			{
				phanNguyen.push_back('0');
				i++;
				soBiChia_Str.push_back(str[i]);
				soBiChia_Int = stoi(soBiChia_Str);
			}
		}
		
	}
}

void LaySoBu1(int ketQua[])
{
	for (int i = 0; i < MAX; i++)
	{
		if (ketQua[i] == 0)
		{
			ketQua[i] = 1;
		}
		else
		{
			ketQua[i] = 0;
		}
	}
}

void LaySoBu2(int ketQua[])
{
	LaySoBu1(ketQua);
	for (int i = 0; i < MAX; i++)
	{
		cout << ketQua[i];
	}
	cout << endl;
	int soDu = 0;
	if (ketQua[MAX - 1] == 1)
	{
		ketQua[MAX - 1] = 0;
		soDu = 1;
	}
	else if (ketQua[MAX - 1] == 0)
	{
		ketQua[MAX-1]=1;
	}
	for (int i = MAX-2; i >=0; i--)
	{
		if (ketQua[i] == 1 && soDu == 1)
		{
			ketQua[i] = 0;
			soDu = 1;
		}
		else if (ketQua[i] == 0 && soDu == 1)
		{
			ketQua[i] = 1;
			soDu = 0;
		}
		else if (ketQua[i] == 0 && soDu == 0)
		{
			ketQua[i] = 0;
		}
		else if (ketQua[i] == 1 && soDu == 0)
		{
			ketQua[i] = 1;
		}
	}
	for (int i = 0; i < MAX; i++)
	{
		cout << ketQua[i];
	}
}

void Doi_Sang_Nhi_Phan(string str,int ketQua[])
{
	int temp[MAX] = { 0 };
	int i = 0;
	string PhanNguyen, PhanDu;
	bool flag = false; // kiểm tra có phải là số âm
	char x = str[0];
	if (x == '-')
	{
		flag = true;
		str.erase(0, 1);
	}
	while (1)
	{
		String_Chia_2(str, PhanDu, PhanNguyen);
		if (PhanNguyen == "0")
		{
			temp[i] = stoi(PhanDu);
			break;
		}
		else 
		{
			temp[i] = stoi(PhanDu);
			str = PhanNguyen;
			PhanNguyen.clear();
			PhanDu.clear();
			i++;
		}
	}
	int j = 0;
	for (int i = MAX-1; i >= 0; i--)
	{
		ketQua[j] = temp[i];
		j++;
	}
	
	if (flag == true)
	{
		LaySoBu2(ketQua);
	}
}
void ScanfQInt(QInt &number, int dayNhiPhan[])
{
	for (int i = 0; i < MAX; i++)
	{
		if (dayNhiPhan[i] == 1)
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i%32));
		}
	}
	cout << endl;
	cout <<bitset<32>(number.data[3]) << endl;  //in ra dãy bit
}
int main()
{
	QInt number;
	/*string s = "8793278316383117319";
	string a, b;
	int dayNhiPhan[MAX];
	Doi_Sang_Nhi_Phan(s,dayNhiPhan);
	ScanfQInt(number, dayNhiPhan);*/
	string s = "-8793278316383117319";
	string a, b;
	int dayNhiPhan[MAX];
	Doi_Sang_Nhi_Phan(s, dayNhiPhan);
	ScanfQInt(number, dayNhiPhan);
	system("pause");
	return 0;
}