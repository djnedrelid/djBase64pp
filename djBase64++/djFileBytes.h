#pragma once

//
//	Klasse for å lese og skrive filer binært.
//
class djFileBytes
{
public:
	static void ReadFileBytes(const char* filename, ByteData* bd)
	{
		FILE* fptr;
		size_t fres;

		// Åpne fil i binær lesemodus.
		fopen_s(&fptr, filename, "rb");
		if (fptr == 0) {
			std::cout << L"ReadFileBytes feilet å åpne filen." << std::endl;
			exit(1);
		}

		// Filstørrelse.
		fseek(fptr, 0, SEEK_END);
		bd->Size = ftell(fptr);
		rewind(fptr);

		// Reserver minne til å holde fildata.
		bd->Bytes = (unsigned char*)malloc(sizeof(unsigned char) * bd->Size);
		if (bd->Bytes == 0) {
			std::cout << L"ReadFileBytes feilet å reservere minne." << std::endl;
			exit(1);
		}

		// Kopier fila inn til minnet.
		fres = fread(bd->Bytes, 1, bd->Size, fptr);
		if (fres != bd->Size) {
			std::cout << L"ReadFileBytes feilet å lese filen til minnet." << std::endl;
			exit(1);
		}

		fclose(fptr);
	}

	static void WriteFileBytes(ByteData* fd, const char* filename)
	{
		FILE* fptr;
		size_t fres;

		// Åpne fil i binær skrivemodus.
		fopen_s(&fptr, filename, "wb");
		if (fptr == 0) {
			std::cout << L"WriteFileBytes feilet å åpne filen." << std::endl;
			exit(1);
		}

		fres = fwrite(fd->Bytes, 1, fd->Size, fptr);
		fclose(fptr);
	}
};