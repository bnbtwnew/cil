#include "MyEncryptor.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/buffer.h>
#include <iomanip> // Include for setw and setfill 
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

namespace MyEncryptor {

    void hexStringToBytes(const std::string& hexString, unsigned char* bytes, size_t length) {
        for (size_t i = 0; i < length; i++) {
            std::sscanf(hexString.c_str() + 2 * i, "%2hhx", &bytes[i]);
        }
    }

    void removePadding(std::string& data) {
        if (!data.empty()) {
            size_t paddingLength = static_cast<size_t>(data.back());
            if (paddingLength <= data.length()) {
                data.resize(data.length() - paddingLength);
            }
        }
    }

    bool Sha256UsingEVP(string text, string& hashed) {
        std::stringstream hashStream;

        unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
        unsigned int lengthOfHash = 0;
        EVP_MD_CTX* context = EVP_MD_CTX_new();
        if (!EVP_DigestInit_ex(context, EVP_sha256(), NULL)) {
            return false;
        }
        if (!EVP_DigestUpdate(context, text.c_str(), text.length())) {
            return false;
        }
        if (!EVP_DigestFinal_ex(context, sha256_hash, &lengthOfHash)) {
            return false;
        }

        // Convert the hash to a hexadecimal string.
        std::stringstream sha256_stream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sha256_stream << std::hex << std::setw(2) << std::setfill('0') << (int)sha256_hash[i];
        }
        EVP_MD_CTX_free(context);
        hashed = sha256_stream.str();
        return true;
    }

    bool DecryptAES(const std::string& encryptedData, std::string& decryptedData, string keyHex) {
        // Base64 decode the input.
        std::string ciphertext = Base64Decode(encryptedData);

        // Convert the AES key from hexadecimal to binary.
        unsigned char aesKey[16];
        hexStringToBytes(keyHex, aesKey, sizeof(aesKey));

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

        const unsigned char* key = aesKey;
        const unsigned char* iv = nullptr; // IV is not needed for decryption.

        // Initialize decryption context.
        if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            std::cerr << "EVP_DecryptInit_ex() failed." << std::endl;
            return false;
        }

        // Decrypt the data.
        int len;
        int plaintextLen;

        // Allocate memory for the plaintext (output).
        decryptedData.resize(encryptedData.length());

        if (EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&decryptedData[0]), &len,
            reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.length()) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            std::cerr << "EVP_DecryptUpdate() failed." << std::endl;
            return false;
        }

        plaintextLen = len;

        if (EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&decryptedData[len]), &len) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            std::cerr << "EVP_DecryptFinal_ex() failed." << std::endl;
            return false;
        }

        plaintextLen += len;
        EVP_CIPHER_CTX_free(ctx);

        // Determine the padding size by inspecting the last byte of decryptedData.
        int paddingSize = static_cast<int>(decryptedData[plaintextLen - 1]);

        // Ensure that the padding size is within a valid range.
        if (paddingSize < 1 || paddingSize > EVP_CIPHER_CTX_block_size(ctx)) {
            std::cerr << "Invalid padding size." << std::endl;
            return false;
        }

        // Remove the PKCS#7 padding.
        decryptedData.resize(plaintextLen - paddingSize);

        return true;
    }

    std::string Base64Encode(const std::string& input) {
        BIO* bmem = BIO_new(BIO_s_mem());
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO_push(b64, bmem);

        BIO_write(b64, input.c_str(), static_cast<int>(input.length()));
        BIO_flush(b64);

        BUF_MEM* bptr;
        BIO_get_mem_ptr(b64, &bptr);

        std::string result(bptr->data, bptr->length);

        BIO_free_all(b64);

        return result;
    }

    std::string Base64Decode(const std::string& input) {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO* bmem = BIO_new_mem_buf(input.c_str(), static_cast<int>(input.length()));
        BIO_push(b64, bmem);

        std::string decoded;
        decoded.resize(input.length()); // Allocate space for decoding

        int decodedLen = BIO_read(b64, &decoded[0], static_cast<int>(decoded.size()));
        BIO_free_all(b64);

        if (decodedLen > 0)
            decoded.resize(decodedLen);
        else
            decoded.clear();

        return decoded;
    }

}