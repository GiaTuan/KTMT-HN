#include <iostream>
#include<string>
#include <array>

using namespace std;
#define MAX 128
typedef struct
{
	unsigned int data[4];
	// kiem tra so am
}QInt;

//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;
}

//xuất chuỗi nhị phân ra màn hình 
void xuat(array<int, MAX>a)
{
	for (int i=0;i<MAX;i++)
	{
		cout << a[i];
	}
	cout << endl;
}

int stringToNum(char c)     // chuyen char sang so
{
	return c - '0';
}

char numToString(int n)     // chuyen so sang char
{
	return (char)(n + 48);
}


string chia2(string bigInt)
{
	string tmp;
	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(bigInt.length());
	if (bigInt[0] - '0' < 2)
	{
		i = 1;
		j = 10;
	}
	for (; i < bigInt.length(); i++)
	{
		tmp[k++] = ((bigInt[i] - '0' + j) / 2 + '0');
		j = ((bigInt[i] - 48 + j) % 2) * 10;
	}
	tmp.resize(k);
	return tmp;
}
// Ham lay bu 1
array<int, MAX> bu1(array<int, MAX> a)
{
	array<int, MAX> tmp;
	for (int i = 0; i < MAX; i++)
	{
		tmp[i] = (a[i] == 1) ? 0 : 1;
	}
	return tmp;
}

//Ham lay bu 2
array<int, MAX> bu2(array<int, MAX> a)
{
	a = bu1(a);
	int soDu = 1;
	array<int, MAX> bu2 = { 0 };
	for (int i = MAX - 1; i >= 0; i--)
	{
		if (a[i] == 0 && soDu == 1)
		{
			bu2[i] = 1;
			soDu = 0;
		}
		else if (a[i] == 1 && soDu == 0)
		{
			bu2[i] = 1;
		}
	}

	return bu2;
}


//Ham dao nguoc mang (sau khi chia 2 thi he nhi phan la lay so du tu duoi len)
array<int, MAX> reverse(array<int, MAX>a)
{
	array<int, MAX> rev_arr = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		rev_arr[i] = a[MAX - i - 1];
	}
	return rev_arr;
}

//ham chuyen tu thap phan sang nhi phan
array<int, MAX> DecToBin(string userInputStr)
{
	array<int, MAX> binary = { 0 };
	bool kiemTra = false;
	if (userInputStr[0] == '-')
	{
		userInputStr.erase(0, 1);
		kiemTra = true;
	}

	for (unsigned short int i = 0; userInputStr.length() != 0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary[i] = 1;
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary[i] = 0;
		userInputStr = chia2(userInputStr);
	}
	array<int, MAX> res = reverse(binary);

	if (kiemTra)
	{
		res = bu2(res);
	}
	return res;

}


//Ham nhap so QInt, con thieu cai doc File, ko biet cho 2 tham so co dc ko
void ScanQInt(QInt &number, string userInputStr)
{
	initQInt(number);
	array<int, MAX> binArr = DecToBin(userInputStr);
	for (int i = 0; i < MAX; i++)
	{
		if (binArr[i] == 1)
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}

}
string nhan2(string bigInt)
{
	string res = "";
	int len = bigInt.length();
	int tmp = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		tmp = stringToNum(bigInt[i]) * 2 + tmp;
		res.insert(0, 1, numToString(tmp % 10));//lay phan don vi cho vao string
		tmp = tmp / 10;// lay phan chuc de tinh tiep
	}
	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}

string _2_mu_n(int n)
{
	string res = "1";
	for (int i = 1; i <= n; i++)
	{
		res = nhan2(res);
	}
	return res;

}

void canBang2Chuoi(string& a, string& b)// cho do dai 2 chuoi bang nhau de cong 2 chuoi lai
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


