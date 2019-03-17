#include <iostream>
#include <string>
#include <bitset>
using namespace std;
#define MAX 128

typedef struct
{
	uint32_t data[4] = { 0 };
}QFloat;

bool IsSign(string num)
{
	return (num[0] == '-') ? true : false;
}


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
	if (k == 112)
	{
		phanThapPhan = phanThapPhan * 2;
		len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
		so1 = Float_1(len_sauDauCham);
		if (phanThapPhan == so1 || phanThapPhan > so1)
		{
			res = CongBit(res, "1");
		}
	}
	return res;
}


void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan)
{
	int len = bigFloat.length();
	int dauCham = bigFloat.find_first_of('.');
	phanNguyen.assign(bigFloat, 0, dauCham);
	phanThapPhan.assign(bigFloat, dauCham, len - phanNguyen.length());//dg co dang (.x)
	phanThapPhan.insert(0, 1, '0');//dua ve dang (0.x)
}


int chuanHoaQFloat(string& floatNum)
{
	int exponent;
	int dauCham = floatNum.find_first_of('.');
	int so1DauTien = floatNum.find_first_of('1');

	int viTri = (dauCham > so1DauTien) ? so1DauTien + 1 : so1DauTien;
	floatNum.erase(dauCham, 1);
	floatNum.insert(viTri, 1, '.');
	exponent = (dauCham > so1DauTien) ? dauCham - so1DauTien - 1 : dauCham - so1DauTien;
	return exponent;
}
QFloat Arr_To_QFloat(const string& binArr)
{

	QFloat number;
	for (int i = 0; i < MAX; i++)
	{
		if (binArr[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}
string ChuyenSangNhiPhan(string number)
{
	string PhanNguyen, PhanThapPhan;
	tachQFloat(number, PhanNguyen, PhanThapPhan);
	PhanNguyen = DecToBin(PhanNguyen);
	PhanThapPhan = DecToBin_phanThapPhan(PhanThapPhan);
	string res;
	res = PhanNguyen + '.' + PhanThapPhan;
	return res;
}



void ScanQFloat(QFloat &x, string number)
{
	string res;
	if (IsSign(number) == true)
	{
		res.push_back('1');
		number.erase(0, 1);
	}
	else
	{
		res.push_back('0');
	}
	string temp=ChuyenSangNhiPhan(number);
	int E = chuanHoaQFloat(temp);
	E += 16383;
	string str_E = DecToBin(to_string(E));
	cout << "E: "<<str_E << endl;
	temp.erase(0, 2);
	
	int n = temp.size();
	if (n < 112)
	{
		temp.insert(n, 112 - n, '0');
	}
	res = res + str_E + temp;
	x = Arr_To_QFloat(res);

}
string QFloat_To_Arr(const QFloat& number)
{
	string a;
	for (int i = 0; i < MAX; i++)
	{
		if ((number.data[i / 32] >> (32 - 1 - i % 32)) & 1 == 1)
		{
			a.push_back('1');
		}
		else
		{
			a.push_back('0');
		}
	}
	return a;
}
string _x_mu_n(int coSo, int soMu)
{
	bool soAm = false;
	if (coSo < 0)
	{
		soAm = (soMu % 2 == 0) ? false : true;
		coSo *= -1;
	}
	string res = "1";
	for (int i = 1; i <= soMu; i++)
	{
		res = res * coSo;
	}
	if (soAm)
		res.insert(0, 1, '-');

	return res;
}
string operator+(string a, string b)
{
	string res = "";
	canBang2Chuoi(a, b);
	int len = a.length();

	int tmp = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		tmp = stringToNum(a[i]) + stringToNum(b[i]) + tmp;
		res.insert(0, 1, numToString(tmp % 10));
		tmp /= 10;
	}
	if (tmp > 0)
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}

string operator-(string a, string b)
{
	string res = "";
	canBang2Chuoi(a, b);
	int len = a.length();
	int tmp = 0;
	int soDu = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (a[i] >= b[i])
		{
			tmp = stringToNum(a[i]) - (stringToNum(b[i]) + soDu);
			res.insert(0, 1, numToString(tmp));
			soDu = 0;
		}
		else
		{
			tmp = (10 + stringToNum(a[i])) - (stringToNum(b[i]) + soDu);
			res.insert(0, 1, numToString(tmp));
			soDu = 1;
		}
	}
	res=remove0(res);
	return res;
}


string BinToDec(string bit)
{
	string decNum, tmp;

	for (int i = 0; i < bit.length(); i++)
	{
		if (bit[i] == '1')
		{
			tmp = _x_mu_n(2, bit.length() - i - 1);
		}
		else
		{
			tmp = "0";
		}
		decNum = decNum + tmp;
	}
	return decNum;
}

//string _1_Chia_N(string)
//{
//	return "0."
//}

void BinToDec_PhanThapPhan(string str)
{
	string decNum, tmp;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '1')
		{
			tmp = _x_mu_n(2, str.length() - i - 1);
		}
		else
		{
			tmp = "0";
		}
		decNum = decNum + tmp;
	}
}
void xoa_0_Cuoi_String(string &str)
{
	int n = str.size();
	int i;
	for (i = n - 1; i >= 0; i--)
	{
		if (str[i] != '0')
		{
			break;
		}
	}
	str.erase(i+1);
}

void Bin_To_Dec(string arr)
{
	string res;
	if (arr[0] == '1')
	{
		res.push_back('-');
	}
	arr.erase(0, 1);
	string E_str;
	string S;

	E_str = arr.substr(0, 15);
	S = arr.substr(15);

	string E = BinToDec(E_str);
	E = E - "16383";

	xoa_0_Cuoi_String(S);
	string x = "1." + S;
	int i = x.find_first_of('.');
	x.erase(i, 1);
	x.insert(stoi(E)+1, 1, '.');
	cout << x << endl;
	string PhanNguyen, PhanThapPhan;
	tachQFloat(x, PhanNguyen, PhanThapPhan);
	PhanThapPhan.erase(0, 2);
	cout << PhanNguyen << " " << PhanThapPhan << endl;
	PhanNguyen = BinToDec(PhanNguyen);
	res += PhanNguyen;
	res += ".";
	cout << res << endl;
	
}

void PrintQfloat(QFloat number)
{
	string arr = QFloat_To_Arr(number);
	Bin_To_Dec(arr);
	
}

int main()
{
	string s = "8.1";
	string ss = "-24.3017578125";
	QFloat a;
	ScanQFloat(a, ss);
	PrintQfloat(a);
	//cout << a << " " << b << endl;
	system("pause");
	return 0;
}