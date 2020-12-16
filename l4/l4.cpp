#include <Windows.h>
#include <wincrypt.h>
#include <iostream>

using namespace std;

void firtask() {
	BYTE basArr[100];
	BYTE basKeyArr[100];
	int QuanBytes;
	cout << " Enter quantity  of bytes" << endl;
	cin >> QuanBytes;
	cout << endl;
	HCRYPTPROV a;
	CryptAcquireContext(&a, NULL, NULL, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT);
	CryptGenRandom(a, QuanBytes, basArr);
	CryptGenRandom(a, 100, basKeyArr);
	BYTE* notEncrypted = new BYTE[QuanBytes];
	for (int i = 0; i < QuanBytes; i++) {
		notEncrypted[i] = basArr[i];
	}
//	for (int i = 0; i < 100; i++) {
//			cout << hex << int(basKeyArr[i]);
//	}
	HCRYPTPROV q;
	HCRYPTKEY keyDesk;
	HCRYPTHASH hashDesk;
	CryptAcquireContext(&q, NULL, NULL, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT);
	CryptCreateHash(q, CALG_MD5, 0, 0, &hashDesk);
	if (!CryptHashData(hashDesk, basKeyArr, 100, 0)) {
		cout << '2';
	}
	if (!CryptDeriveKey(q,CALG_3DES, hashDesk, CRYPT_EXPORTABLE, &keyDesk)) {
		cout << '1';
	}
	DWORD size = QuanBytes;
	CryptEncrypt(keyDesk, hashDesk, TRUE, NULL, notEncrypted, &size, );
}

int main()
{
	firtask();
}
