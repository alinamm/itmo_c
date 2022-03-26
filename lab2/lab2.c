#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "you have to enter only the names of input and output files");
        return 1;
    }
    FILE *in = fopen(argv[1], "rb");
    if (in == NULL) {
        fprintf(stderr, "can not open file");
        fclose(in);
        return 1;
    }
    unsigned char a, b, c, d;

    fread(&a, sizeof(char), 1, in);
    fread(&b, sizeof(char), 1, in);
    fread(&c, sizeof(char), 1, in);
    fread(&d, sizeof(char), 1, in);

    FILE *out = fopen(argv[2], "wb");
    if (out == NULL) {
        fprintf(stderr, "can not open file");
        fclose(out);
        return 1;
    }

    if (a == 0xEF && b == 0xBB && c == 0xFB) {
        if (atoi(argv[3]) == 1 || atoi(argv[3]) == 2) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 0) {
            unsigned char next;
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
    } else if (a == 0xFE && b == 0xFF) {
        if (atoi(argv[3]) == 3) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 2) {
            unsigned char next1, next2;
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next1 = fgetc(in);
                next2 = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next2, sizeof(char), 1, out);
                    fwrite(&next1, sizeof(char), 1, out);
                }
            }
        }
    } else if (a == 0xFF && b == 0xFE && c == 0x00 && d == 0x00) {
        if (atoi(argv[3]) == 4) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 5) {
            unsigned char next1, next2, next3, next4;
            fwrite(&d, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&a, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next1 = fgetc(in);
                next2 = fgetc(in);
                next3 = fgetc(in);
                next4 = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next4, sizeof(char), 1, out);
                    fwrite(&next3, sizeof(char), 1, out);
                    fwrite(&next2, sizeof(char), 1, out);
                    fwrite(&next1, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 0) {
            unsigned char next;
            for (int i = 0; i < 10000000; i++) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    if (i % 4 == 0) {
                        fwrite(&next, sizeof(char), 1, out);
                    }
                } else {
                    break;
                }
            }
        }
    } else if (a == 0x00 && b == 0x00 && c == 0xFE && d == 0xFF) {
        if (atoi(argv[3]) == 5) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 0) {
            unsigned char next;
            for (int i = 0; i < 10000000; i++) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    if (next != 0) {
                        fwrite(&next, sizeof(char), 1, out);
                    }
                } else {
                    break;
                }
            }
        }
        if (atoi(argv[3]) == 4) {
            unsigned char next1, next2, next3, next4;
            fwrite(&d, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&a, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next1 = fgetc(in);
                next2 = fgetc(in);
                next3 = fgetc(in);
                next4 = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next4, sizeof(char), 1, out);
                    fwrite(&next3, sizeof(char), 1, out);
                    fwrite(&next2, sizeof(char), 1, out);
                    fwrite(&next1, sizeof(char), 1, out);
                }
            }
        }
    } else if (a == 0xFF && b == 0xFE) {
        if (atoi(argv[3]) == 2) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 3) {
            unsigned char next1, next2;
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next1 = fgetc(in);
                next2 = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next2, sizeof(char), 1, out);
                    fwrite(&next1, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 0) {
            unsigned char next;
            fwrite(&c, sizeof(char), 1, out);
            int i = 0;
            for (int i = 0; i < 10000000; i++) {
                i++;
                next = fgetc(in);
                if (feof(in) != 0) {
                    break;
                }
                if (feof(in) == 0) {
                    if (i % 2 == 0) {
                        fwrite(&next, sizeof(char), 1, out);
                    }
                }
            }
        }
    } else {
        if (atoi(argv[3]) == 0) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 3) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 2) {
            unsigned char next;
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
        if (atoi(argv[3]) == 1) {
            unsigned char next, a1, a2, a3;
            a1 = 0xEF;
            a2 = 0xBB;
            a3 = 0xFB;
            fwrite(&a1, sizeof(char), 1, out);
            fwrite(&a2, sizeof(char), 1, out);
            fwrite(&a3, sizeof(char), 1, out);
            fwrite(&a, sizeof(char), 1, out);
            fwrite(&b, sizeof(char), 1, out);
            fwrite(&c, sizeof(char), 1, out);
            fwrite(&d, sizeof(char), 1, out);
            while (feof(in) == 0) {
                next = fgetc(in);
                if (feof(in) == 0) {
                    fwrite(&next, sizeof(char), 1, out);
                }
            }
        }
    }
    fclose(out);
    fclose(in);
    return 0;
}