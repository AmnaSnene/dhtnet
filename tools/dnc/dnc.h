/*
 *  Copyright (C) 2004-2023 Savoir-faire Linux Inc.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "connectionmanager.h"
#include "multiplexed_socket.h"
#include "ice_transport_factory.h"
#include "certstore.h"

#include <asio.hpp>

namespace dhtnet {
/**
 * Attempt to retrieve the identity from the .ssh directory, and if none is found, generate a new
 * certification.
 * @return dht::crypto::Identity
 */

class Dnc
{
public:
    // Build a server
    Dnc(dht::crypto::Identity identity,
        const std::string& bootstrap_ip_add,
        const std::string& bootstrap_port);
    // Build a client
    Dnc(dht::crypto::Identity identity,
        const std::string& bootstrap_ip_add,
        const std::string& bootstrap_port,
        dht::InfoHash peer_id,
        int port,
        const std::string& ip_add);
    ~Dnc();
    void run();

private:
    std::unique_ptr<ConnectionManager> connectionManager;
    std::shared_ptr<Logger> logger;
    tls::CertificateStore certStore;
    IceTransportFactory iceFactory;
    std::shared_ptr<asio::io_context> ioContext;
    std::thread ioContextRunner;

    std::shared_ptr<asio::posix::stream_descriptor> stdinDescriptor;

    std::pair<std::string, std::string> parseName(const std::string_view name);
};

} // namespace dhtnet