string String_Cong_String(string& a, string& b)
{
	string res = "";
	canBang2Chuoi(a, b);
	int len = a.length();

	int tmp = 0;
	for (int i = len - 1; i >= 0; i--)
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
string String_Tru_String(string& a, string& b)
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
			tmp = stringToNum(a[i]) -(stringToNum(b[i])+soDu);
			res.insert(0, 1, numToString(tmp));
			soDu = 0;
		}
		else 
		{
			tmp = (10 + stringToNum(a[i])) - (stringToNum(b[i])+soDu);
			res.insert(0, 1, numToString(tmp));
			soDu = 1;
		}
	}
	return res;

}
//Ham chuyen tu QInt sang mang int a[MAX]
array<int, MAX> QInt_To_Arr(const QInt& number)
{
	array<int, MAX> a = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		if ((number.data[i / 32] >> (32 - 1 - i % 32)) & 1 == 1)
		{
			a[i] = 1;
		}
	}
	return a;
}

void Ham_Xoa_So_0_Dau_Chuoi(string &str)
{
	int i = 0;
	for (i; i < MAX; i++)
	{
		if (str[i] != '0')
		{
			break;
		}
	}
	str.erase(0, i);
}

string Bin_to_Dec(array<int, MAX>a)
{
	string decNum;
	int i;
	bool isSigned = false;
	if (a[0] == 1)
	{
		i = 1;
		isSigned = true;
	}
	else
	{
		i = 0;
	}
	for (i; i < MAX; i++)
	{
		if (a[i] == 1)
		{
			string x = _2_mu_n(MAX - 1 - i);
			decNum = String_Cong_String(decNum, x);
		}
	}
	if (isSigned == true)
	{
		string x = _2_mu_n(MAX - 1);
		decNum = String_Tru_String(x, decNum);
		Ham_Xoa_So_0_Dau_Chuoi(decNum);
		decNum.insert(0, 1, '-');
	}
	return decNum;
}

//ham xuat so QInt, xuat ra so he thap phan
void PrintQInt(QInt number)
{
	//chuyen tu QInt sang mang a
	array<int, MAX>a = { 0 };
	a=QInt_To_Arr(number);
	xuat(a);
	//Tu mang nhi phan a chuyen sang so thap phan
	string decNum = Bin_to_Dec(a);
	cout << "\nSo chuyen sang he thap phan: ";
	if (decNum.size() == 0)
	{
		cout << '0';
	}
	cout << decNum;
}

//======================================== HÀM TOÁN TỬ ================================

