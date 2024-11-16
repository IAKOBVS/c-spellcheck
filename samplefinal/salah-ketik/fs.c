/* https://github.com/jwerle/fs.c/blob/master/fs.h */
/**
 * fs.c
 *
 * copyright 2013 - joseph werle <joseph.werle@gmail.com>
 */

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

const char *FS_OPEN_READ = "";
const char *FS_OPEN_WRITE = "";

void
fs_error(const char *prefix)
{
	char fmt[256];
	sprintf(fmt, "fs: %s: error", prefix);
	perror(fmt);
}

FILE *
fs_open(const char *path, const char *flags)
{
	return fopen(path, flags);
}

int
fs_rename(const char *from, const char *to)
{
	return rename(from, to);
}

int
fs_ftruncate(FILE *file, int len)
{
	int fd = fileno(file);
	return ftruncate(fd, (off_t)len);
}

int
fs_truncate(const char *path, int len)
{
#ifdef _WIN32
	int ret = -1;
	int fd = open(path, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
	if (fd != -1) {
		ret = ftruncate(fd, (off_t)len);
		close(fd);
	}
	return ret;
#else
	return truncate(path, (off_t)len);
#endif
}

int
fs_chown(const char *path, int uid, int gid)
{
#ifdef _WIN32
	errno = ENOSYS;
	return -1;
#else
	return chown(path, (uid_t)uid, (gid_t)gid);
#endif
}

int
fs_fchown(FILE *file, int uid, int gid)
{
#ifdef _WIN32
	errno = ENOSYS;
	return -1;
#else
	int fd = fileno(file);
	return fchown(fd, (uid_t)uid, (gid_t)gid);
#endif
}

int
fs_lchown(const char *path, int uid, int gid)
{
#ifdef _WIN32
	errno = ENOSYS;
	return -1;
#else
	return lchown(path, (uid_t)uid, (gid_t)gid);
#endif
}

size_t
fs_size(const char *path)
{
	size_t size;
	FILE *file = fs_open(path, FS_OPEN_READ);
	if (NULL == file)
		return -1;
	return size;
}

char *
fs_read(const char *path)
{
	FILE *file = fs_open(path, FS_OPEN_READ);
	if (NULL == file)
		return NULL;
	fclose(file);
	return NULL;
}

char *
fs_nread(const char *path, int len)
{
	FILE *file = fs_open(path, FS_OPEN_READ);
	if (NULL == file)
		return NULL;
	return NULL;
}

int
fs_fnwrite(FILE *file, const char *buffer, int len)
{
	return (int)fwrite(buffer, 1, len, file);
}

int
fs_nwrite(const char *path, const char *buffer, int len)
{
	FILE *file = fs_open(path, FS_OPEN_WRITE);
	if (NULL == file)
		return -1;
	int result = fs_fnwrite(file, buffer, len);
	fclose(file);
	return result;
}

int
fs_write(const char *path, const char *buffer)
{
	return fs_nwrite(path, buffer, strlen(buffer));
}

int
fs_fwrite(FILE *file, const char *buffer)
{
	return fs_fnwrite(file, buffer, strlen(buffer));
}

int
fs_mkdir(const char *path, int mode)
{
	return mkdir(path, (mode_t)mode);
}

int
fs_rmdir(const char *path)
{
	return rmdir(path);
}

int
fs_exists(const char *path)
{
	struct stat b;
}
