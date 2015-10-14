#include "aesCrypto.h"

#include <string.h>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <iostream>

#define AESBlockSize 16

std::string AESCrypto::encryptECBWithBase64(const std::string& data, const std::string& key) {
  AES_KEY aes_enc_key;
  AES_set_encrypt_key((const unsigned char*)key.c_str(), 128, &aes_enc_key);

  int size = (data.size() / AESBlockSize) + 1;
  unsigned char* out = new unsigned char[size * AESBlockSize]();

  size_t len = data.size();
  size_t i = 0;
  for (i = 0; i < data.size(); i += AESBlockSize) {
    int blockSize = len - i > AESBlockSize ? AESBlockSize : len - i;
    unsigned char block[AESBlockSize] = { 0 };
    memcpy(block, data.c_str() + i, blockSize);

    AES_encrypt(block, out + i, &aes_enc_key);
  }

  //for(i = 0; i < 16; i++) {
  //  printf("0x%x\n", out[i] & 0xff);
  //}

  std::string result = base64Encode(out, i);

  delete []out;

  return result;
}

std::string AESCrypto::decryptECBWithBase64(const std::string& data, const std::string& key) {
  AES_KEY aes_enc_key;
  AES_set_decrypt_key((const unsigned char*)key.c_str(), 128, &aes_enc_key);
  
  int hexLen = getBase64DecodeLen(data);
  unsigned char* buffer = new unsigned char[hexLen];
  int byteLen = base64Decode(data, buffer);
  std::string hex((char*)buffer, byteLen);

  //for(int j = 0; j < 16; j++) {
  //  printf("0x%x\n", buffer[j] & 0xff);
  //}

  delete[]buffer;

  int size = (hex.size() / AESBlockSize) + 1;
  unsigned char* out = new unsigned char[size * AESBlockSize]();
  out[size - 1] = 0;

  size_t len = hex.size();
  size_t i = 0;
  for (i = 0; i < hex.size(); i += AESBlockSize) {
    int blockSize = len - i > AESBlockSize ? AESBlockSize : len - i;
    unsigned char block[AESBlockSize] = { 0 };
    memcpy(block, hex.c_str() + i, blockSize);

    AES_decrypt(block, out + i, &aes_enc_key);
  }

  //for(i = 0; i < 17; i++) {
  //  printf("0x%x\n", out[i] & 0xff);
  //}

  std::string result((char*)out);

  delete []out;

  return result;
}


std::string AESCrypto::base64Encode(const unsigned char* input, int len) {
  BIO *bmem, *b64;
  BUF_MEM *bptr;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);

  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO_write(b64, input, len);
  if (BIO_flush(b64)) {
    BIO_get_mem_ptr(b64, &bptr);
  }

  std::string result(bptr->data, bptr->length);

  BIO_free_all(b64);

  return result;
}

int AESCrypto::base64Decode(const std::string& input, unsigned char* output) {
  BIO *bio, *b64;

  bio = BIO_new_mem_buf((unsigned char*)input.c_str(), -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio,
    BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
  int len = BIO_read(bio, output, input.size());
  BIO_free_all(bio);

  return len;
}

int AESCrypto::getBase64DecodeLen(const std::string& b64input) {
  size_t len = b64input.size(),
    padding = 0;

  if (b64input[len - 1] == '='
    && b64input[len - 2] == '=') { //last two chars are =
    padding = 2;
  }
  else if (b64input[len - 1] == '=') { //last char is =
    padding = 1;
  }

  return (len * 3) / 4 - padding;
}
