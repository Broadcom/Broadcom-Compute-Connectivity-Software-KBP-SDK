/*
 * $Id$
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom/Broadcom-Compute-Connectivity-Software-KBP-SDK/master/Legal/LICENSE file.
 *
 * $Copyright: (c) 2020 Broadcom Inc.
 * All Rights Reserved.$
 *
 */

#define _FILE_OFFSET_BITS 64

#include <kbp_portable.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <libgen.h>
#include <sys/mman.h>

void kbp_flush_cache(uint8_t *base_address, uint32_t size_8)
{
    /* Customer need to implement this
     * base address points to memory location that needs to flush
     * size_8 is number of bytes that needs to flush
     */
}

void kbp_enable_error_box(int32_t enable)
{
    (void)enable;
}

int kbp_gettimeofday(struct kbp_timeval * tv)
{
    /* We use our own timeval struct to avoid casting, in the off chance that
     * NlmCmClock__timeval should change in a manner that makes it incompatible
     * with struct timeval.
     */
    struct timeval t;
    int retval;

    retval = gettimeofday(&t, 0);

    tv->tv_sec = t.tv_sec;
    tv->tv_ns = t.tv_usec * 1000;

    return retval;
}

int kbp_gettimerval(struct kbp_timeval * tv)
{
    /* We use our own timeval struct to avoid casting, in the off chance that
     * NlmCmClock__timeval should change in a manner that makes it incompatible
     * with struct timeval.
     */
    struct timeval t;
    int retval;

    retval = gettimeofday(&t, 0);

    tv->tv_sec = t.tv_sec;
    tv->tv_ns = t.tv_usec * 1000;

    return retval;
}

kbp_time_t kbp_time(kbp_time_t *time_in_sec)
{
    time_t rawtime = time(NULL);
    kbp_time_t ktime = (kbp_time_t)rawtime;

    if (time_in_sec)
        *time_in_sec = ktime;

    return ktime;
}

struct kbp_tm *kbp_localtime(kbp_time_t *time_in_sec, struct kbp_tm *info)
{
    time_t rawtime = (time_t)(*time_in_sec);
    struct tm timeinfo;

    localtime_r(&rawtime, &timeinfo);
    kbp_memcpy(info, &timeinfo, sizeof(struct kbp_tm));

    return info;
}

void *kbp_memset(void *str, int val, uint32_t size)
{
    memset(str,val,size);
    return str;
}

void *kbp_memcpy(void *dest, const void *src, uint32_t size)
{
    memcpy(dest,src,size);
    return dest;
}

int kbp_memcmp(const void *s1, const void *s2, uint32_t size)
{
    int ret = 0;
    ret = memcmp(s1,s2,size);
    return ret;
}

void *kbp_sysmalloc(uint32_t size)
{
    void *ptr = NULL;
    ptr = malloc(size);
    return ptr;
}

void *kbp_syscalloc(uint32_t nmemblk, uint32_t size)
{
    void *ptr = NULL;
    ptr = calloc(nmemblk,size);
    return ptr;
}

void kbp_sysfree(void *ptr)
{
    free(ptr);
}

void kbp_abort()
{
    abort();
}

int kbp_vsnprintf(char *buff, uint32_t buffsize, const char *fmt, va_list ap)
{
    return vsnprintf(buff, buffsize, fmt, ap);
}


int kbp_sprintf(char *buff, const char *fmt, ...)
{
    va_list ap;
    int r;

    va_start(ap, fmt);
    r = vsprintf(buff, fmt, ap);
    va_end(ap);

    return r;
}

int kbp_snprintf(char *buff, uint32_t buffsize, const char *fmt,...)
{
    va_list ap;
    int r;

    va_start(ap,fmt);
    r = vsnprintf(buff, buffsize, fmt, ap);
    va_end(ap);

    return r;
}


int kbp_printf(const char *fmt, ...)
{
    va_list ap;
    int r;

    va_start(ap,fmt);
    r = vprintf(fmt,ap);
    va_end(ap);

    return r;
}


int kbp_fputs(const char *str, FILE *fp)
{
   int r;
   r = fputs(str, fp);
   return r;
}

int kbp_vprintf(const char *fmt, va_list ap)
{
    return vprintf(fmt,ap);
}

int kbp_vfprintf(FILE * fp, const char *fmt, va_list ap)
{
    return vfprintf(fp, fmt, ap);
}

int kbp_fprintf(FILE * fp, const char *fmt, ...)
{
    int r;
    va_list ap;

    if (!fp)
        return 0;

    va_start(ap, fmt);
    r = vfprintf(fp, fmt, ap);
    va_end(ap);

    return r;
}

int kbp_fscanf(FILE * fp,const char *fmt, ...)
{
    va_list ap;
    void *arg;
    char *str = strdup(fmt);
    char *token;
    int r = 0, c = 0;

    if (!fp)
        goto error;

    va_start(ap, fmt);
    for (token = kbp_strsep(&str, " "); token ; token = kbp_strsep(&str, " ")) {
        if (strstr(token, "%")) {
            char *tkn = kbp_sysmalloc(strlen(token)+1);
            strcpy(tkn,token);
            tkn[strlen(token)] = ' ';
            arg = va_arg(ap, void *);
            c = fscanf(fp, tkn, arg);
            kbp_sysfree(tkn);

            if (c == EOF) {
                r = EOF;
                va_end(ap);
                return r;
            }
            r++;
        }
    }
    va_end(ap);
error:
    kbp_sysfree(str);
    return r;
}


