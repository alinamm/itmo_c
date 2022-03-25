#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bio {
    char surname[21];
    char name[21];
    char patronym[21];
    long long number;
};

long long partition(struct bio *arr, long long left, long long right) {
    long long i = left;
    long long j = right;
    struct bio x = arr[(left + right) / 2];

    while (i <= j) {
        while ((strcmp(arr[i].surname, x.surname) < 0
                || strcmp(arr[i].name, x.name) < 0 && strcmp(arr[i].surname, x.surname) == 0
                || strcmp(arr[i].surname, x.surname) == 0 && strcmp(arr[i].name, x.name) == 0 &&
                   strcmp(arr[i].patronym, x.patronym) < 0
                || strcmp(arr[i].surname, x.surname) == 0 && strcmp(arr[i].name, x.name) == 0 &&
                   strcmp(arr[i].patronym, x.patronym) == 0 && arr[i].number < x.number))
            i++;
        while ((strcmp(arr[j].surname, x.surname) > 0
                || strcmp(arr[j].name, x.name) > 0 && strcmp(arr[j].surname, x.surname) == 0
                || strcmp(arr[j].surname, x.surname) == 0 && strcmp(arr[j].name, x.name) == 0 &&
                   strcmp(arr[j].patronym, x.patronym) > 0
                || strcmp(arr[j].surname, x.surname) == 0 && strcmp(arr[j].name, x.name) == 0 &&
                   strcmp(arr[j].patronym, x.patronym) == 0 && arr[j].number > x.number))
            j--;

        if (i >= j) {
            break;
        }
        struct bio p;
        p = arr[i];
        arr[i] = arr[j];
        arr[j] = p;
        i++;
        j--;
    }
    return j;
}

void sort(struct bio *arr, long long left, long long right) {
    while (left < right) {
        long long s = partition(arr, left, right);
        long long t = left;
        left = s + 1;
        sort(arr, t, s);
    }
}


int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "you have to enter only the names of input and output files");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "can not open file");
        fclose(in);
        return 1;
    }


    struct bio *people = malloc(50 * 1 * sizeof(struct bio));
    if (people == NULL) {
        fprintf(stderr, "failed to allocate memory");
        fclose(in);
        return 2;
    }
    long long size = 50;

    long long r = 0;
    while (!feof(in)) {
        if (r + 1 == size) {
            int w = 1;
            long long h;
            people = realloc(people, 2 * size * sizeof(struct bio));
            while (people == NULL) {
                h = size + size / (2 * w);
                people = realloc(people, h * 1 * sizeof(struct bio));
                w++;
            }
            if (h <= size && h != 0) {
                fprintf(stderr, "failed to allocate memory");
                fclose(in);
                free(people);
                return 2;
            } else {
                size = h;
            }
        }
        int x;
        x = fscanf(in, "%s%s%s%lld", &people[r].surname, &people[r].name, &people[r].patronym, &people[r].number);
        if (x != 4) {
            r--;
        }
        r++;
    }
    fclose(in);
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "can not open file");
        fclose(out);
        free(people);
        return 1;
    }
    sort(people, 0, r - 1);
    for (long long i = 0; i < r; i++) {
        fprintf(out, "%s %s %s %lld\n", people[i].surname, people[i].name, people[i].patronym, people[i].number);
    }
    fclose(out);
    free(people);
    return 0;
}