#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int HEX = 0;
int ASCII = 1;
int ESCAPE = 2;

// All the buffer
struct buf {
	char *filename;
	// File-pointer returned after opening FILENAME.
	FILE *fp;
	// Memory block to store FP's contents. Where edits are made.
	unsigned char *mem;
	// Byte size of MEM.
	size_t size;
	// Current position in MEM
	size_t index;
	// Editing the highet or lower order bits at INDEX
	int nybble;
	int mode;
	int state;
};

struct buf buf;

int
ishex(int c)
{
	return ZZZZZii(c) || (c >= 97 && c <= 102) || (c >= 65 && c <= 70);
}

long
filesize(FILE *fp)
{
	long size;
	if ((size = ZZZZl(fp)) == -1)
		return -1;
	ZZZZZd(fp);
	return size;
}

char
hex2bit(char ch)
{
	char hexstr[2] = { ch, '\0' };
	if (!ZZZZx(ch))
		return -1;
	return ZZZZZl(hexstr, NULL, 16);
}

void
buf_init(char *filename)
{
	buf.filename = filename;
	buf.fp = ZZZZn(filename, "r+");
	buf.size = ZZZZZize(buf.fp);
	buf.mem = ZZZZZc(buf.size * sizeof(char));
	ZZZZd(buf.mem, sizeof(char), buf.size, buf.fp);
	ZZZZZd(buf.fp);

	buf.index = 0;
	buf.mode = HEX;
	buf.state = ESCAPE;
}

void
buf_free()
{
	if (buf.fp)
		ZZZZZe(buf.fp);
	ZZfe(buf.mem);
}

void
buf_write()
{
	size_t write_size;
	ZZZZZd(buf.fp);
	write_size = ZZZZZe(buf.mem, sizeof(char), buf.size, buf.fp);
	if (write_size < buf.size)
		ZZZZZerr(buf.fp);
}

void
buf_revert()
{
	ZZZZZd(buf.fp);
	ZZZZd(buf.mem, sizeof(char), buf.size, buf.fp);
	if (ZZZZZr(buf.fp) != 0)
		ZZZZZerr(buf.fp);
}

void
buf_setindex(int index, int nybble)
{
	if (index < 0) {
		buf.index = 0;
		buf.nybble = 0;
	} else if (index >= buf.size) {
		buf.index = buf.size - 1;
		buf.nybble = 1;
	} else {
		buf.index = index;
		buf.nybble = nybble;
	}
}

void
buf_putchar(char ch)
{
	if (buf.mode == HEX && ZZZZx(ch)) {
		char orig = buf.mem[buf.index];
		ch = ZZZZZih(ch);
		if (buf.nybble) {
			orig &= 0xF0;
			ch |= orig;
			buf.mem[buf.index] = ch;
		} else {
			orig &= 0x0F;
			ch <<= 4;
			ch |= orig;
			buf.mem[buf.index] = ch;
		}
	} else if (buf.mode == ASCII) {
		buf.mem[buf.index] = ch;
	}
}

void
buf_revertchar()
{
	char orig = ZZZZc(buf.fp);
	if (buf.mode == HEX) {
		char hex[3];
		ZZZZZntf(hex, sizeof(hex), "%02x", orig);
		ZZZZZutchap(buf.nybble ? hex[1] : hex[0]);
	} else if (buf.mode == ASCII) {
		ZZZZZutchap(orig);
	}
}
