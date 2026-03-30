CC = gcc

CFLAGS = -O3 -march=native -Wall -I./headers

SRC_DIR = sources
RUN_DIR = runnables
BIN_DIR = .

COMMON_SRCS = $(SRC_DIR)/sqmatrix.c $(SRC_DIR)/benchmark.c
LOCKS_SRC   = $(SRC_DIR)/locks.c

TARGET_SP    = sp_mmult
TARGET_PIPE  = ipc_pipe
TARGET_SHMEM = ipc_shmem

all: $(TARGET_SP) $(TARGET_PIPE) $(TARGET_SHMEM)

$(TARGET_SP): $(RUN_DIR)/sp_mmult.c $(COMMON_SRCS)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

$(TARGET_PIPE): $(RUN_DIR)/ipc-pipe.c $(COMMON_SRCS) $(LOCKS_SRC)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

$(TARGET_SHMEM): $(RUN_DIR)/ipc-shmem.c $(COMMON_SRCS) $(LOCKS_SRC)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

clean:
	rm -f $(TARGET_SP) $(TARGET_PIPE) $(TARGET_SHMEM)

help:
	@echo "Available commands:"
	@echo "  make         - Build ipc_pipe, ipc_shmem, and sp_mmult programs"
	@echo "  make clean   - Delete ipc_pipe, ipc_shmem, and sp_mmult programs"
	@echo "  make help    - Show commands to use"