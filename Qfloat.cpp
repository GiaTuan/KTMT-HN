#include <iostream>
#include <string>
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
	string binary;


	// chia userInputStr cho 2 r lay so du bo vao binary
	for (int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary.push_back('1');
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary.push_back('0');
		userInputStr = chia2(userInputStr);
	}

	//Dao chuoi lai
	binary = reverse(binary);
	string so0(binary.size(), '0');
	if (binary == so0)
	{
		binary = "0";
	}
	else
	{
		binary = remove0(binary);
	}
	
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

void tachQFloat(string bigFloat, string& phanNguyen, string& phanThapPhan)
{
	int len = bigFloat.length();
	int dauCham = bigFloat.find_first_of('.');
	phanNguyen.assign(bigFloat, 0, dauCham);
	phanThapPhan.assign(bigFloat, dauCham, len - phanNguyen.length());//dg co dang (.x)
	phanThapPhan.insert(0, 1, '0');//dua ve dang (0.x)
}


void chuanHoaQFloat(string &number, int &soMu)
{
	string phanNguyen, phanThapPhan;
	tachQFloat(number, phanNguyen, phanThapPhan);
	phanNguyen = DecToBin(phanNguyen);

	bool kiemTra = false; // kiem tra dung de dem du 112 so
	bool kiemTra_1 = false; // neu so 1 nam o trong phan thap phan
	bool flag = false; // kiem tra neu so 1 nam o phan nguyen
	int n_PhanNguyen = phanNguyen.size();

	// neu n_PhanNguyen >112
	if (n_PhanNguyen > 112)
	{
		phanThapPhan = phanNguyen.substr(1, 112);
		if (phanNguyen[113] == '1')
		{
			phanThapPhan = CongBit(phanThapPhan, "1");
		}
		soMu = 112;
		number = "1.";
		number += phanThapPhan;
	}

	// neu n_PhanNguyen # 112
	else
	{
		int i = 0; // luu so luong chu so sau 1 cua phan nguyen
		if (phanNguyen[0] == '1')
		{
			i = n_PhanNguyen - 1;
			kiemTra = true;
			flag = true;
		}
		string sub = phanNguyen.substr(n_PhanNguyen - i); // tao mang con sau so 1 de noi voi day so thap phan

		string res;// ket qua
		res += sub;

		string tmp;  // bien tam de luu gia tri phan thap phan sau khi chuyen sang nhi phan
		int k = 0, m = 0; // bien dem 
		int j = 0; // luu vi tri so 1 dau tien cua phan thap phan
		int len_sauDauCham;
		string so1;		// de tao chuoi string = 1 de kiem tra sau khi * 2
		bool kiemTra_2 = false;  // 
		while (1)
		{
			phanThapPhan = phanThapPhan * 2;
			len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
			so1 = Float_1(len_sauDauCham);  // tao so 1 
			if (phanThapPhan == so1)
			{
				tmp.push_back('1');
				break;
			}
			else if (phanThapPhan > so1)
			{
				if (kiemTra_2 == false)
				{
					kiemTra_1 = true;
				}
				tmp.push_back('1');
				int DauCham = phanThapPhan.find_first_of('.');
				for (int i = 0; i < DauCham; i++)
				{
					phanThapPhan[i] = '0';
				}
			}
			else
			{
				tmp.push_back('0');
			}

			k++; // tang k
			if (kiemTra_2 == false && kiemTra_1 == true)
			{
				j = k;
				kiemTra_2 = true;
				kiemTra = true;
			}
			if (kiemTra == true)
			{
				m++;
			}
			if (flag == true)
			{
				if (m == 112 - i)
				{
					break;
				}
			}
			else
			{
				if (m == 112 - i + 1)
				{
					break;
				}
			}
		}

		if (kiemTra_1 == false && flag == false)
		{
			j = tmp.size();
			tmp = "0";
		}
		else
		{
			if (flag == false)
			{
				tmp = remove0(tmp);
				tmp.erase(0, 1);
			}
		}
		res += tmp;
		if (m + i >= 112)
		{
			phanThapPhan = phanThapPhan * 2;
			len_sauDauCham = SoPhanTuSauDauCham(phanThapPhan);
			so1 = Float_1(len_sauDauCham);
			if (phanThapPhan == so1 || phanThapPhan > so1)
			{
				res = CongBit(res, "1");
			}
		}
		string ketQua;
		soMu = flag == false ? -j : i;
		ketQua += "1.";
		ketQua += res;
		number = ketQua;
	}
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


string Dec_To_Bin(string number)
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
	int E;
	chuanHoaQFloat(number,E);
	E += 16383;
	string str_E = DecToBin(to_string(E));
	if (str_E.size() < 15)
	{
		str_E.insert(0, 1, '0');
	}
	number.erase(0, 2);

	int n = number.size();
	if (n < 112)
	{
		number.insert(n, 112 - n, '0');
	}
	res = res + str_E + number;
	return res;
}