QInt Arr_To_QInt(const array<int, MAX>& binArr)
{
	QInt number;
	initQInt(number);
	for (int i = 0; i < MAX; i++)
	{
		if (binArr[i] == 1)
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}
// ======================================================

int viTriBit1(array<int,MAX> a, int viTriDangXet=0)
{
	int i = viTriDangXet;

	for (i; i < MAX; i++)
	{
		if (a[i] == 1)
		{
			return i;
		}
	}
	return -1;
}
bool IsSign(QInt num)
{
	array<int, MAX>a = QInt_To_Arr(num);
	if (a[0] == 1)
	{
		return true;
	}
	return false;
}

bool operator < (const QInt& a, const QInt& b)
{
	if (IsSign(a) == false && IsSign(b) == true)
	{
		return false;
	}
	else if (IsSign(a) == true && IsSign(b) == false)
	{
		return true;
	}
	else
	{
		//chuyen QInt qua mang de so sanh
		array<int, MAX> arr1 = { 0 };
		arr1=QInt_To_Arr(a);
		
		array<int,MAX> arr2 = { 0 };
		arr2=QInt_To_Arr(b);

		// tim vi tri bit 1 dau tien
		int bit1_A = viTriBit1(arr1);
		int bit1_B = viTriBit1(arr2);
		while (1)
		{
			if (bit1_A == -1 && bit1_B == -1)
			{
				return false;
			}
			else if (bit1_A > bit1_B)//vi tri bit 1 cua a > vi tri bit 1 dau tien cua b
			{
				return true;
			}
			else if (bit1_A < bit1_B)
			{
				return false;
			}
			else if (bit1_A == bit1_B)
			{
				bit1_A = viTriBit1(arr1, bit1_A+1);
				bit1_B = viTriBit1(arr2, bit1_B+1);
			}
		}
	}
}



bool operator > (const QInt& a, const QInt& b)
{
	return !(a < b);
}




bool operator == (const QInt& a, const QInt& b)
{
	bool flag = true;

	//chuyen QInt qua mang de so sanh
	array<int,MAX>  arr1;
	arr1=QInt_To_Arr(a);
	array<int, MAX>  arr2;
	arr2=QInt_To_Arr(b);

	for (int i = 0; i < MAX; i++)
	{
		if (arr1[i] != arr2[i])
		{
			flag = false;
			break;
		}
	}
	return flag;
}


bool operator <= (const QInt& a, const QInt& b)
{
	if (a < b || a == b)
	{
		return true;
	}
	return false;
}



bool operator >= (const QInt& a, const QInt& b)
{
	if (a > b || a == b)
	{
		return true;
	}
	return false;
}
//========================================================================================
// operator + 
// lấy giá trị tuyệt đối của QInt number 
QInt Abs(QInt number)
{
	array<int, MAX> a;
	a = QInt_To_Arr(number);
	a = bu2(a);
	return Arr_To_QInt(a);
}

QInt operator+(QInt number1, QInt number2)
{
	array<int, MAX> a = { 0 };
	array<int, MAX> b = { 0 };
	array<int, MAX>res = { 0 };
	a=QInt_To_Arr(number1);
	b=QInt_To_Arr(number2);
	QInt number;

	int temp = 0;
	for (int i = MAX - 1; i >= 0; i--)
	{
		temp = a[i] + b[i] + temp;
		if (temp == 2)
		{
			res[i] = 0;
			temp = 1;
		}
		else if (temp == 3)
		{
			res[i] = 1;
			temp = 1;
		}
		else
		{
			res[i] = temp;
			temp = 0;
		}
	}
;
	number = Arr_To_QInt(res);
	return number;
}
//


//dang test

 //operator - 
QInt operator-(QInt number1, QInt number2)
{
	QInt number= Abs(number2);
	return number1 + number;
}

//=============================================== test theo kiểu của Tường là sử dụng toàn string 
string QInt_To_String(const QInt& number)
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
QInt String_To_QInt(const string& binArr)
{

	string _128bit = binArr;
	int n = binArr.length();
	if (n < 128)
	{
		_128bit.insert(0, 128 - n, '0');
	}

	QInt number;
	initQInt(number);
	for (int i = 0; i < 128; i++)
	{
		if (_128bit[i] == '1')
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}

void dichPhaiString(string &str)
{
	bool kiemTra=false;
	if (str[0] == '1')
	{
		kiemTra = true;
	}
	int n = str.size();
	for (int i = n - 1; i >= 1; i--)
	{
		str[i] = str[i - 1];
	}
	if (kiemTra == true)
	{
		str[0] = '1';
	}
}

//====================================================================================================
// phep nhan


QInt operator*(QInt number1, QInt number2)   
{
	string a=QInt_To_String(number1), b= QInt_To_String(number2);
	int n = a.size();
	int k = n;
	string A, A_Q_Qo;
	int i = 0;
	QInt number;


	//them n so 0 vao A;
	for ( i ; i < n; i++)
	{
		A.push_back('0');
	}
	number = String_To_QInt(A);
	A_Q_Qo += A;

	// noi chuoi Q vao A_Q_Qo
	A_Q_Qo += b;



	 //them Qo vao A_Q_Qo
	A_Q_Qo.push_back('0');


	n = A_Q_Qo.size();


	//// execute
	while (k > 0)
	{
		if (A_Q_Qo[n - 2] == '1'&&A_Q_Qo[n - 1] == '0')
		{
			number = number - number1;// A=A-Q
			A = QInt_To_String(number);
			int m = A.size();
			A_Q_Qo.replace(0, m, A); 
		}
		else if (A_Q_Qo[n - 2] == '0'&&A_Q_Qo[n - 1] == '1')
		{
			number = number + number1; // A=A+Q
			A = QInt_To_String(number);
			int m = A.size();
			A_Q_Qo.replace(0, m, A);
		}
		dichPhaiString(A_Q_Qo);
		A = A_Q_Qo.substr(0, MAX + 1); // luu lai gia tri moi cua A 
		number = String_To_QInt(A);
		k--;
	}
	A_Q_Qo.pop_back();
	A_Q_Qo = A_Q_Qo.substr(A_Q_Qo.size() - MAX);
	return String_To_QInt(A_Q_Qo);
	
}

//============================== OPERATOR/===============================


//=======================================lam theo ham isgin cua tuong

bool IsSign_2(string num)
{
	return (num[0] == '1') ? true : false;
}

void dichTraiString(string &str)
{
	int n = str.size();
	for (int i = 0; i <n-1; i++)
	{
		str[i] = str[i + 1];
	}
	str[n - 1] = '0';
}

// Ham lay bu 1
string bu_1(string a)
{
	string tmp;
	for (int i = 0; i < MAX; i++)
	{
		char x = (a[i] == '1') ? '0' : '1';
		tmp.push_back(x);
	}
	return tmp;
}


//Ham lay bu 2
string bu_2(string a)
{
	string dayBu1 = bu_1(a);
	int soDu = 1;
	string bu2;
	for (int i = MAX - 1; i >= 0; i--)
	{
		char x;
		if (dayBu1[i] == '0' && soDu == 1)
		{
			x = '1';
			soDu = 0;
		}
		else if (dayBu1[i] == '0'&& soDu == 0)
		{
			x = '0';
			soDu = 0;
		}
		else if (dayBu1[i] == '1' && soDu == 0)
		{
			x = '1';
			soDu = 0;
		}
		else if (dayBu1[i] == '1'&& soDu == 1)
		{
			x = '0';
			soDu = 1;
		}
		bu2.insert(0, 1, x);
	}
	return bu2;
}
bool kiemTraQInt(string a)  //kiem tra number co phai la so 0 hay khong
{
	int n = a.size();
	for (int i = 0; i < n; i++)
	{
		if (a[i] != '0')
		{
			return false;
		}
	}
	return true;

}

QInt operator/(QInt number1, QInt number2)
{
	string M = QInt_To_String(number2);
	/*bool la_So_0 = false;
	if (kiemTraQInt(M) == true)
	{
		cout<<"aaaaa" ;
	}*/
	string Q = QInt_To_String(number1);
	bool kiemTra = false;
	if (IsSign_2(Q) == true && IsSign_2(M) == false) 	
	{
		Q = bu_2(Q);
		number1 = String_To_QInt(Q);
		kiemTra = true;
	}
	else if (IsSign_2(Q) == false && IsSign_2(M) == true)
	{
		M = bu_2(M);
		number2 = String_To_QInt(M);
		kiemTra = true;
	}
	else if (IsSign_2(Q) == true && IsSign_2(M) == true)
	{
		M = bu_2(M);
		Q = bu_2(Q); 
		number1 = String_To_QInt(Q);
		number2 = String_To_QInt(M);
	}
	string A;
	int n = Q.size();
	if (IsSign_2(Q) == false)
	{
		for (int i = 0; i < n; i++)
		{
			A.push_back('0');
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			A.push_back('1');
		}
	}
	int k = n;
	string A_Q;
	QInt number;
	A_Q += A + Q;
	while(k>0)
	{
		dichTraiString(A_Q);
		A = A_Q.substr(0, n);
		Q = A_Q.substr(n);

		//A=A-M
		number = String_To_QInt(A);
		number = number - number2;
		A = QInt_To_String(number);
		if (IsSign_2(A) == true)
		{
			Q[n - 1] = '0';
			number = number + number2;
			A = QInt_To_String(number);
		}
		else
		{
			Q[n - 1] = '1';
		}
		A_Q.clear();
		A_Q += A + Q;
		k--;
	}
	Q = A_Q.substr(n);

	if (kiemTra == true)
	{
		Q = bu_2(Q);
	}
	
	return String_To_QInt(Q);
}

int main()
{
	string s = "-10432534343434332332323246464554740";
	string ss = "999999";

	QInt number1;
	QInt number2;

	ScanQInt(number1, s);
	//PrintQInt(number1);
	cout << endl;
	ScanQInt(number2, ss);
	//PrintQInt(number2);
	cout << endl;
	QInt x=number1 /number2;
	PrintQInt(x);


	/*if (number1 >= number2)
	{
		cout << "haha";
	}
	else
		cout << "hi";*/
	system("pause");
	return 0;
}