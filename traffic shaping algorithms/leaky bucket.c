
#include <stdio.h>
#include <unistd.h>

#define BUCKET_CAPACITY 10
#define LEAK_RATE 3

int main() {

    int incoming_packets[] = {4, 8, 2, 0, 6};
    int current_bucket_size = 0;

    int num_seconds = sizeof(incoming_packets) /
                      sizeof(incoming_packets[0]);

    printf("--- Leaky Bucket Simulation ---\n");
    printf("Bucket Capacity: %d, Leak Rate: %d\n\n",
           BUCKET_CAPACITY, LEAK_RATE);

    for (int i = 0; i < num_seconds; i++) {

        int incoming = incoming_packets[i];

        printf("Second %d: Incoming packets = %d\n",
               i + 1, incoming);

        if (incoming + current_bucket_size > BUCKET_CAPACITY) {

            int accepted = BUCKET_CAPACITY - current_bucket_size;
            int dropped = incoming - accepted;

            current_bucket_size = BUCKET_CAPACITY;

            printf("  [!] Bucket overflow! Accepted: %d, Dropped: %d\n",
                   accepted, dropped);

        } else {

            current_bucket_size += incoming;

            printf("  [+] Accepted all %d packets.\n", incoming);
        }

        printf("  Current buffer status: %d / %d\n",
               current_bucket_size, BUCKET_CAPACITY);

        if (current_bucket_size >= LEAK_RATE) {
            current_bucket_size -= LEAK_RATE;
            printf("  [-] Leaked %d packets. Buffer remaining: %d\n\n",
                   LEAK_RATE, current_bucket_size);
        } else {
            printf("  [-] Leaked %d packets. Buffer remaining: 0\n\n",
                   current_bucket_size);
            current_bucket_size = 0;
        }
    }

    while (current_bucket_size > 0) {

        int leaked;

        if (current_bucket_size >= LEAK_RATE) {
            leaked = LEAK_RATE;
        } else {
            leaked = current_bucket_size;
        }

        current_bucket_size -= leaked;

        printf("After Stream: Leaked %d packets. Buffer remaining: %d\n",
               leaked, current_bucket_size);
    }

    return 0;
}
