#define LED 0x10012000  // Example GPIO address

void delay() {
    for (volatile int i = 0; i < 1000000; i++);
}

int main() {
    volatile int *led = (int *)LED;

    while (1) {
        *led = 1;  // Turn LED on
        delay();
        *led = 0;  // Turn LED off
        delay();
    }

    return 0;
}
