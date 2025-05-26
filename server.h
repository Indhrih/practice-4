#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 5

// Структура для передачи данных в поток
typedef struct {
    int thread_num;     // Номер потока
    int sleep_time;     // Время работы потока (в секундах)
} thread_data_t;

// Функция, выполняемая в потоке
void* thread_function(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    
    printf("%d-й поток начал работу\n", data->thread_num);
    
    // Имитация работы потока (ожидание)
    sleep(data->sleep_time);
    
    printf("%d-й поток выполнил задачу\n", data->thread_num);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int i, ret;
    char choice;
    
    do {
        // Запрос времени работы для каждого потока
        for (i = 0; i < NUM_THREADS; i++) {
            printf("Введите время работы для %d-го потока (в секундах): ", i + 1);
            scanf("%d", &thread_data[i].sleep_time);
            thread_data[i].thread_num = i + 1;
        }
        
        // Создание потоков
        for (i = 0; i < NUM_THREADS; i++) {
            ret = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_data[i]);
            if (ret != 0) {
                fprintf(stderr, "Ошибка при создании потока %d: %s\n", i + 1, strerror(ret));
                exit(EXIT_FAILURE);
            }
        }
        
        // Ожидание завершения всех потоков
        for (i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        
        // Запрос действия у пользователя
        printf("Нажмите 'x', чтобы выйти, или 'r', чтобы перезапустить: ");
        scanf(" %c", &choice);
        
    } while (choice == 'r' || choice == 'R');
    
    return 0;
}
