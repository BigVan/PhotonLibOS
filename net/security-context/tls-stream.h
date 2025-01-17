/*
Copyright 2022 The Photon Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <photon/common/object.h>

namespace photon {
namespace net {

class ISocketStream;
class ISocketServer;
class ISocketClient;

enum class SecurityRole {
    Client = 1,
    Server = 2,
};

class TLSContext;

/**
 * @brief Create a tls context, contains cert and private key infomation.
 *
 * @param cert_str certificate in string format
 * @param key_str private key in string format
 * @param passphrase passphrase for private key
 * @return TLSContext* context object pointer
 */
TLSContext* new_tls_context(const char* cert_str, const char* key_str,
                            const char* passphrase = nullptr);

/**
 * @brief Destruct and free a tls context.
 *
 * @param ctx
 */
void delete_tls_context(TLSContext* ctx);

/**
 * @brief Create socket stream on TLS.
 *
 * @param ctx TLS context. Context lifetime is inrelevant to Stream, user should
 *            keep it accessable during whole life time
 * @param base base socket, as underlay socket using for data transport
 * @param role should act as client or server during TLS handshake
 * @param ownership if new socket stream owns base socket.
 * @return net::ISocketStream*
 */
ISocketStream* new_tls_stream(TLSContext* ctx, net::ISocketStream* base,
                                   SecurityRole role, bool ownership = false);
/**
 * @brief Create socket server on TLS. as a client socket factory.
 *
 * @param ctx TLS context. Context lifetime is inrelevant to Stream, user should
 *            keep it accessable during whole life time.
 * @param base base socket, as underlay socket using for data transport.
 * @param ownership if new socket stream owns base socket.
 * @return net::ISocketServer* server factory
 */
ISocketServer* new_tls_server(TLSContext* ctx, net::ISocketServer* base,
                                   bool ownership = false);

/**
 * @brief Create socket client on TLS. as a client socket factory.
 *
 * @param ctx TLS context. Context lifetime is inrelevant to Stream, user should
 *            keep it accessable during whole life time.
 * @param base base socket, as underlay socket using for data transport.
 * @param ownership if new socket stream owns base socket.
 * @return net::ISocketClient* client factory
 */
ISocketClient* new_tls_client(TLSContext* ctx, net::ISocketClient* base,
                                   bool ownership = false);

}
}
