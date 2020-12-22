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
	CryptCreateHash(q, CALG_MD5, 0, 0, &hashDesk);  //3 параметр!!!!!!!!!!!!
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
	HCRYPTKEY openkeyDesk;
	HCRYPTHASH hashDesk;
	LPCTSTR contName = L"Name";
	CryptAcquireContext(&q, NULL, NULL, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT);
	CryptCreateHash(q, CALG_MD5, 0, 0, &hashDesk);    //3 параметр!!!!!!!!!!!
	BYTE DATA[100];
	DWORD DataArrSize;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<< endl;
	cout << " Enter quantity  of bytes" << endl;
	cin >> DataArrSize;
	CryptGenRandom(q, DataArrSize, DATA);
	for (int i = 0; i < DataArrSize; i++) {
		cout <<hex<<int( DATA[i]);
	}
	cout << endl;
	if (!CryptAcquireContext(&cryptDesk, contName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_SILENT)) {
		cout<<'2'<<endl;
	}
	if (!CryptGenKey(cryptDesk, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &keyDesk)) {
		cout << '1' << endl;
	}
	if (!CryptEncrypt(keyDesk, NULL, TRUE, NULL, DATA, &DataArrSize, 100)) {
		cout << '3' << endl;
	}
	cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
	for (int i = 0; i < DataArrSize; i++) {
		cout << hex << int(DATA[i]);
	}

	if (!CryptGetUserKey(q, AT_KEYEXCHANGE, &openkeyDesk)) {
		cout << '4' << endl;
	}
	BYTE DATABLOMB[200];
	DWORD DATABLOMBSize = 200;
	if (CryptExportKey(keyDesk, openkeyDesk, PRIVATEKEYBLOB, NULL, DATABLOMB, &DATABLOMBSize)) {
		cout << '5' << endl;
	}

}

int main()
{
	FirstPart();
	SecondPart();
}
