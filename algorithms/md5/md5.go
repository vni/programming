/* TODO: add test suite */
/* TODO: make it a separate package */

package main
import("os";"io";"fmt")

const BLOCK_SIZE = 64

type md5 struct {
	A, B, C, D uint32
	size uint64
	buf [BLOCK_SIZE]byte
	pos byte
}

func New() *md5 {
	return &md5{
		A: 0x67452301,
		B: 0xEFCDAB89,
		C: 0x98BADCFE,
		D: 0x10325476,
		size: 0,
		pos: 0,
	}
}

func rotate(value, shift uint32) uint32 {
	return (value << shift) | (value >> (32-shift))
}

func F(X, Y, Z uint32) uint32 { return X & Y | ^X & Z }
func G(X, Y, Z uint32) uint32 { return X & Z | Y & ^Z }
func H(X, Y, Z uint32) uint32 { return X ^ Y ^ Z }
func I(X, Y, Z uint32) uint32 { return Y ^ (X | ^Z) }

func round(a *uint32, b, c, d, data, s, t uint32, fun func(X,Y,Z uint32) uint32) {
	*a = b + rotate(*a + fun(b, c, d) + data + t, s)
}

func (md5 *md5) process_block(bytes_block []byte) {
	if len(bytes_block) != BLOCK_SIZE {
		panic("len(block) expected to be BLOCK_SIZE bytes long")
	}

	// FIXME: Do not know how to convert [64]byte to [16]uint32 properly in go
	var block [16]uint32
	for i:=0; i<len(block); i++ {
		block[i] |= uint32(bytes_block[i*4+3])
		block[i] <<= 8
		block[i] |= uint32(bytes_block[i*4+2])
		block[i] <<= 8
		block[i] |= uint32(bytes_block[i*4+1])
		block[i] <<= 8
		block[i] |= uint32(bytes_block[i*4+0])
	}

	AA := md5.A
	BB := md5.B
	CC := md5.C
	DD := md5.D

	// ROUND 1 [abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)
	// [ABCD  0 7  1][DABC  1 12  2][CDAB  2 17  3][BCDA  3 22  4]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 0],  7, 0xd76aa478, F)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 1], 12, 0xe8c7b756, F)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 2], 17, 0x242070db, F)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 3], 22, 0xc1bdceee, F)

	// [ABCD  4 7  5][DABC  5 12  6][CDAB  6 17  7][BCDA  7 22  8]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 4],  7, 0xf57c0faf, F)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 5], 12, 0x4787c62a, F)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 6], 17, 0xa8304613, F)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 7], 22, 0xfd469501, F)

	// [ABCD  8 7  9][DABC  9 12 10][CDAB 10 17 11][BCDA 11 22 12]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 8],  7, 0x698098d8, F)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 9], 12, 0x8b44f7af, F)
	round(&md5.C, md5.D, md5.A, md5.B, block[10], 17, 0xffff5bb1, F)
	round(&md5.B, md5.C, md5.D, md5.A, block[11], 22, 0x895cd7be, F)

	// [ABCD 12 7 13][DABC 13 12 14][CDAB 14 17 15][BCDA 15 22 16]
	round(&md5.A, md5.B, md5.C, md5.D, block[12],  7, 0x6b901122, F)
	round(&md5.D, md5.A, md5.B, md5.C, block[13], 12, 0xfd987193, F)
	round(&md5.C, md5.D, md5.A, md5.B, block[14], 17, 0xa679438e, F)
	round(&md5.B, md5.C, md5.D, md5.A, block[15], 22, 0x49b40821, F)

	// ROUND 2 [abcd k s i] a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s)
	// [ABCD  1 5 17][DABC  6 9 18][CDAB 11 14 19][BCDA  0 20 20]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 1],  5, 0xf61e2562, G)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 6],  9, 0xc040b340, G)
	round(&md5.C, md5.D, md5.A, md5.B, block[11], 14, 0x265e5a51, G)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 0], 20, 0xe9b6c7aa, G)

	// [ABCD  5 5 21][DABC 10 9 22][CDAB 15 14 23][BCDA  4 20 24]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 5],  5, 0xd62f105d, G)
	round(&md5.D, md5.A, md5.B, md5.C, block[10],  9, 0x02441453, G)
	round(&md5.C, md5.D, md5.A, md5.B, block[15], 14, 0xd8a1e681, G)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 4], 20, 0xe7d3fbc8, G)

	// [ABCD  9 5 25][DABC 14 9 26][CDAB  3 14 27][BCDA  8 20 28]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 9],  5, 0x21e1cde6, G)
	round(&md5.D, md5.A, md5.B, md5.C, block[14],  9, 0xc33707d6, G)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 3], 14, 0xf4d50d87, G)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 8], 20, 0x455a14ed, G)

	// [ABCD 13 5 29][DABC  2 9 30][CDAB  7 14 31][BCDA 12 20 32]
	round(&md5.A, md5.B, md5.C, md5.D, block[13],  5, 0xa9e3e905, G)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 2],  9, 0xfcefa3f8, G)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 7], 14, 0x676f02d9, G)
	round(&md5.B, md5.C, md5.D, md5.A, block[12], 20, 0x8d2a4c8a, G)

	// ROUND 3 [abcd k s i] a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s)
	// [ABCD  5 4 33][DABC  8 11 34][CDAB 11 16 35][BCDA 14 23 36]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 5],  4, 0xfffa3942, H)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 8], 11, 0x8771f681, H)
	round(&md5.C, md5.D, md5.A, md5.B, block[11], 16, 0x6d9d6122, H)
	round(&md5.B, md5.C, md5.D, md5.A, block[14], 23, 0xfde5380c, H)

	// [ABCD  1 4 37][DABC  4 11 38][CDAB  7 16 39][BCDA 10 23 40]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 1],  4, 0xa4beea44, H)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 4], 11, 0x4bdecfa9, H)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 7], 16, 0xf6bb4b60, H)
	round(&md5.B, md5.C, md5.D, md5.A, block[10], 23, 0xbebfbc70, H)

	// [ABCD 13 4 41][DABC  0 11 42][CDAB  3 16 43][BCDA  6 23 44]
	round(&md5.A, md5.B, md5.C, md5.D, block[13],  4, 0x289b7ec6, H)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 0], 11, 0xeaa127fa, H)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 3], 16, 0xd4ef3085, H)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 6], 23, 0x04881d05, H)

	// [ABCD  9 4 45][DABC 12 11 46][CDAB 15 16 47][BCDA  2 23 48]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 9],  4, 0xd9d4d039, H)
	round(&md5.D, md5.A, md5.B, md5.C, block[12], 11, 0xe6db99e5, H)
	round(&md5.C, md5.D, md5.A, md5.B, block[15], 16, 0x1fa27cf8, H)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 2], 23, 0xc4ac5665, H)

	// ROUND 4 [abcd k s i] a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s)
	// [ABCD  0 6 49][DABC  7 10 50][CDAB 14 15 51][BCDA  5 21 52]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 0],  6, 0xf4292244, I)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 7], 10, 0x432aff97, I)
	round(&md5.C, md5.D, md5.A, md5.B, block[14], 15, 0xab9423a7, I)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 5], 21, 0xfc93a039, I)

	// [ABCD 12 6 53][DABC  3 10 54][CDAB 10 15 55][BCDA  1 21 56]
	round(&md5.A, md5.B, md5.C, md5.D, block[12],  6, 0x655b59c3, I)
	round(&md5.D, md5.A, md5.B, md5.C, block[ 3], 10, 0x8f0ccc92, I)
	round(&md5.C, md5.D, md5.A, md5.B, block[10], 15, 0xffeff47d, I)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 1], 21, 0x85845dd1, I)

	// [ABCD  8 6 57][DABC 15 10 58][CDAB  6 15 59][BCDA 13 21 60]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 8],  6, 0x6fa87e4f, I)
	round(&md5.D, md5.A, md5.B, md5.C, block[15], 10, 0xfe2ce6e0, I)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 6], 15, 0xa3014314, I)
	round(&md5.B, md5.C, md5.D, md5.A, block[13], 21, 0x4e0811a1, I)

	// [ABCD  4 6 61][DABC 11 10 62][CDAB  2 15 63][BCDA  9 21 64]
	round(&md5.A, md5.B, md5.C, md5.D, block[ 4],  6, 0xf7537e82, I)
	round(&md5.D, md5.A, md5.B, md5.C, block[11], 10, 0xbd3af235, I)
	round(&md5.C, md5.D, md5.A, md5.B, block[ 2], 15, 0x2ad7d2bb, I)
	round(&md5.B, md5.C, md5.D, md5.A, block[ 9], 21, 0xeb86d391, I)

	md5.A += AA
	md5.B += BB
	md5.C += CC
	md5.D += DD
}

