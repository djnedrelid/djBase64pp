#pragma once

//
//	Struktur for lagring av bytedata.
//
struct ByteData {
	unsigned long Size = 0;
	unsigned char* Bytes = 0;
};

//
//	Klasse for å enkode og dekode bytes med Base64.
//
class djBase64
{
	public:
	static std::string EncodeBytes(ByteData* bd)
	{
		char base64_table[65];
		table(base64_table);

		// Hent alle bits fra bytes.
		std::string bits;
		for (unsigned long a = 0; a < bd->Size; a++) {
			std::bitset<8> b(bd->Bytes[a]);
			bits.append(b.to_string());
		}

		//std::ofstream _debug ("encode_orig_bit_string.txt");
		//_debug.write(bits.c_str(), bits.length());

		// Del de opp i 6-bit deler og lag en base64 streng.
		std::string base64str = "";
		std::string sixbit = "";
		int c;

		// Håndter komplette 6-bit sekvenser.
		for (unsigned int a = 0; a < bits.length(); a++) {
			if (sixbit.length() == 6) {
				c = std::stoi(sixbit, nullptr, 2);
				base64str.push_back(base64_table[c]);
				sixbit.clear();
			}
			sixbit.append(bits.substr(a, 1));
		}

		// Håndter gjenstående bits.
		if (sixbit.length() > 0) {
			while (sixbit.length() < 6)
				sixbit.push_back('0');
			c = std::stoi(sixbit, nullptr, 2);
			base64str.push_back(base64_table[c]);
		}

		//
		// Legg på = padding hvis strengen ikke er delbar med 4.
		// Det trengs 4 base64 karakterer for å dekode 3 bytes.
		// Det trengs 3 base64 karakterer for å dekode 2 bytes.
		// Det trengs 2 base64 karakterer for å dekode 1 byte.
		// Dette er fordi 1x 8-bit tar 2x 6-bit lengder.
		// Ved dekoding vet man ved hjelp av padding hvor mange 
		// bytes det er på slutten av en streng.
		//
		// Ikke så nyttig ved kun dekoding av enkeltstrenger, men
		// nyttig I tilfelle man dekoder strenger på rekke og rad.
		//
		while (base64str.length() % 4)
			base64str.push_back('=');

		return base64str;
	}



	static void DecodeBytes(std::string Base64String, ByteData* bd)
	{
		// Base64 alfabet.
		char base64_table[65];
		table(base64_table);

		// Hent alle bits til en lang streng, unntatt =.
		std::string bits;
		for (size_t a = 0; a < Base64String.length(); a++) {

			for (int b = 0; b < 65; b++) {
				if (Base64String[a] == base64_table[b]) {
					std::bitset<6> sixbits(b);
					bits.append(sixbits.to_string());
				}
			}

			// Ta høyde for padding.
			if (Base64String[a] == '=') {
				for (int c = 0; c < 6; c++)
					bits.pop_back();

				// Fjern evt. 0 padding utført på slutten.
				while (bits.length() % 8)
					bits.pop_back();
			}
		}

		//std::ofstream _debug ("decode_orig_bit_string.txt");
		//_debug.write(bits.c_str(), bits.length());

		// Bit-streng bør nå være klar for dekoding.
		std::string eightbit = "";
		std::vector<unsigned char> c;
		for (size_t a = 0; a < bits.length() + 1; a++) {

			// bits.length()+1 gjør at alle bits blir sjekket.
			if (eightbit.length() == 8) {
				c.push_back(std::stoi(eightbit, nullptr, 2));
				eightbit.clear();
			}

			// Ikke gå over indeks.
			if (a < bits.length())
				eightbit.push_back(bits[a]);
		}

		// Skriv bytes til pekt datastruktur.
		bd->Size = (unsigned long)c.size();
		bd->Bytes = (unsigned char*)malloc(sizeof(unsigned char) * bd->Size);
		for (size_t a = 0; a < c.size(); a++)
			bd->Bytes[a] = c[a];
	}



	private:
	static void table(char* out_table)
	{
		// Base64 alfabet.
		char base64_table[65] = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9', '+', '/',
			'='
		};

		// Kopier til tabell som spør.
		for (int a = 0; a < 65; a++)
			out_table[a] = base64_table[a];
	}
};