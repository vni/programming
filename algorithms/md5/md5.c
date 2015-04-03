/* TODO: add test suite */
/* TODO: make it a separate package (library) */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned char byte;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define BLOCK_SIZE 64

#define ROTATE(value, s) ((value << s) | (value >> (32 - s)))

static void round1(uint32 d[4], uint32 *X)
{
#define F(X,Y,Z) (((X) & (Y)) | ((~(X)) & (Z)))
#define r1(a,b,c,d,k,s,t) ((a) = (b) + ROTATE((a) + F((b),(c),(d)) + X[(k)] + (t), (s)))
	/* [abcd k s i] ::: a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s) */

	/* [ABCD  0  7  1]  [DABC  1 12  2]  [CDAB  2 17  3]  [BCDA  3 22  4] */
	r1(d[0], d[1], d[2], d[3],  0,  7, 0xd76aa478);
	r1(d[3], d[0], d[1], d[2],  1, 12, 0xe8c7b756);
	r1(d[2], d[3], d[0], d[1],  2, 17, 0x242070db);
	r1(d[1], d[2], d[3], d[0],  3, 22, 0xc1bdceee);

	/* [ABCD  4  7  5]  [DABC  5 12  6]  [CDAB  6 17  7]  [BCDA  7 22  8] */
	r1(d[0], d[1], d[2], d[3],  4,  7, 0xf57c0faf);
	r1(d[3], d[0], d[1], d[2],  5, 12, 0x4787c62a);
	r1(d[2], d[3], d[0], d[1],  6, 17, 0xa8304613);
	r1(d[1], d[2], d[3], d[0],  7, 22, 0xfd469501);

	/* [ABCD  8  7  9]  [DABC  9 12 10]  [CDAB 10 17 11]  [BCDA 11 22 12] */
	r1(d[0], d[1], d[2], d[3],  8,  7, 0x698098d8);
	r1(d[3], d[0], d[1], d[2],  9, 12, 0x8b44f7af);
	r1(d[2], d[3], d[0], d[1], 10, 17, 0xffff5bb1);
	r1(d[1], d[2], d[3], d[0], 11, 22, 0x895cd7be);

	/* [ABCD 12  7 13]  [DABC 13 12 14]  [CDAB 14 17 15]  [BCDA 15 22 16] */
	r1(d[0], d[1], d[2], d[3], 12,  7, 0x6b901122);
	r1(d[3], d[0], d[1], d[2], 13, 12, 0xfd987193);
	r1(d[2], d[3], d[0], d[1], 14, 17, 0xa679438e);
	r1(d[1], d[2], d[3], d[0], 15, 22, 0x49b40821);
#undef r1
#undef F
}

static void round2(uint32 d[4], uint32 *X)
{
#define G(X,Y,Z) (((X) & (Z)) | ((Y) & (~(Z))))
#define r2(a,b,c,d,k,s,t) ((a) = (b) + ROTATE((a) + G((b),(c),(d)) + X[(k)] + (t), (s)))
	/* [abcd k s i] ::: a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s) */

	/* [ABCD  1  5 17]  [DABC  6  9 18]  [CDAB 11 14 19]  [BCDA  0 20 20] */
	r2(d[0], d[1], d[2], d[3],  1,  5, 0xf61e2562);
	r2(d[3], d[0], d[1], d[2],  6,  9, 0xc040b340);
	r2(d[2], d[3], d[0], d[1], 11, 14, 0x265e5a51);
	r2(d[1], d[2], d[3], d[0],  0, 20, 0xe9b6c7aa);

	/* [ABCD  5  5 21]  [DABC 10  9 22]  [CDAB 15 14 23]  [BCDA  4 20 24] */
	r2(d[0], d[1], d[2], d[3],  5,  5, 0xd62f105d);
	r2(d[3], d[0], d[1], d[2], 10,  9, 0x02441453);
	r2(d[2], d[3], d[0], d[1], 15, 14, 0xd8a1e681);
	r2(d[1], d[2], d[3], d[0],  4, 20, 0xe7d3fbc8);

	/* [ABCD  9  5 25]  [DABC 14  9 26]  [CDAB  3 14 27]  [BCDA  8 20 28] */
	r2(d[0], d[1], d[2], d[3],  9,  5, 0x21e1cde6);
	r2(d[3], d[0], d[1], d[2], 14,  9, 0xc33707d6);
	r2(d[2], d[3], d[0], d[1],  3, 14, 0xf4d50d87);
	r2(d[1], d[2], d[3], d[0],  8, 20, 0x455a14ed);

	/* [ABCD 13  5 29]  [DABC  2  9 30]  [CDAB  7 14 31]  [BCDA 12 20 32] */
	r2(d[0], d[1], d[2], d[3], 13,  5, 0xa9e3e905);
	r2(d[3], d[0], d[1], d[2],  2,  9, 0xfcefa3f8);
	r2(d[2], d[3], d[0], d[1],  7, 14, 0x676f02d9);
	r2(d[1], d[2], d[3], d[0], 12, 20, 0x8d2a4c8a);
#undef r2
#undef G
}

