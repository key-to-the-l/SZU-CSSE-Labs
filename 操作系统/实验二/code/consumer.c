#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include "shm_com_sem.h"

void consume_data(struct shared_mem_st* shared_stuff, sem_t* sem_queue, sem_t* sem_queue_empty, sem_t* sem_queue_full) {
    while (1) {
        // 等待有数据
        sem_wait(sem_queue_full);
        sem_wait(sem_queue);

        // 读取数据
        printf("[PID: %d] Read: %s\n", getpid(), shared_stuff->buffer[shared_stuff->line_read]);

        // 退出条件
        if (strcmp(shared_stuff->buffer[shared_stuff->line_read], "quit") == 0) {
            sem_post(sem_queue);
            sem_post(sem_queue_full);
            break;
        }

        // 清空当前行
        memset(shared_stuff->buffer[shared_stuff->line_read], 0, LINE_SIZE);
        shared_stuff->line_read = (shared_stuff->line_read + 1) % NUM_LINES;

        // 释放互斥锁 & 增加可用空缓冲区数
        sem_post(sem_queue);
        sem_post(sem_queue_empty);

        // 模拟延迟
        sleep(1);
    }
}

int main() {
    int shmid;
    void* shared_memory = NULL;
    struct shared_mem_st* shared_stuff;
    sem_t* sem_queue, * sem_queue_empty, * sem_queue_full;

    // 获取共享内存
    shmid = shmget((key_t)1234, sizeof(struct shared_mem_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    shared_stuff = (struct shared_mem_st*)shared_memory;

    // 获取信号量
    sem_queue = sem_open(queue_mutex, 0);
    sem_queue_empty = sem_open(queue_empty, 0);
    sem_queue_full = sem_open(queue_full, 0);

    pid_t fork_result = fork();

    if (fork_result == -1) {
        fprintf(stderr, "Fork failure\n");
        exit(EXIT_FAILURE);
    }

    if (fork_result == 0) {
        consume_data(shared_stuff, sem_queue, sem_queue_empty, sem_queue_full);
    }