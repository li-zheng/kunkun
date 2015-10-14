/*
This file is part of KUNKUN.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.


<aesCrypto.h>
<this class is used for AES encryption and decryption>

Author: Zheng Li
*/

#ifndef AES_CRYPTO_H
#define AES_CRYPTO_H

#include <string>

class AESCrypto {
public:
  std::string encryptECBWithBase64(const std::string& data, const std::string& key);
  std::string decryptECBWithBase64(const std::string& data, const std::string& key);

private:
  std::string base64Encode(const unsigned char* input, int len);
  int base64Decode(const std::string& input, unsigned char* output);
  int getBase64DecodeLen(const std::string& b64input);
};

#endif