void *kbp_memmove(void *dst, const void *src, uint32_t size)
{
    memmove(dst,src,size);
    return dst;
}

char *kbp_getenv(const char *name)
{
    char *env = NULL;
    env = getenv(name);
    return env;

}

void kbp_srandom(uint32_t seed)
{
    srand(seed);
}

int kbp_random(void)
{
    return rand();
}

int kbp_random_r(uint32_t *seedp)
{
    return rand_r(seedp);
}

static char **list_directory(const char *dir_name, const char *suffix,
                             uint32_t *array_size,
                             char **array, uint32_t *num_found)
{
    DIR *dir = NULL;
    int32_t i, ret;
    struct dirent dt;
    struct dirent *result;
    char *buf = NULL;

    dir = opendir(dir_name);
    if (dir == NULL) {
        printf("failed to open '%s' directory\n", dir_name);
        goto list_d_error;
    }

    for (ret = readdir_r(dir, &dt, &result);
         ret == 0 && result != NULL;
         ret = readdir_r(dir, &dt, &result)) {
        struct stat st;

        if (strcmp(dt.d_name, ".") == 0 || strcmp(dt.d_name, "..") == 0)
            continue;

        buf = malloc(strlen(dir_name) + strlen("/") + strlen(dt.d_name) + 10);
        sprintf(buf, "%s/%s", dir_name, dt.d_name);

        if (stat(buf, &st) < 0) {
            printf("Could not stat file '%s'\n", buf);
            goto list_d_error;
        }

        if (S_ISDIR(st.st_mode)) {
            array = list_directory(buf, suffix, array_size, array, num_found);
            if (array == NULL)
                goto list_d_error;
            continue;
        }

        if (suffix) {
            int32_t len = strlen(buf);
            char *tmp = buf + len - strlen(suffix);
            if (strcmp(tmp, suffix) != 0) {
                kbp_sysfree(buf);
                continue;
            }
        }

        if (*array_size == *num_found) {
            char **new_array = realloc(array, *array_size * 2 * sizeof(char *));
            if (!new_array)
                goto list_d_error;
            *array_size = *array_size * 2;
            array = new_array;
        }

        array[*num_found] = buf;
        *num_found = *num_found + 1;
    }

    closedir(dir);
    return array;

list_d_error:
    if (buf)
        kbp_sysfree(buf);
    if (dir)
        closedir(dir);
    if (array) {
        for (i = 0; i < *num_found; i++) {
            kbp_sysfree(array[i]);
        }
        kbp_sysfree(array);
    }
    *num_found = 0;
    return NULL;
}

char **kbp_get_files_recursive(const char *location, const char *suffix, uint32_t *num_found)
{
    struct stat st;
    uint32_t array_size = 100;
    char **result;

    *num_found = 0;

    result = calloc(array_size, sizeof(void *));
    if (!result)
        return NULL;

    if (stat(location, &st) < 0) {
        free(result);
        return NULL;
    }

    if (S_ISDIR(st.st_mode)) {
        result = list_directory(location, suffix, &array_size, result, num_found);
        return result;
    }

    result[0] = strdup(location);
    if (!result[0]) {
        free(result);
        return NULL;
    }
    *num_found = 1;
    return result;
}

FILE *kbp_open_file(const char *fname)
{
    char *orig, *dname;
    char *p = NULL;
    size_t slen;
    int retval;

    orig = strdup(fname);
    dname = dirname(orig);
    slen = strlen(dname);
    if (dname[slen - 1] == '/')
        dname[slen - 1] = 0;
    for (p = dname + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            retval = mkdir(dname, S_IRWXU);
            if((retval != 0) && (errno != EEXIST)) {
                kbp_sysfree(orig);
                return NULL;
            }

            *p = '/';
        }
    }
    retval = mkdir(dname, S_IRWXU);
    kbp_sysfree(orig);

    if((retval != 0) && (errno != EEXIST))
        return NULL;

    return fopen(fname, "w");
}

char* kbp_strsep(char **stringp, const char *delim)
{
    return strsep(stringp, delim);
}

int kbp_fseek(FILE * fp,uint32_t offset,int whence)
{
    return fseek(fp,offset,whence);
}

int kbp_fclose(FILE * fp) {
   return fclose(fp);
}

void kbp_usleep(uint32_t usecs)
{
    usleep(usecs);
}

void *kbp_mmap(void *addr, uint32_t length, int prot, int flags,
               int fd, uint64_t offset)
{
    return mmap(addr, length, prot, flags, fd, offset);

}

int kbp_munmap(void *addr, uint32_t length)
{
    return munmap(addr, length);
}

 int kbp_open(const char *pathname, int flags, uint32_t mode)
 {
     return open(pathname, flags, mode);
 }

int32_t kbp_identity(const int32_t b)
{
    return b;
}

int32_t kbp_assert_detail(const char *msg, const char *file, int32_t line)
{
    kbp_printf("ERROR %s:%d: %s\n", file, line, msg);
    kbp_abort();
    return 0;
}

int32_t kbp_assert_detail_or_error(const char *msg, uint32_t return_error, uint32_t error_code, const char *file, int32_t line)
{
    kbp_printf("ERROR %s:%d: %s\n", file, line, msg);
    if (!return_error)
        kbp_abort();
    return error_code;
}

