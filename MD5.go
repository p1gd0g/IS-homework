//teat data taken from https://zh.scribd.com/doc/35954574/MD5-With-Example
//uploaded to https://github.com/p1gd0g/IS-homework
//written in golang
package main

import (
	"fmt"
)

func show(k [4]uint8) {
	fmt.Println(uint32(k[0])<<24 + uint32(k[1])<<16 + uint32(k[2])<<8 + uint32(k[3]))
}

func lenn(k [1111]uint8) int {
	var i int
	for i = 0; k[i] != 0; i++ {
	}
	return i
}

func pad(k [1111]uint8) [1111]uint8 {
	n := lenn(k)
	n_temp := n % 64
	n_bit := n * 8

	if n_temp >= 56 {
		k[n] = 128
		n_temp++
		for i := 0; i < 64-n_temp+56; i++ {
			k[n+i+1] = 0
		}
		for i := 0; i < 8; i++ {
			temp := uint(n_bit) >> (uint(i) * 8)
			k[n+64-n_temp+56+i] = uint8(temp)
		}
	} else {
		k[n] = 128
		n_temp++
		for i := 0; i < 56-n_temp; i++ {
			k[n+i+1] = 0
		}
		for i := 0; i < 8; i++ {
			temp := uint(n_bit) >> (uint(i) * 8)
			k[n+56-n_temp+i+1] = uint8(temp)
		}
	}
	for i := 0; i*4+3 < len(k); i++ {
		k[i*4], k[i*4+1], k[i*4+2], k[i*4+3] = k[i*4+3], k[i*4+2], k[i*4+1], k[i*4]
		//fmt.Println(i)
	}
	return k
}

func g(b, c, d [4]uint8, k int) (temp [4]uint8) {
	switch k {
	case 1:
		for i := 0; i < 4; i++ {
			temp[i] = (b[i] & c[i]) | (^b[i] & d[i])
		}
		//fmt.Println(temp[0]<<24 + temp[1]<<16 + temp[2]<<8 + temp[3])
	case 2:
		for i := 0; i < 4; i++ {
			temp[i] = (b[i] & d[i]) | (c[i] & ^d[i])
		}
		//fmt.Println(temp[0]<<24 + temp[1]<<16 + temp[2]<<8 + temp[3])
	case 3:
		for i := 0; i < 4; i++ {
			temp[i] = b[i] ^ c[i] ^ d[i]
		}
	case 4:
		for i := 0; i < 4; i++ {
			temp[i] = c[i] ^ (b[i] | ^d[i])
		}
		//fmt.Println("-", temp)
		//show(temp)
		//show(b)
		//show(c)
		//show(d)
	}
	return
}

func mod44(a, b [4]uint8) (sum [4]uint8) {
	var sum1, sum2 uint32 = 0, 0
	for i := 0; i < 4; i++ {
		sum1 += uint32(a[i])
		sum2 += uint32(b[i])
		if i < 3 {
			sum1 = sum1 << 8
			sum2 = sum2 << 8
		}
	}
	sum1 += sum2
	sum[3] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[2] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[1] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[0] = uint8(sum1)
	return sum
}

func mod41(a [4]uint8, sum2 uint32) (sum [4]uint8) {
	var sum1 uint32 = 0
	for i := 0; i < 4; i++ {
		sum1 += uint32(a[i])
		if i < 3 {
			sum1 = sum1 << 8
		}
	}
	sum1 += sum2
	sum[3] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[2] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[1] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[0] = uint8(sum1)
	return sum
}

func cls(a [4]uint8, k int, i int) (sum [4]uint8) {
	s := []uint8{
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}
	temp := s[(k-1)*16+i]
	var sum1 uint32 = 0
	for i := 0; i < 4; i++ {
		sum1 += uint32(a[i])
		if i < 3 {
			sum1 = sum1 << 8
		}
	}
	sum2 := sum1
	sum1 = sum1 << temp
	sum2 = sum2 >> (32 - temp)
	sum1 += sum2
	sum[3] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[2] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[1] = uint8(sum1)
	sum1 = sum1 >> 8
	sum[0] = uint8(sum1)
	return sum
}

func F(a, b, c, d [4]uint8, s []uint8, k int) ([4]uint8, [4]uint8, [4]uint8, [4]uint8) {
	T := []uint32{
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
		0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
		0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51,
		0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905,
		0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
		0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
		0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
		0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
		0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314,
		0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391}
	//fmt.Println(s)
	for i := 0; i < 16; i++ {
		temp := g(b, c, d, k)
		//show(a)
		//show(temp)
		a = mod44(a, temp)
		//show(a)
		for j := 0; j < 4; j++ {
			switch k {
			case 1:
				temp[j] = s[i*4+j]
				//fmt.Println(temp[j])
			case 2:
				ii := (1 + 5*i) % 16
				temp[j] = s[ii*4+j]
			case 3:
				ii := (5 + 3*i) % 16
				temp[j] = s[ii*4+j]
			case 4:
				ii := (7 * i) % 16
				temp[j] = s[ii*4+j]
			}
		}
		//fmt.Println(i)
		//show(temp)
		a = mod44(a, temp)
		//fmt.Println(T[16*(k-1)+i])
		a = mod41(a, T[16*(k-1)+i])
		//show(a)
		a = cls(a, k, i)
		//show(a)
		a = mod44(a, b)
		//show(a)
		a, b, c, d = d, a, b, c
		//fmt.Println("-")
		//show(a)
		//show(b)
		//show(c)
		//show(d)
	}
	return a, b, c, d
}

func HMD5(a, b, c, d [4]uint8, s []uint8) ([4]uint8, [4]uint8, [4]uint8, [4]uint8) {
	A, B, C, D := a, b, c, d
	for k := 1; k < 5; k++ {
		a, b, c, d = F(a, b, c, d, s, k)
	}
	a, b, c, d = mod44(a, A), mod44(b, B), mod44(c, C), mod44(d, D)
	return a, b, c, d
}

func MD5(k string) ([4]uint8, [4]uint8, [4]uint8, [4]uint8) {
	var k_uint8 [1111]uint8
	for i := 0; i < len(k); i++ {
		k_uint8[i] = uint8(k[i])
	}
	n := lenn(k_uint8)
	if n%64 >= 56 {
		n = n/64 + 2
	} else {
		n = n/64 + 1
	}

	k_uint8 = pad(k_uint8)
	//fmt.Println(k_uint8)
	a := [4]uint8{0x67, 0x45, 0x23, 0x01} //8bit*4=32bit
	b := [4]uint8{0xef, 0xcd, 0xab, 0x89}
	c := [4]uint8{0x98, 0xba, 0xdc, 0xfe}
	d := [4]uint8{0x10, 0x32, 0x54, 0x76}
	for i := 0; i < n; i++ {
		s := k_uint8[i*64 : i*64+64]
		a, b, c, d = HMD5(a, b, c, d, s)
	}
	return a, b, c, d
}

func main() {

	//k1 := "Hello World!"
	k1 := "ShenzhenUniversity"
	k2 := "ShenZhenUniversity"
	fmt.Println(k1)
	a, b, c, d := MD5(k1)
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", a[3-i])
	}
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", b[3-i])
	}
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", c[3-i])
	}
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", d[3-i])
	}
	fmt.Println()
	fmt.Println(k2)
	a, b, c, d = MD5(k2)
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", a[3-i])
	}
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", b[3-i])
	}
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", c[3-i])
	}
	for i := 0; i < 4; i++ {
		fmt.Printf("%.2X", d[3-i])
	}
	fmt.Println()
}
