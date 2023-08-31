#pragma once
#include <string>
using namespace std;
namespace MyEncryptor
{
	bool Sha256UsingEVP(string text, string& hashed);
	bool DecryptAES(const std::string& encryptedData, std::string& decryptedData, string keyHex);
	std::string Base64Encode(const std::string& input);
	std::string Base64Decode(const std::string& input);
};

