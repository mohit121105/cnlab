
#include <stdio.h>

#define MAX_TOKENS 10
#define TOKEN_GEN_RATE 2

int main() {

    int packet_demands[] = {2, 7, 1, 0, 9};
    int current_tokens = 0;

    int num_seconds = sizeof(packet_demands) /
                      sizeof(packet_demands[0]);

    printf("--- Token Bucket Simulation ---\n");

    printf("Max Tokens: %d, Token Generation Rate: %d/sec\n\n",
           MAX_TOKENS, TOKEN_GEN_RATE);

    for (int i = 0; i < num_seconds; i++) {

        int incoming_demands = packet_demands[i];

        printf("Second %d: Packets trying to transmit = %d\n",
               i + 1, incoming_demands);

        current_tokens += TOKEN_GEN_RATE;

        if (current_tokens > MAX_TOKENS) {
            current_tokens = MAX_TOKENS;
        }

        printf("  [+] Generated tokens. Current token count: %d\n",
               current_tokens);

        if (incoming_demands <= current_tokens) {

            current_tokens -= incoming_demands;

            printf("  [v] Success: Transmitted all %d packets.\n",
                   incoming_demands);

        } else {

            int transmitted = current_tokens;
            int dropped = incoming_demands - transmitted;

            current_tokens = 0;

            printf("  [!] Insufficient tokens! Transmitted a burst of %d. Dropped: %d\n",
                   transmitted, dropped);
        }

        printf("  Tokens left for next cycle: %d\n\n",
               current_tokens);
    }

    return 0;
}
