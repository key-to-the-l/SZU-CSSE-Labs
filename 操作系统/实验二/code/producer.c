#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include "shm_com_sem.h"

int main() {
    int shmid;
    void* shared_memory = NULL;
    struct shared_mem_st* shared_stuff;
    sem_t* sem_queue, * sem_queue_empty, * sem_queue_full;

    // 创建共享内存
    shmid = shmget((key_t)1234, sizeof(struct shared_mem_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // 挂载共享内存
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    shared_stuff = (struct shared_mem_st*)shared_memory;
    shared_stuff->line_write = 0;
    shared_stuff->line_read = 0;

    // 创建信号量
    sem_queue = sem_open(queue_mutex, O_CREAT, 0644, 1);
    sem_queue_empty = sem_open(queue_empty, O_CREAT, 0644, NUM_LINES);
    sem_queue_full = sem_open(queue_full, O_CREAT, 0644, 0);

    char key_line[LINE_SIZE];

    while (1) {
        printf("Enter your text ('quit' to exit): ");
        fgets(key_line, LINE_SIZE, stdin);
        key_line[strcspn(key_line, "\n")] = 0; // 去掉换行符

        // 退出条件
        if (strcmp(key_line, "quit") == 0) {
            break;
        }

        // 等待空缓冲区
        sem_wait(sem_queue_empty);
        sem_wait(sem_queue);

        // 写入数据
        strcpy(shared_stuff->buffer[shared_stuff->line_write], key_line);
        shared_stuff->line_write = (shared_stuff->line_write + 1) % NUM_LINES;

        // 释放互斥锁 & 增加可用数据块数
        sem_post(sem_queue);
        sem_post(sem_queue_full);
    }

    // 清理
    sem_close(sem_queue);
    sem_close(sem_queue_empty);
    sem_close(sem_queue_full);
    sem_unlink(queue_mutex);
    sem_unlink(queue_empty);
    sem_unlink(queue_full);

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}