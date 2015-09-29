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
/*#define ROTATE(value, s) ((value << s) | (value >> (32 - s)))*/

uint32 ROTATE(uint32 value, uint32 s) {
	return ((value << s) | (value >> (32 - s)));
}

typedef struct {
	uint32 h[5];
	uint32 processed[2];
	byte buf[BLOCK_SIZE], pos;
} sha1_ctx_t;

void sha1_init(sha1_ctx_t *p)
{
	p->h[0] = 0x67452301;
	p->h[1] = 0xEFCDAB89;
	p->h[2] = 0x98BADCFE;
	p->h[3] = 0x10325476;
	p->h[4] = 0xC3D2E1F0;

	p->processed[0] = p->processed[1] = 0;
	p->pos = 0;
}

void sha1_process_block(sha1_ctx_t *p, const byte *block)
{
	static uint32 K[4] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };

	uint32 a, b, c, d, e, f, k, temp;

	a = p->h[0];
	b = p->h[1];
	c = p->h[2];
	d = p->h[3];
	e = p->h[4];

	uint32 w[80];
	int i;

	for (i = 0; i < 16; i++) {
		w[i]  = block[i*4+0] << 24;
		w[i] |= block[i*4+1] << 16;
		w[i] |= block[i*4+2] << 8;
		w[i] |= block[i*4+3];
	}

	for (i = 16; i < 80; i++)
		w[i] = ROTATE((w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]), 1);

	for (i = 0; i < 80; i++) {
		if (0 <= i && i < 20) {
			f = (b & c) ^ ((~b) & d);
			k = K[0];
		} else if (20 <= i && i < 40) {
			f = b ^ c ^ d;
			k = K[1];
		} else if (40 <= i && i < 60) {
			f = (b & c) ^ (b & d) ^ (c & d);
			k = K[2];
		} else if (60 <= i && i < 80) {
			f = b ^ c ^ d;
			k = K[3];
		}

		temp = ROTATE(a, 5) + f + e + k + w[i];
		e = d;
		d = c;
		c = ROTATE(b, 30);
		b = a;
		a = temp;
	}

	p->h[0] += a;
	p->h[1] += b;
	p->h[2] += c;
	p->h[3] += d;
	p->h[4] += e;
}

void sha1_inc_processed(sha1_ctx_t *p, unsigned by)
{
	p->processed[0] += by;
	if (p->processed[0] < by)
		p->processed[1]++;
}

void sha1_process(sha1_ctx_t *p, const byte *data, unsigned size)
{
	if (p->pos) {
		uint n = BLOCK_SIZE - p->pos;
		if (n > size)
			n = size;
		memcpy(p->buf+p->pos, data, n);
		p->pos += n;
		data += n;
		size -= n;
		if (p->pos == BLOCK_SIZE) {
			sha1_process_block(p, p->buf);
			sha1_inc_processed(p, BLOCK_SIZE);
			p->pos = 0;
		}
	}

	while (size >= BLOCK_SIZE) {
		sha1_process_block(p, data);
		sha1_inc_processed(p, BLOCK_SIZE);
		data += BLOCK_SIZE;
		size -= BLOCK_SIZE;
	}

	memcpy(p->buf, data, size);
	p->pos = size;
}

