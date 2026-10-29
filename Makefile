CXX ?= g++
CXXFLAGS = -O3 -std=c++20 -march=native -Wall -Wextra -Iinclude -pthread

TARGET = build/torky-ipc-daemon
SERVER_BIN = build/torky_ipc_server
CLIENT_BIN = build/torky_ipc_client

all: $(TARGET) $(SERVER_BIN) $(CLIENT_BIN)

$(TARGET): src/torky_cli_kernel.cpp include/torky_continuum_core.hpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) src/torky_cli_kernel.cpp -o $(TARGET)

$(SERVER_BIN): src/server/torky_ipc_server.cpp include/ipc/torky_ipc_protocol.hpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude/ipc src/server/torky_ipc_server.cpp -o $(SERVER_BIN)

$(CLIENT_BIN): src/client/torky_ipc_client.cpp include/ipc/torky_ipc_protocol.hpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude/ipc src/client/torky_ipc_client.cpp -o $(CLIENT_BIN)

test: all
	./$(TARGET)
	./$(SERVER_BIN) 8080
	./$(CLIENT_BIN)
	./run_audit.sh

clean:
	rm -rf build local_verification_certificate.json