void ScanQFloat(QFloat &x, string number)
{
	string res;
	int kiemTra = number.find_first_of('.');  // nêu số x nhập vào không có dấu . thì chuyển về x.0
	if(kiemTra == -1)
	{
		number += ".0";
	}
	res = Dec_To_Bin(number);
	cout << res << endl;
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

	if (bit == "0")
	{
		decNum = "0";
	}
	else
	{
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
	}
	return decNum;
}

void canBangHaiChuoi_2(string &a, string &b)
{
	int a_len = a.length(), b_len = b.length();
	if (a_len > b_len)
	{
		b.insert(b_len,a_len-b_len, '0');
	}
	else
	{
		a.insert(a_len,b_len-a_len, '0');
	}
}
string _2_Mu_Tru_N(int n)
{
	string res = "1";
	for (int i = 0; i < n; i++)
	{
		res = res * 5;
	}
	int len = res.size();
	n = n - len;
	if (n > 0)
	{
		res.insert(0, n, '0');
	}
	return res;
}

string BinToDec_PhanThapPhan(string str)
{
	string tmp, res="0";
	int n = str.length();

	for (int i = 0; i < n; i++)
	{
		if (str[i] == '1')
		{
			tmp = _2_Mu_Tru_N(i + 1);
			canBangHaiChuoi_2(tmp, res);
			res = res + tmp;
		}
	}
	return res;
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

string Bin_To_Dec(string arr)
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
	if (E > "16383")
	{
		E = E - "16383";
	}
	else
	{
		E = "16383" - E;
		E.insert(0, 1, '-');
	}

	xoa_0_Cuoi_String(S);
	string x = "1." + S;
	x.erase(1, 1);// xoa dau . 

	//them dau . vao
	int doDoi = stoi(E);
	if (doDoi >= 0)
	{
		if (x.size() == 1)
		{
			x.insert(1, doDoi, '0');
			x += ".0";
		}
		else if (doDoi > x.size())
		{
			x.insert(x.size(), doDoi - x.size()+1, '0');
			x += ".0";
		}
		else { x.insert(doDoi + 1, 1, '.'); }
	}
	else
	{
		x.insert(0, abs(doDoi), '0');
		x.insert(1, 1, '.');

	}
	if(x[x.size()-1]=='.')
	{
		x += "0";
	}
	string PhanNguyen, PhanThapPhan;
	tachQFloat(x, PhanNguyen, PhanThapPhan);
	
	// xoa dang 0. cua phan thap phan
	PhanThapPhan.erase(0, 2);
	
	//chuyen phan nguyen ve dang thap phan
	PhanNguyen = BinToDec(PhanNguyen);
	
	//chuyen phan thap phan sang dec
	PhanThapPhan=BinToDec_PhanThapPhan(PhanThapPhan);

	res += PhanNguyen;
	res += ".";
	res+=PhanThapPhan;
	return res;
}

void PrintQfloat(QFloat number)
{
	string arr = QFloat_To_Arr(number);
	string res=Bin_To_Dec(arr);
	cout << res;
}


int main()
{
	string s ="-945083490583940583904.01";
	QFloat a;
	ScanQFloat(a, s);
	PrintQfloat(a);

	system("pause");
	return 0;
}