static void round3(uint32 d[4], uint32 *X)
{
#define H(X,Y,Z) ((X) ^ (Y) ^ (Z))
#define r3(a,b,c,d,k,s,t) ((a) = (b) + ROTATE((a) + H((b),(c),(d)) + X[(k)] + (t), (s)))
	/* [abcd k s t] ::: a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s) */

	/* [ABCD  5  4 33]  [DABC  8 11 34]  [CDAB 11 16 35]  [BCDA 14 23 36] */
	r3(d[0], d[1], d[2], d[3],  5,  4, 0xfffa3942);
	r3(d[3], d[0], d[1], d[2],  8, 11, 0x8771f681);
	r3(d[2], d[3], d[0], d[1], 11, 16, 0x6d9d6122);
	r3(d[1], d[2], d[3], d[0], 14, 23, 0xfde5380c);

	/* [ABCD  1  4 37]  [DABC  4 11 38]  [CDAB  7 16 39]  [BCDA 10 23 40] */
	r3(d[0], d[1], d[2], d[3],  1,  4, 0xa4beea44);
	r3(d[3], d[0], d[1], d[2],  4, 11, 0x4bdecfa9);
	r3(d[2], d[3], d[0], d[1],  7, 16, 0xf6bb4b60);
	r3(d[1], d[2], d[3], d[0], 10, 23, 0xbebfbc70);

	/* [ABCD 13  4 41]  [DABC  0 11 42]  [CDAB  3 16 43]  [BCDA  6 23 44] */
	r3(d[0], d[1], d[2], d[3], 13,  4, 0x289b7ec6);
	r3(d[3], d[0], d[1], d[2],  0, 11, 0xeaa127fa);
	r3(d[2], d[3], d[0], d[1],  3, 16, 0xd4ef3085);
	r3(d[1], d[2], d[3], d[0],  6, 23, 0x04881d05);

	/* [ABCD  9  4 45]  [DABC 12 11 46]  [CDAB 15 16 47]  [BCDA  2 23 48] */
	r3(d[0], d[1], d[2], d[3],  9,  4, 0xd9d4d039);
	r3(d[3], d[0], d[1], d[2], 12, 11, 0xe6db99e5);
	r3(d[2], d[3], d[0], d[1], 15, 16, 0x1fa27cf8);
	r3(d[1], d[2], d[3], d[0],  2, 23, 0xc4ac5665);
#undef r3
#undef H
}

static void round4(uint32 d[4], uint32 *X)
{
#define I(X,Y,Z) ((Y) ^ ((X) | (~(Z))))
#define r4(a,b,c,d,k,s,t) ((a) = (b) + ROTATE((a) + I((b),(c),(d)) + X[(k)] + (t), (s)))
	/* [ABCD  0  6 49]  [DABC  7 10 50]  [CDAB 14 15 51]  [BCDA  5 21 52] */
	r4(d[0], d[1], d[2], d[3],  0,  6, 0xf4292244);
	r4(d[3], d[0], d[1], d[2],  7, 10, 0x432aff97);
	r4(d[2], d[3], d[0], d[1], 14, 15, 0xab9423a7);
	r4(d[1], d[2], d[3], d[0],  5, 21, 0xfc93a039);

	/* [ABCD 12  6 53]  [DABC  3 10 54]  [CDAB 10 15 55]  [BCDA  1 21 56] */
	r4(d[0], d[1], d[2], d[3], 12,  6, 0x655b59c3);
	r4(d[3], d[0], d[1], d[2],  3, 10, 0x8f0ccc92);
	r4(d[2], d[3], d[0], d[1], 10, 15, 0xffeff47d);
	r4(d[1], d[2], d[3], d[0],  1, 21, 0x85845dd1);

	/* [ABCD  8  6 57]  [DABC 15 10 58]  [CDAB  6 15 59]  [BCDA 13 21 60] */
	r4(d[0], d[1], d[2], d[3],  8,  6, 0x6fa87e4f);
	r4(d[3], d[0], d[1], d[2], 15, 10, 0xfe2ce6e0);
	r4(d[2], d[3], d[0], d[1],  6, 15, 0xa3014314);
	r4(d[1], d[2], d[3], d[0], 13, 21, 0x4e0811a1);

	/* [ABCD  4  6 61]  [DABC 11 10 62]  [CDAB  2 15 63]  [BCDA  9 21 64] */
	r4(d[0], d[1], d[2], d[3],  4,  6, 0xf7537e82);
	r4(d[3], d[0], d[1], d[2], 11, 10, 0xbd3af235);
	r4(d[2], d[3], d[0], d[1],  2, 15, 0x2ad7d2bb);
	r4(d[1], d[2], d[3], d[0],  9, 21, 0xeb86d391);
#undef r4
#undef I
}

