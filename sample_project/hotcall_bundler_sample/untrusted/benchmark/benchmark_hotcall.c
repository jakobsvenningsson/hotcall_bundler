#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include <stdarg.h>
#include "postfix_translator.h"
#include "hotcall_bundler_sample_u.h"
#include "sample.h"


/*
*   What is the effect on the number of arguments ?
*   We can see that the number of arguments of a function increases the execution time of a HCALL.
*   A function which does nothing andtakes 15 arguments takes roughly twice as long to execute in comparison
*   to a function which does nothing and take no arguments.
*
*   The results suggest that ít might be wiser to replace functions which has a lot of arguments with a struct instead.
*/

unsigned int
benchmark_hotcall_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    printf("benchmark_hotcall_0\n");
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        BEGIN
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_0));
        CLOSE
        t = GET_TIME
        if(i >= warmup) {
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


#include <time.h>

unsigned int
benchmark_vanilla_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    //FILE *fp;
    //fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    int ret;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        BEGIN
        ecall_test_func_0(global_eid);
        CLOSE
        t = GET_TIME
        if(i >= warmup) {
            rounds[i - warmup] = t;
            //fprintf(fp, "%d\n", t);
        }
        //printf("T: %u\n", t);
    }
    //fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_1";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int x = 0;
        BEGIN
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_1), VAR(x, 'd'));
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_1";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int x = 0;
        BEGIN
        ecall_test_func_1(global_eid, x);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_3";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int x = 0, y = 0, z = 0;
        BEGIN
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_3), VAR(x, 'd'), VAR(y, 'd'), VAR(z, 'd'));
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_3";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int x = 0, y = 0, z = 0;
        BEGIN
        ecall_test_func_3(global_eid, x, y, z);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_5";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int a, b, c, d, e;
        a = b = c = d = e = 0;
        BEGIN
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_5),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
        );
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_5";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int a, b, c, d, e;
        a = b = c = d = e = 0;
        BEGIN
        ecall_test_func_5(global_eid, a, b, c, d, e);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_10";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int a, b, c, d, e, f, g, h, t, j;
        a = b = c = d = e = f = g = h = t = j = 0;
        BEGIN
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_10),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
            VAR(f, 'd'),
            VAR(g, 'd'),
            VAR(h, 'd'),
            VAR(t, 'd'),
            VAR(j, 'd')
        );
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_10";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int a, b, c, d, e, f, g, h, t, j;
        a = b = c = d = e = f = g = h = t = j = 0;
        BEGIN
        ecall_test_func_10(global_eid, a, b, c, d, e, f, g, h, t, j);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_15";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int a, b, c, d, e, f, g, h, t, j, l, m, n, o, p;
        a = b = c = d = e = f = g = h = t = j = l = m = n = o = p = 0;
        BEGIN
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_15),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
            VAR(f, 'd'),
            VAR(g, 'd'),
            VAR(h, 'd'),
            VAR(t, 'd'),
            VAR(j, 'd'),
            VAR(l, 'd'),
            VAR(m, 'd'),
            VAR(n, 'd'),
            VAR(o, 'd'),
            VAR(p, 'd'),
        );
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_15";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache();
        int a, b, c, d, e, f, g, h, t, j, l, m, n, o, p;
        a = b = c = d = e = f = g = h = t = j = l = m = n = o = p = 0;
        BEGIN
        ecall_test_func_15(global_eid, a, b, c, d, e, f, g, h, t, j, l, m, n, o, p);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


void
variadic_function(int n, ...) {
    va_list args;
    va_start(args, n);

    int x = 0;
    for(int i = 0; i < n; ++i) {
        x += va_arg(args, int);
    }

    va_end(args);
}

unsigned int
benchmark_variadic_function(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds) {
    unsigned int warmup = n_rounds / 10;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        //if(cold_cache) clear_cache();
        BEGIN
        variadic_function(10, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        CLOSE
        if(i >= warmup) {
            rounds[i - warmup] = GET_TIME
        }
    }
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
