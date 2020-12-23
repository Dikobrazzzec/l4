#include <Windows.h>
#include <wincrypt.h>
#include <iostream>

using namespace std; 


void ContainerManipulation(BYTE data[], DWORD datasize) {
	HCRYPTPROV contDesk;
	HCRYPTPROV freeDesk;
	HCRYPTKEY seckeyDesk;
	HCRYPTKEY openkeyDesk;
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
	CryptEncrypt(seckeyDesk,0,TRUE,0,data,&datasize,100);
	if (!CryptAcquireContext(&contDesk, contName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_DELETEKEYSET)) {
		cout << "CM4      " << GetLastError() << endl;
	}
	for (int i = 0; i < datasize; i++) {
		cout << hex<<int(data[i]);
	}
	cout << endl;
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