typedef struct {
	uint32 d[4];
	uint32 processed[2];
	byte buf[BLOCK_SIZE], pos;
} md5_ctx_t;

void md5_init(md5_ctx_t *p) {
	p->d[0] = 0x67452301;
	p->d[1] = 0xEFCDAB89;
	p->d[2] = 0x98BADCFE;
	p->d[3] = 0x10325476;
	p->processed[0] = p->processed[1] = 0;
	p->pos = 0;
}

static void md5_process_block(md5_ctx_t *p, uint32 *block) {
	uint32 orig[4];
	memcpy(orig, p->d, sizeof(orig));

	round1(p->d, block);
	round2(p->d, block);
	round3(p->d, block);
	round4(p->d, block);

	p->d[0] += orig[0];
	p->d[1] += orig[1];
	p->d[2] += orig[2];
	p->d[3] += orig[3];
}

static void md5_inc_processed(md5_ctx_t *p, unsigned by) {
	p->processed[0] += by;
	if (p->processed[0] < by)
		p->processed[1]++;
}

void md5_process(md5_ctx_t *p, const unsigned char *data, unsigned size) {
	if (p->pos) {
		uint n = BLOCK_SIZE - p->pos;
		if (n > size)
			n = size;
		memcpy(p->buf+p->pos, data, n);
		p->pos += n;
		data += n;
		size -= n;
		if (p->pos == BLOCK_SIZE) {
			md5_process_block(p, (uint32*)p->buf);
			md5_inc_processed(p, BLOCK_SIZE);
			p->pos = 0;
		}
	}
	while (size >= BLOCK_SIZE) {
		md5_process_block(p, (uint32*)data);
		md5_inc_processed(p, BLOCK_SIZE);
		data += BLOCK_SIZE;
		size -= BLOCK_SIZE;
	}
	memcpy(p->buf, data, size);
	p->pos = size;
}

void md5_finish(md5_ctx_t *p) {
	md5_inc_processed(p, p->pos);

	// size should be in bits
	p->processed[1] <<= 3;
	p->processed[1] |= (p->processed[0] >> 29) & 7;
	p->processed[0] <<= 3;

	p->buf[p->pos++] = 0x80;

	if (p->pos > 56) {
		while (p->pos < BLOCK_SIZE)
			p->buf[p->pos++] = 0x00;
		md5_process_block(p, (uint32*)p->buf);
		p->pos = 0;
	}

	while (p->pos < 56)
		p->buf[p->pos++] = 0x00;

	/* append size */
	p->buf[p->pos++] = p->processed[0];
	p->buf[p->pos++] = p->processed[0] >> 8;
	p->buf[p->pos++] = p->processed[0] >> 16;
	p->buf[p->pos++] = p->processed[0] >> 24;
	p->buf[p->pos++] = p->processed[1];
	p->buf[p->pos++] = p->processed[1] >> 8;
	p->buf[p->pos++] = p->processed[1] >> 16;
	p->buf[p->pos++] = p->processed[1] >> 24;

	md5_process_block(p, (uint32*)p->buf);

	// put complited md5 hash into buf
	p->buf[ 0] = (byte)(p->d[0]);
	p->buf[ 1] = (byte)(p->d[0]>>8);
	p->buf[ 2] = (byte)(p->d[0]>>16);
	p->buf[ 3] = (byte)(p->d[0]>>24);
	p->buf[ 4] = (byte)(p->d[1]);
	p->buf[ 5] = (byte)(p->d[1]>>8);
	p->buf[ 6] = (byte)(p->d[1]>>16);
	p->buf[ 7] = (byte)(p->d[1]>>24);
	p->buf[ 8] = (byte)(p->d[2]);
	p->buf[ 9] = (byte)(p->d[2]>>8);
	p->buf[10] = (byte)(p->d[2]>>16);
	p->buf[11] = (byte)(p->d[2]>>24);
	p->buf[12] = (byte)(p->d[3]);
	p->buf[13] = (byte)(p->d[3]>>8);
	p->buf[14] = (byte)(p->d[3]>>16);
	p->buf[15] = (byte)(p->d[3]>>24);
}

static void processFile(int fd, const char *filename)
{
	md5_ctx_t md5;
	byte bigbuf[4096];
	int n;

	md5_init(&md5);

	while ((n = read(fd, bigbuf, sizeof(bigbuf))) > 0)
		md5_process(&md5, bigbuf, n);
	if (n == -1) {
		fprintf(stderr, "Error occured during reading the file: %s\n", strerror(errno));
		return;
	}

	md5_finish(&md5);
	for (n=0; n<16; n++)
		printf("%02x", md5.buf[n]);
	printf("  %s\n", filename);
}

int main(int argc, char *argv[])
{
	while (*++argv) {
		int fd = open(*argv, O_RDONLY);
		if (fd == -1) {
			fprintf(stderr, "Couldn't open %s: %s\n", *argv, strerror(errno));
			continue;
		}
		processFile(fd, *argv);
		close(fd);
	}
	return 0;
}
