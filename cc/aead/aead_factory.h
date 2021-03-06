// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TINK_AEAD_AEAD_FACTORY_H_
#define TINK_AEAD_AEAD_FACTORY_H_

#include "cc/aead.h"
#include "cc/key_manager.h"
#include "cc/keyset_handle.h"
#include "cc/util/statusor.h"

namespace crypto {
namespace tink {

///////////////////////////////////////////////////////////////////////////////
// AeadFactory allows for obtaining an Aead primitive from a KeysetHandle.
//
// AeadFactory gets primitives from the Registry, which can be initialized
// via convenience methods from AeadConfig-class. Here is an example
// how one can obtain and use a Aead primitive:
//
//   AeadConfig.RegisterStandardKeyTypes();
//   KeysetHandle keyset_handle = ...;
//   std::unique_ptr<Aead> aead =
//       std::move(AeadFactory.GetPrimitive(keyset_handle).ValueOrDie());
//   string plaintext = ...;
//   string aad = ...;
//   string ciphertext = aead.Encrypt(plaintext, aad).ValueOrDie();
//
class AeadFactory {
 public:
  // Returns an Aead-primitive that uses key material from the keyset
  // specified via 'keyset_handle'.
  static util::StatusOr<std::unique_ptr<Aead>> GetPrimitive(
      const KeysetHandle& keyset_handle);

  // Returns an Aead-primitive that uses key material from the keyset
  // specified via 'keyset_handle' and is instantiated by the given
  // 'custom_key_manager' (instead of the key manager from the Registry).
  static util::StatusOr<std::unique_ptr<Aead>> GetPrimitive(
      const KeysetHandle& keyset_handle,
      const KeyManager<Aead>* custom_key_manager);

 private:
  AeadFactory() {}
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_AEAD_AEAD_FACTORY_H_
