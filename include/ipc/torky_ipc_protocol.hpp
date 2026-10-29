#ifndef TORKY_IPC_PROTOCOL_HPP
#define TORKY_IPC_PROTOCOL_HPP

#include "torky_continuum_core.hpp"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <atomic>

namespace torky::ipc {

constexpr const char* SHM_RING_NAME = "/torky_continuum_shm_ring";
constexpr size_t RING_CAPACITY = 1048576; // 1M 9-byte cells (~9 MiB)
constexpr uint16_t IPC_DEFAULT_PORT = 8080;

#pragma pack(push, 1)
struct ShmRingBuffer {
    std::atomic<uint64_t> write_head{0};
    std::atomic<uint64_t> read_tail{0};
    uint64_t capacity{RING_CAPACITY};
    torky::continuum::TORKY_CELL_DTYPE cells[RING_CAPACITY];
};
#pragma pack(pop)

} // namespace torky::ipc
#endif // TORKY_IPC_PROTOCOL_HPP
