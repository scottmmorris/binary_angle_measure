#include "bam.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool compareAngles(char* name, double a, double b) {
    if (a != b) {
        printf("%s ERROR: Expected %f to equal %f\n", name, a, b);
        return false;
    }
    printf("%s SUCCESS\n", name);
    return true;
}

double addAngles(double a1, double a2) {
    double res = a1 + a2;
    while (res < 0) {
        res += 360;
    }
    while (res >= 360) {
        res -= 360;
    }
    return res;
}

int main(int argc, char *argv[]) {

    uint16_t test = 0b1000000000000000;
    double angle = ConvertFromBAM(test);
    printf("%f\n", angle);

    uint16_t bam = ConvertToBAM(180);
    printf("%d and %d\n", bam, test);

    // TEST: Conversions to and from binary angle measure system
    printf("\nTEST: From BAMS Conversions\n");

    compareAngles("TEST 1", ConvertFromBAM(0b1000000000000000), 180);
    compareAngles("TEST 2", ConvertFromBAM(0b1000000000000001), 180 + 0.00549316406);
    compareAngles("TEST 3", ConvertFromBAM(0b0111111111111111), 180 - 0.00549316406);
    compareAngles("TEST 4", ConvertFromBAM(0b0000000000000000), 0);
    compareAngles("TEST 5", ConvertFromBAM(0b0000000000000001), 0.00549316406);
    compareAngles("TEST 6", ConvertFromBAM(0b0000000000000010), 0.01098632813);
    compareAngles("TEST 7", ConvertFromBAM(0b0000000000000100), 0.02197265625);
    compareAngles("TEST 8", ConvertFromBAM(0b0000000000001000), 0.0439453125);
    compareAngles("TEST 9", ConvertFromBAM(0b0000000000010000), 0.087890625);
    compareAngles("TEST 10", ConvertFromBAM(0b0000000000100000), 0.17578125);
    compareAngles("TEST 11", ConvertFromBAM(0b0000000001000000), 0.3515625);
    compareAngles("TEST 12", ConvertFromBAM(0b0000000010000000), 0.703125);
    compareAngles("TEST 13", ConvertFromBAM(0b0000000100000000), 1.40625);
    compareAngles("TEST 14", ConvertFromBAM(0b0000001000000000), 2.8125);
    compareAngles("TEST 15", ConvertFromBAM(0b0000010000000000), 5.625);
    compareAngles("TEST 16", ConvertFromBAM(0b0000100000000000), 11.25);
    compareAngles("TEST 17", ConvertFromBAM(0b0001000000000000), 22.5);
    compareAngles("TEST 18", ConvertFromBAM(0b0010000000000000), 45);
    compareAngles("TEST 19", ConvertFromBAM(0b0100000000000000), 90);
    compareAngles("TEST 20", ConvertFromBAM(0b1111111111111111), 360 - 0.00549316406);

    printf("\nTEST: To BAMS Conversions\n");

    compareAngles("TEST 1", ConvertToBAM(180), 0b1000000000000000);
    compareAngles("TEST 2", ConvertToBAM(180 + 0.00549316406), 0b1000000000000001);
    compareAngles("TEST 3", ConvertToBAM(180 - 0.00549316406), 0b0111111111111111);
    compareAngles("TEST 4", ConvertToBAM(0), 0b0000000000000000);
    compareAngles("TEST 5", ConvertToBAM(0.00549316406), 0b0000000000000001);
    compareAngles("TEST 6", ConvertToBAM(0.01098632813), 0b0000000000000010);
    compareAngles("TEST 7", ConvertToBAM(0.02197265625), 0b0000000000000100);
    compareAngles("TEST 8", ConvertToBAM(0.0439453125), 0b0000000000001000);
    compareAngles("TEST 9", ConvertToBAM(0.087890625), 0b0000000000010000);
    compareAngles("TEST 10", ConvertToBAM(0.17578125), 0b0000000000100000);
    compareAngles("TEST 11", ConvertToBAM(0.3515625), 0b0000000001000000);
    compareAngles("TEST 12", ConvertToBAM(0.703125), 0b0000000010000000);
    compareAngles("TEST 13", ConvertToBAM(1.40625), 0b0000000100000000);
    compareAngles("TEST 14", ConvertToBAM(2.8125), 0b0000001000000000);
    compareAngles("TEST 15", ConvertToBAM(5.625), 0b0000010000000000);
    compareAngles("TEST 16", ConvertToBAM(11.25), 0b0000100000000000);
    compareAngles("TEST 17", ConvertToBAM(22.5), 0b0001000000000000);
    compareAngles("TEST 18", ConvertToBAM(45), 0b0010000000000000);
    compareAngles("TEST 19", ConvertToBAM(90), 0b0100000000000000);
    compareAngles("TEST 20", ConvertToBAM(360 - 0.00549316406), 0b1111111111111111);

    uint16_t angle_1, angle_2, angle_res;
    printf("\nTEST: BAMS Operations\n");
    angle_1 = 0b1111111111111111;
    angle_2 = 0b0000000000000001;
    time_t benchStart = clock();
    angle_res = angle_1 + angle_2;
    time_t benchStop = clock();
    compareAngles("TEST 1", angle_res, 0b0000000000000000);
    printf("TEST 1 BAMS took %ld ticks\n", (benchStop - benchStart));
    benchStart = clock();
    addAngles(360 - 0.00549316406, 0.00549316406);
    benchStop = clock();
    printf("TEST 1 Non BAMS took %ld ticks\n", (benchStop - benchStart));

    angle_1 = 0b1111111111110111;
    angle_2 = 0b0000000000001011;
    benchStart = clock();
    angle_res = angle_1 + angle_2;
    benchStop = clock();
    compareAngles("TEST 2", angle_res, 0b0000000000000010);
    printf("TEST 2 BAMS took %ld ticks\n", (benchStop - benchStart));
    benchStart = clock();
    addAngles(360 - 0.00549316406, 0.00549316406 + 0.01098632813 + 0.0439453125);
    benchStop = clock();
    printf("TEST 2 Non BAMS took %ld ticks\n", (benchStop - benchStart));

    angle_1 = 0b1111111111111111;
    angle_2 = 0b1111111111111111;
    benchStart = clock();
    angle_res = angle_1 + angle_2;
    benchStop = clock();
    compareAngles("TEST 3", angle_res, 0b1111111111111110);
    printf("TEST 3 BAMS took %ld ticks\n", (benchStop - benchStart));
    benchStart = clock();
    addAngles(360 - 0.00549316406, 360 - 0.00549316406);
    benchStop = clock();
    printf("TEST 3 Non BAMS took %ld ticks\n", (benchStop - benchStart));

    angle_1 = 0b0000000000000001;
    angle_2 = 0b1111111111111111;
    benchStart = clock();
    angle_res = angle_1 - angle_2;
    benchStop = clock();
    compareAngles("TEST 4", angle_res, 0b0000000000000010);
    printf("TEST 4 BAMS took %ld ticks\n", (benchStop - benchStart));
    benchStart = clock();
    addAngles(0.00549316406, - 360 + 0.00549316406);
    benchStop = clock();
    printf("TEST 4 Non BAMS took %ld ticks\n", (benchStop - benchStart));

}