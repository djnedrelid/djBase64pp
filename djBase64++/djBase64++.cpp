#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <Windows.h>
#include "base64.h"
#include "djFileBytes.h"

int main()
{
	setlocale(LC_ALL, "");

	//
	//	Test med filer.
	//

	ByteData BD;

	// Les bytes fra fil.
	djFileBytes::ReadFileBytes("ani.gif", &BD);

	// Kod om til base64 og tilbake igjen.
	std::string Base64String = djBase64::EncodeBytes(&BD);
	free(BD.Bytes);
	std::cout << "\r\nEnkoder ani.gif og skriver dekodet output til ani_out.gif ...\r\n";
	djBase64::DecodeBytes(Base64String, &BD);

	// Skriv bytes til fil.
	djFileBytes::WriteFileBytes(&BD, "ani_out.gif");

	// Trenger ikke ta vare på bytes i minnet lenger.
	free(BD.Bytes);

	std::cout << "Ferdig med filtest, sjekk resultat.\r\n\r\n";



	//
	//	Tester i denne omgang med wchar_t tekstdata.
	//

	std::wstring orig_tekst = L"æøåÆØÅ er fine norske bokstaver.";
	std::wcout << L"Skal enkode: " << orig_tekst;

	// Hent byte-vis alle wchar_t's inn i orig_bytes.
	std::vector<unsigned char> orig_bytes;
	unsigned char wchar_bytes[2] = {0};
	for (int a = 0; a < orig_tekst.size(); a++) {
		*(wchar_t*)&wchar_bytes[0] = *(wchar_t*)&orig_tekst[a];
		orig_bytes.push_back(wchar_bytes[0]);
		orig_bytes.push_back(wchar_bytes[1]);
	}
	std::cout << " (" << orig_bytes.size() << " bytes).\r\n";

	// Reserver minne til å holde tekstdata.
	BD.Size = (unsigned long)orig_bytes.size();
	BD.Bytes = (unsigned char*)malloc(sizeof(unsigned char) * BD.Size);
	for (size_t a = 0; a < BD.Size; a++) 
		BD.Bytes[a] = orig_bytes.data()[a];
	orig_bytes.clear();

	// Vis enkoding av streng.
	Base64String = djBase64::EncodeBytes(&BD);
	std::cout << "Enkodet streng: " << Base64String << "\r\n\r\n";
	free(BD.Bytes);
	
	// Vis dekoding av sammensatt streng for å bekrefte at padding tas høyde for.
	Base64String = Base64String + Base64String + Base64String;
	djBase64::DecodeBytes(Base64String, &BD);
	wchar_t dekodet_karakter[2] = L" ";
	std::wstring dekodet_tekst = L"";
	for (size_t a = 0; a < BD.Size; a += 2) {
		*(wchar_t*)&dekodet_karakter[0] = *(wchar_t*)&BD.Bytes[a];
		dekodet_tekst.append(dekodet_karakter);
	}

	std::wcout << L"Dekoder 3x sammensatt streng på ett kall for å teste padding: \r\n" << dekodet_tekst << " (" << BD.Size << " bytes).\r\n\r\n";
	free(BD.Bytes);
}