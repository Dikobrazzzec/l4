#include <Windows.h>
#include <wincrypt.h>
#include <iostream>

using namespace std;

void FirstPart() {
	BYTE Data[100];
	BYTE basKeyArr[100];
	DWORD QuanBytes;
	cout << " Enter quantity  of bytes" << endl;
	cin >> QuanBytes;
	HCRYPTPROV a;
	CryptAcquireContext(&a, NULL, NULL, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT);
	CryptGenRandom(a, QuanBytes, Data);
	CryptGenRandom(a, 100, basKeyArr);
	for (int i = 0; i < 100; i++) {
			cout << hex << int(Data[i]);
	}
	cout << endl;
	cout <<"|||||||||||||||||||||||||||||||||||||||||||" <<endl;
	HCRYPTPROV q;
	HCRYPTKEY keyDesk;
	HCRYPTHASH hashDesk;
	HCRYPTHASH hashDeskEn;
	HCRYPTHASH hashDeskDec;
	CryptAcquireContext(&q, NULL, NULL, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT);
	CryptCreateHash(q, CALG_MD5, 0, 0, &hashDesk);
	CryptCreateHash(q, CALG_MD5, 0, 0, &hashDeskEn);
	CryptCreateHash(q, CALG_MD5, 0, 0, &hashDeskDec);
	//if (!CryptHashData(hashDesk, basKeyArr, 100, 0)) {
	//	cout << '2';
	//}
	if (!CryptDeriveKey(q,CALG_3DES, hashDesk, CRYPT_EXPORTABLE, &keyDesk)) {
		cout << '1';
	}
	DWORD size = QuanBytes;
	cout << size << endl;
	if (!CryptEncrypt(keyDesk, hashDeskEn, TRUE, NULL, Data, &size, 100)) {
		cout << '3' << endl;
	}
	for (int i = 0; i < 100; i++) {
		cout << hex << int(Data[i]);
	}
	cout << endl;
	cout << size << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
	if (!CryptDecrypt(keyDesk, hashDeskDec, TRUE, 0, Data, &size)) {
		cout << '4' << endl;
	}
	for (int i = 0; i < 100; i++) {
		cout << hex << int(Data[i]);
	}
	cout << endl;
	cout << size << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
	for (int i = 0; i < size; i++) {
		cout << hex << int(Data[i]);
	}
	cout << endl;
}

void SecondPart() {
	HCRYPTPROV cryptDesk;
	HCRYPTPROV q;
	HCRYPTKEY keyDesk;
	LPCTSTR contName = L"Containerrrr";
	CryptAcquireContext(&cryptDesk, contName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET);
	if (!CryptGenKey(cryptDesk, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &keyDesk)) {
		cout << '1' << endl;
	}
}

int main()
{
	FirstPart();
	SecondPart();
}
