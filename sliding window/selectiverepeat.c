
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 50

void sender(int frames[], int size, int window_size);
void receiver(int frames[], int start, int window_size, int size);

int main() {
    int n, window_size;
    int frames[MAX_FRAMES];

    printf("Selective Repeat Sliding Window Protocol\n");

    printf("Enter number of frames (max %d): ", MAX_FRAMES);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_FRAMES) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    printf("Enter window size: ");
    scanf("%d", &window_size);

    if (window_size <= 0 || window_size > n) {
        printf("Invalid window size.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        frames[i] = i;
    }

    sender(frames, n, window_size);

    return 0;
}

void sender(int frames[], int size, int window_size) {
    int base = 0;
    char choice;
    int ack[MAX_FRAMES] = {0};

    while (base < size) {

        printf("\nSender window: ");

        for (int i = base; i < base + window_size && i < size; i++) {
            printf("[%d] ", frames[i]);
        }

        printf("\nSending frames...\n");

        for (int i = base; i < base + window_size && i < size; i++) {
            if (!ack[i]) {
                printf("Sent frame: %d\n", frames[i]);
            }
        }

        receiver(frames, base, window_size, size);

        printf("\nEnter ACK status for each frame (1=Received, 0=Lost):\n");

        for (int i = base; i < base + window_size && i < size; i++) {
            if (!ack[i]) {
                printf("Frame %d ACK: ", frames[i]);
                scanf(" %c", &choice);

                if (choice == '1') {
                    ack[i] = 1;
                }
            }
        }

        // Slide window over consecutively acknowledged frames
        while (base < size && ack[base]) {
            base++;
        }

        // Retransmit only unacknowledged frames
        printf("\nUnacknowledged frames will be retransmitted.\n");
    }

    printf("\nAll frames sent successfully!\n");
}

void receiver(int frames[], int start, int window_size, int size) {
    printf("\nReceiver is ready to receive frames.\n");

    for (int i = start; i < start + window_size && i < size; i++) {
        printf("Receiver expects frame: %d\n", frames[i]);
    }
}
