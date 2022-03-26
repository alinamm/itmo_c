#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "you have to enter only the names of input and output files");
        return 1;
    }
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "can not open file");
        fclose(in);
        return 1;
    }
    int n = 0;
    fscanf(in, "%d", &n);
    float* a = malloc(n * n * sizeof(float));
    if (a == NULL) {
        fprintf(stderr, "failed to allocate memory");
        fclose(in);
        return 2;

    }
    float* b = malloc(n * 1 * sizeof(float));
    if (b == NULL) {
        fprintf(stderr, "failed to allocate memory");
        fclose(in);
        free(a);
        return 2;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(in, "%g", &a[i * n + j]);
        }
        fscanf(in, "%g", &b[i]);
    }
    fclose(in);
    for (int k = 0; k < n - 1; k++) {
        if (a[k * n + k] == 0) {
            for (int l = k + 1; l < n; l++) {
                if (a[l * n + k] != 0) {
                    for (int r = 0; r < n; r++) {
                        float p;
                        p = a[l * n + r];
                        a[l * n + r] = a[k * n + r];
                        a[k * n + r] = p;
                    }
                    float p;
                    p = b[k];
                    b[k] = b[l];
                    b[l] = p;
                    break;
                }
            }
        }
        for (int i = k + 1; i < n; i++) {
            double y = a[i * n + k] / a[k * n + k];
            for (int j = k; j < n; j++) {
                if (a[k * n + k] != 0) {
                    a[i * n + j] = a[i * n + j] - a[k * n + j] * y;
                }
            }
            if (a[k * n + k] != 0) {
                b[i] = b[i] - b[k] * y;
            }
        }
    }
    int ns = 0;
    int ms = 0;
    for (int i = 0; i < n - 1; i++) {
        int k1 = 0;
        int k2 = 0;
        for (int j = 0; j < n; j++) {
            if (a[i * n + j] == 0) {
                k1++;
            }
            if (a[(i + 1) * n + j] == 0) {
                k2++;
            }
        }

        if (k1 == k2) {
            float y = a[(i + 1) * n + k2] / a[i * n + k2];
            for (int j = k2; j < n; j++) {
                a[(i + 1) * n + j] -= a[i * n + j] * y;
            }
            b[i + 1] -= b[i] * y;
            for (int j = 0; j < n; j++) {
                if (a[(i + 1) * n + j] != 0 || b[i + 1] != 0) {
                    ns = 1;
                }
                else {
                    ms = 1;
                }
            }
            for (int j = k2; j < n; j++) {
                a[(i + 1) * n + j] += a[i * n + j] * y;
            }
            b[i + 1] += b[i] * y;
        }
    }
    int ind1 = 0;
    int ind2 = 0;
    for (int i = 0; i < n; i++) {
        int ind = 0;
        for (int j = 0; j < n; j++) {
            if (a[i * n + j] != 0) {
                ind = 1;
            }
        }
        if (ind == 0) {
            if (b[i] == 0) {
                ind1 = 1;
            }
            else {
                ind2 = 1;
            }
            break;
        }
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "can not open file");
        fclose(out);
        free(a);
        free(b);
        return 1;
    }
    float* x = malloc(n * 1 * sizeof(float));
    if (x == NULL) {
        fprintf(stderr, "failed to allocate memory");
        fclose(out);
        free(a);
        free(b);
        return 2;
    }
    if (ind2 != 0 || ns != 0) {
        fprintf(out, "no solutions");
    }
    else  if (ind1 != 0 || ms != 0) {
        fprintf(out, "many solutions");
    }
    else {
        for (int k = n - 1; k >= 0; k--) {
            float s = 0;
            for (int j = k + 1; j < n; j++)
                s = s + a[k * n + j] * x[j];
            x[k] = (b[k] - s) / a[k * n + k];
        }
        for (int i = 0; i < n; i++) {
            fprintf(out, "%g\n", x[i]);
        }
    }
    fclose(out);
    free(a);
    free(b);
    free(x);
    return 0;
}