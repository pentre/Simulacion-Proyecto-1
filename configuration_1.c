#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int readSeed() {
    printf( "Enter a seed, if the input is 0 the current time will be used as seed\nSeed: ");
    int seed;
    int result = scanf("%u", &seed);

    if (result == EOF) {
        printf("Seed should be an integer more or equal to 0\n");
        return -1;
    }

    if (seed < 0) {
        printf("Seed should be an integer more or equal to 0\n");
        return -1;
    }

    if (seed == 0) {
        srand(time(NULL));
    } else {
        srand(1);
    }

   return 0;
}

int waitCall() {
    double r = (rand()/(double)RAND_MAX);

    if (r < 0.25) {
        return 1;
    }

    if (r < 0.65) {
        return 2;
    }

    if (r < 0.85) {
        return 3;
    }

    return 4;
}

int attendAsAbel() {
    double r = (rand()/(double)RAND_MAX);

    if (r < 0.25) {
        return 0;
    }

    if (r < 0.65) {
        return 1;
    }

    if (r < 0.85) {
        return 2;
    }

    return 3;
}

int attendAsBaker() {
    double r = (rand()/(double)RAND_MAX);

    if (r < 0.25) {
        return 0;
    }

    if (r < 0.65) {
        return 1;
    }

    if (r < 0.85) {
        return 2;
    }

    return 3;
}

int main() {
    int err = readSeed();
    if (err != 0) {
        return 0;
    }

    int abelCalls[4] = {0, 0, 0, 0};
    int abelTimes[4] = {2, 3, 4, 5};
    int bakerCalls[4] = {0, 0, 0, 0};
    int bakerTimes[4] = {3, 4, 5, 6};

    int currentTime = 0;

    int arrivalTime[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    int attendTime[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    int waitTime[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    int abelAttendingTime = 0;
    int bakerAttendingTime = 0;
    int currentAttendingTime = 0;

    int abelTotalAttendingTime = 0;
    int bakerTotalAttendingTime = 0;

    int abelTotalCalls = 0;
    int bakerTotalCalls = 0;

    int abelCurrentAttendant = 0;
    int bakerCurrentAttendant = 0;

    int pendingTimeToCall = waitCall();
    int queue = 0;

    for (int currentCall = 0, nextAttendant = 1; currentCall <= 100 || nextAttendant <= 100;) {
        if (currentCall <= 100 && pendingTimeToCall == 0) {
            arrivalTime[currentCall] = currentTime;
            ++currentCall;
            pendingTimeToCall = waitCall();
            ++queue;
        }

        if (nextAttendant <= 100 && abelAttendingTime == 0 && queue > 0) {
            int r = attendAsAbel();
            ++abelCalls[r];
            abelAttendingTime = abelTimes[r];

            abelCurrentAttendant = nextAttendant;
            attendTime[abelCurrentAttendant] = abelTimes[r];

            ++nextAttendant;
            ++abelTotalCalls;
            --queue;
            abelTotalAttendingTime += abelTimes[r];
        } else {
            if (nextAttendant <= 100 && bakerAttendingTime == 0 && queue > 0) {
                int r = attendAsAbel();
                ++bakerCalls[r];
                bakerAttendingTime = bakerTimes[r];

                bakerCurrentAttendant = nextAttendant;
                attendTime[bakerCurrentAttendant] = bakerTimes[r];

                ++nextAttendant;
                ++bakerTotalCalls;
                --queue;
                bakerTotalAttendingTime += bakerTimes[r];
            }
        }

        if (abelAttendingTime > 0) {
            --abelAttendingTime;
        }

        if (bakerAttendingTime > 0) {
            --bakerAttendingTime;
        }

        --pendingTimeToCall;
        ++currentTime;

        for (int i = nextAttendant; i < currentCall; ++i) {
            if (i <= 100) {
                ++waitTime[i];
            }
        }
    }

    // Print abel results
    printf("\nAbel results:\n");

    for (int i = 0; i < 4; ++i) {
        printf("  Calls that lasted %d minutes: %d\n", abelTimes[i], abelCalls[i]);
    }

    double average = (abelCalls[0]*abelTimes[0] + abelCalls[1]*abelTimes[1] + abelCalls[2]*abelTimes[2] + abelCalls[3]*abelTimes[3]) / (double)abelTotalCalls;
    printf("  Average call duration: %.2f minutes\n", average);

    printf("  Total calls attended: %d\n", abelTotalCalls);
    printf("  Total busy time: %d minutes\n", abelTotalAttendingTime);
    printf("  Busy time percentage: %2.f%%\n", (abelTotalAttendingTime/(double)currentTime)*100.0);

    // Print baker results
    printf("\nBaker results:\n");

    for (int i = 0; i < 4; ++i) {
        printf("  Calls that lasted %d minutes: %d\n", bakerTimes[i], bakerCalls[i]);
    }

    average = (bakerCalls[0]*bakerTimes[0] + bakerCalls[1]*bakerTimes[1] + bakerCalls[2]*bakerTimes[2] + bakerCalls[3]*bakerTimes[3]) / (double)bakerTotalCalls;
    printf("  Average call duration: %.2f minutes\n", average);

    printf("  Total calls attended: %d\n", bakerTotalCalls);
    printf("  Total busy time: %d minutes\n", bakerTotalAttendingTime);
    printf("  Busy time percentage: %2.f%%\n", (bakerTotalAttendingTime/(double)currentTime)*100.0);

    // Print general results
    printf("\nTotal duration of the simulation: %d minutes\n", currentTime);

    int waitedAttendants = 0;
    int waitedTime = 0;
    for (int i = 0; i < 100; ++i) {
        if (waitTime[i] > 0) {
            ++waitedAttendants;
            waitedTime += waitTime[i];
        }
    }

    printf("Total attendands that had to wait: %d\n", waitedAttendants);
    printf("Total time waited from attendants: %d minutes\n", waitedTime);
    printf("Average time waited per attendant: %.2f minutes\n", (double)waitedTime/(double)waitedAttendants);
}
