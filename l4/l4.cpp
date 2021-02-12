#include <Windows.h>
#include <wincrypt.h>
#include <iostream>

using namespace std; 

BYTE* KeyWorker(HCRYPTKEY expKey, HCRYPTKEY Scrambler, DWORD* BLOBSIZE, int a) {
	if (a == 1) {
		cout << expKey << "  " << Scrambler << endl;
		BYTE DATABLOB[200];
		if (!CryptExportKey(expKey, Scrambler, SIMPLEBLOB, 0, DATABLOB, BLOBSIZE)) {
			cout << "KW1      " << GetLastError() << endl;
		}
		return DATABLOB;
	}
}

void ContainerManipulation(BYTE data[], DWORD datasize) {
	HCRYPTPROV contDesk;
	HCRYPTPROV freeDesk;
	HCRYPTKEY seckeyDesk;
	HCRYPTKEY openkeyDesk;
	HCRYPTKEY newseckeyDesk;
	LPCWSTR contName = L"Container";
	if (!CryptAcquireContext(&freeDesk, 0, 0, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT)) {
		cout << "CM5      " << GetLastError();
	}
	if (!CryptAcquireContext(&contDesk, contName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
		cout << "CM1      " <<GetLastError()<< endl;
	}

	if (!CryptGenKey(contDesk, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &seckeyDesk)) {
		cout << "CM2      " << endl;
	}
	if (!CryptGetUserKey(contDesk, AT_KEYEXCHANGE, &openkeyDesk)) {
		cout << "CM3      " << GetLastError() << endl;
	}
	cout << "secret key"<<seckeyDesk << endl;
	cout << "openkey" << openkeyDesk << endl;
	if (!CryptEncrypt(seckeyDesk, 0, TRUE, 0, data, &datasize, 100)) {
		cout << "CM8      " << GetLastError() << endl;
	}
	if (!CryptAcquireContext(&contDesk, contName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_DELETEKEYSET)) {
		cout << "CM4      " << GetLastError() << endl;
	}
	for (int i = 0; i < datasize; i++) {
		cout << hex<<int(data[i]);
	}
	cout << endl;
	BYTE DATABLOB[200];
	DWORD BLOBSIZE=0;
	//KeyWorker(seckeyDesk, openkeyDesk, &BLOBSIZE, 1);
	if (!CryptExportKey(seckeyDesk, openkeyDesk, PRIVATEKEYBLOB, 0,DATABLOB,&BLOBSIZE)) {
		cout << "CM6      " << GetLastError() << endl;
	}
	//if (!CryptImportKey(freeDesk, DATABLOB, BLOBSIZE, openkeyDesk, 0, &newseckeyDesk)) {
	//	cout << "CM9      " << GetLastError() << endl;
	//}
	//if (!CryptDecrypt(newseckeyDesk, 0, TRUE, 0, data, &datasize)) {
	//	cout << "CM10      " << GetLastError() << endl;
	//}
	//else {
	//	for (int i = 0; i < datasize; i++) {
	//		cout << hex << int(data[i]);
	//	}
	//}
}

void  DataGen() {
	BYTE DATA[100];
	HCRYPTPROV dataDesk;
	DWORD DATAsize;
	if (!CryptAcquireContext(&dataDesk, 0, 0, PROV_RSA_SCHANNEL, CRYPT_VERIFYCONTEXT)) {
		cout << "DG1" << endl;
	}
	cout << "Enter quantity of bytes" << endl;
	cin >> DATAsize;
	if (!CryptGenRandom(dataDesk, DATAsize, DATA)) {
		cout << "DG2" << endl;
	}
	for (int i = 0; i < DATAsize; i++) {
		cout <<hex<<int( DATA[i]);
	}
	cout << endl;
	ContainerManipulation(DATA, DATAsize);
}







void main() {
	DataGen();
}