void sha1_finish(sha1_ctx_t *p)
{
	sha1_inc_processed(p, p->pos);

	/* size is expected to be in bits */
	p->processed[1] <<= 3;
	p->processed[1] |= (p->processed[0] >> 29) & 7;
	p->processed[0] <<= 3;

	p->buf[p->pos++] = 0x80;

	if (p->pos > 56) {
		while (p->pos < BLOCK_SIZE)
			p->buf[p->pos++] = 0x00;
		sha1_process_block(p, p->buf);
		p->pos = 0;
	}

	while (p->pos < 56)
		p->buf[p->pos++] = 0x00;

	/* append size */
	p->buf[p->pos++] = p->processed[1] >> 24;
	p->buf[p->pos++] = p->processed[1] >> 16;
	p->buf[p->pos++] = p->processed[1] >> 8;
	p->buf[p->pos++] = p->processed[1];
	p->buf[p->pos++] = p->processed[0] >> 24;
	p->buf[p->pos++] = p->processed[0] >> 16;
	p->buf[p->pos++] = p->processed[0] >> 8;
	p->buf[p->pos++] = p->processed[0];

	sha1_process_block(p, p->buf);

	/* put completed sha1 hash into buf */
	p->buf[ 0] = (byte)(p->h[0]>>24);
	p->buf[ 1] = (byte)(p->h[0]>>16);
	p->buf[ 2] = (byte)(p->h[0]>>8);
	p->buf[ 3] = (byte)(p->h[0]);
	p->buf[ 4] = (byte)(p->h[1]>>24);
	p->buf[ 5] = (byte)(p->h[1]>>16);
	p->buf[ 6] = (byte)(p->h[1]>>8);
	p->buf[ 7] = (byte)(p->h[1]);
	p->buf[ 8] = (byte)(p->h[2]>>24);
	p->buf[ 9] = (byte)(p->h[2]>>16);
	p->buf[10] = (byte)(p->h[2]>>8);
	p->buf[11] = (byte)(p->h[2]);
	p->buf[12] = (byte)(p->h[3]>>24);
	p->buf[13] = (byte)(p->h[3]>>16);
	p->buf[14] = (byte)(p->h[3]>>8);
	p->buf[15] = (byte)(p->h[3]);
	p->buf[16] = (byte)(p->h[4]>>24);
	p->buf[17] = (byte)(p->h[4]>>16);
	p->buf[18] = (byte)(p->h[4]>>8);
	p->buf[19] = (byte)(p->h[4]);
}

static void processFile(int fd, const char *filename)
{
	sha1_ctx_t sha1;
	byte bigbuf[4096];
	int n;

	sha1_init(&sha1);

	while ((n = read(fd, bigbuf, sizeof(bigbuf))) > 0)
		sha1_process(&sha1, bigbuf, n);
	if (n == -1) {
		fprintf(stderr, "Error occured during reading %s: %s\n", filename, strerror(errno));
		return;
	}

	sha1_finish(&sha1);
	for (n = 0; n < 20; n++)
		printf("%02x", sha1.buf[n]);
	printf(" %s\n", filename);
}

int main(int argc, char *argv[]) {
	int unit_test(void);
	if (argc == 2 && (strcmp(argv[1], "--test") == 0))
		return unit_test();

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

/* UNIT TESTING */

static int total_tests = 0;
static int failed_tests = 0;

int unit_test(void)
{
	struct {
		const char *str;
		char digest[41]; /* printable version of digest */
	} tests[] = {
		{ "", "da39a3ee5e6b4b0d3255bfef95601890afd80709" },
		{ "abc", "a9993e364706816aba3e25717850c26c9cd0d89d" },
		{ "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq","84983e441c3bd26ebaae4aa1f95129e5e54670f1" },
		{ "aaaaaaaaaa", "3495ff69d34671d1e15b33a63c1379fdedd3a32a" },
	};

	sha1_ctx_t sha1;
	int i, j;
	char dbuf[41], digest[41], buf[64];

	for (i=0; i < (sizeof(tests)/sizeof(tests[0])); i++) {
		total_tests++;
		sha1_init(&sha1);
		sha1_process(&sha1, tests[i].str, strlen(tests[i].str));
		sha1_finish(&sha1);
		for (j = 0; j < 20; j++)
			snprintf(dbuf+j*2, sizeof(dbuf)-j*2, "%02x", sha1.buf[j]);
		if (strncmp(dbuf, tests[i].digest, sizeof(dbuf))) {
			fprintf(stderr, "FAILED: on string \"%s\". Expected digest: \"%s\". Got: \"%s\"\n",
					tests[i].str, tests[i].digest, dbuf);
			failed_tests++;
		}
	}
	printf("Total tests run: %d, passed: %d, failed: %d\n", total_tests, total_tests - failed_tests, failed_tests);

	return failed_tests;
}
