#ifndef SHM_COM_SEM_H
#define SHM_COM_SEM_H

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define LINE_SIZE 256   
#define NUM_LINES 16     

// POSIX 信号量名称
const char* queue_mutex = "/queue_mutex";   // 互斥信号量，控制缓冲区访问
const char* queue_empty = "/queue_empty";   // 表示可用的空缓冲区数量
const char* queue_full = "/queue_full";    // 表示已填充的数据块数量

// 共享内存结构
struct shared_mem_st {
    char buffer[NUM_LINES][LINE_SIZE];
    int line_write;  // 生产者写入位置
    int line_read;   // 消费者读取位置
};

#endif