func (md5 *md5) process(data[]byte) {
	if md5.pos > 0 {
		n := int(BLOCK_SIZE - md5.pos)
		if n > len(data) {
			n = len(data)
		}
		for i:=0; i<n; i++ {
			md5.buf[md5.pos] = data[i]
			md5.pos++
		}
		data = data[n:]

		if md5.pos == BLOCK_SIZE {
			md5.process_block(md5.buf[:])
			md5.pos = 0
			md5.size += BLOCK_SIZE
		}
	}
	for len(data) >= BLOCK_SIZE {
		md5.process_block(data)
		md5.size += BLOCK_SIZE
		data = data[BLOCK_SIZE:]
	}
	for i:=0; i<len(data); i++ {
		md5.buf[md5.pos] = data[i]
		md5.pos++
	}
}

func (md5 *md5) finish() {
	md5.size += uint64(md5.pos)
	md5.size <<= 3 // size should be in BITS, not in BYTES

	md5.buf[md5.pos] = 0x80
	md5.pos++
	if md5.pos > 56 {
		for md5.pos < BLOCK_SIZE {
			md5.buf[md5.pos] = 0x00
			md5.pos++
		}
		md5.process_block(md5.buf[:])
		md5.pos = 0
	}
	for md5.pos < 56 {
		md5.buf[md5.pos] = 0x00
		md5.pos++
	}
	md5.buf[md5.pos] = byte(md5.size)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>8)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>16)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>24)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>32)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>40)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>48)
	md5.pos++
	md5.buf[md5.pos] = byte(md5.size>>56)
	md5.pos++
	md5.process_block(md5.buf[:])
}

func (md5 *md5) String() string {
	return fmt.Sprintf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		byte(md5.A), byte(md5.A>>8), byte(md5.A>>16), byte(md5.A>>24),
		byte(md5.B), byte(md5.B>>8), byte(md5.B>>16), byte(md5.B>>24),
		byte(md5.C), byte(md5.C>>8), byte(md5.C>>16), byte(md5.C>>24),
		byte(md5.D), byte(md5.D>>8), byte(md5.D>>16), byte(md5.D>>24))
}

func main() {
	for _,fname := range os.Args[1:] {
		md5file(fname)
	}

}

func md5file(fname string) {
	file, err := os.Open(fname)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Can't open %s: %s\n", fname, err)
		return
	}
	defer file.Close()

	m := New()

	buf := make([]byte, 4096)
	for {
		n,e := file.Read(buf)
		if n == 0 && e == io.EOF {
			break
		}
		if e != nil {
			panic(e)
		}
		m.process(buf[:n])
	}
	m.finish()

	fmt.Printf("%s  %s\n", m, fname)
}
