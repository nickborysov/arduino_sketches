package main

import (
	"fmt"
	"image/color"
	"testing"

	"gotest.tools/assert"
)

func Test_rgbTo8bit(t *testing.T) {
	var i uint8
	for i = 0; i < 255; i++ {
		r, g, b := the8bitToRGB(i)
		color := rgbTo8bit(color.RGBA{r, g, b, 0})
		// fmt.Printf("%d, %d, %d, ", r, g, b)
		assert.Equal(t, uint8(i), color)
	}
}

func Test_rr(t *testing.T) {
	// fmt.Println(the8bitToRGB(105))
	fmt.Println((255&0x1)<<8 | 0)
}

func the8bitToRGB(value uint8) (r uint8, g uint8, b uint8) {
	r = (((value & 0b11100000) >> 5) & 0b00000111) * 31
	g = (((value & 0b00011100) >> 2) & 0b00000111) * 31
	b = (value & 0b00000011) * 63

	return
}
