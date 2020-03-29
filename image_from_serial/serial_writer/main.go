package main

import (
	"fmt"
	"image"
	"image/color"
	"io"
	"log"
	"os"
	"strings"
	"time"

	"github.com/jacobsa/go-serial/serial"
	"golang.org/x/image/bmp"
)

func main() {

	// Set up options.
	options := serial.OpenOptions{
		PortName:              "/dev/cu.usbserial-1410",
		BaudRate:              9600,
		DataBits:              8,
		StopBits:              1,
		MinimumReadSize:       1,
		InterCharacterTimeout: 200,
	}

	// Open the port.
	port, err := serial.Open(options)
	if err != nil {
		log.Fatalf("serial.Open: %v", err)
	}

	// Make sure to close it later.
	defer port.Close()

	file, err := os.Open("woof.bmp")
	// file, err := os.Open("IMAGE658.BMP")
	if err != nil {
		panic(err)
	}
	defer file.Close()
	bmpImage, err := bmp.Decode(file)
	if err != nil {
		panic(err)
	}

	// go lineReader(port)

	// time.Sleep(time.Second * 3)
	output := make([]byte, 1)
	timer := time.NewTimer(time.Second * 10)
	interrupted := false
	for !interrupted {
		select {
		case <-timer.C:
			fmt.Println("Timeout for connect. Start transfering...")
			interrupted = true
			break
		default:
			n, err := port.Read(output)
			if err != nil {
				log.Fatalf("port.Write: %v", err)
			}
			if n > 0 && output[0] == 255 {
				interrupted = true
				fmt.Println("Start transfering...")
			}
			// fmt.Printf("Waiting for start %v, out len %v, %s \n", time.Now().Second(), n, output)
			time.Sleep(time.Second)
		}
	}
	startTime := time.Now()
	// go lineReader(port)
	var actionType byte = 8
	// _, err = port.Write([]byte{actionType})
	// if err != nil {
	// 	log.Fatalf("port.Write: %v", err)
	// }
	fmt.Println("Image size", bmpImage.Bounds().Size())

	if actionType == 8 {
		writeByPixel8(bmpImage, port)
	} else if actionType == 7 {
		writeByPixel(bmpImage, port)
	} else {
		log.Fatal("invalid action type")
	}

	fmt.Println("It taked ", time.Since(startTime).Milliseconds(), "ms")
	time.Sleep(time.Second)

}

func writeByPixel8(bmpImage image.Image, port io.ReadWriteCloser) {
	size := bmpImage.Bounds().Size()
	for y := 0; y < size.Y; y++ {
		rgbBytes := make([]byte, 242)
		rgbBytes[0] = 254
		if y > 255 {
			rgbBytes[0] = 255
		}
		rgbBytes[1] = byte(y % 256)
		// rgbBytes = append(rgbBytes, byte(y>>8), byte(y))

		for x := 0; x < size.X; x++ {
			rgb := bmpImage.At(x, y).(color.RGBA)
			rgbBytes[x+2] = rgbTo8bit(rgb)
		}
		_, err := port.Write(rgbBytes)
		if err != nil {
			log.Fatalf("port.Write: %v", err)
		}
	}
}

func writeByPixel8_chunk(bmpImage image.Image, port io.ReadWriteCloser) {
	size := bmpImage.Bounds().Size()
	for y := 0; y < size.Y; y++ {
		rgbBytes := make([]byte, 242)
		rgbBytes[0] = 254
		if y > 255 {
			rgbBytes[0] = 255
		}
		rgbBytes[1] = byte(y % 256)
		// rgbBytes = append(rgbBytes, byte(y>>8), byte(y))

		for x := 0; x < size.X; x++ {
			rgb := bmpImage.At(x, y).(color.RGBA)
			rgbBytes[x+2] = rgbTo8bit(rgb)
		}
		_, err := port.Write(rgbBytes)
		if err != nil {
			log.Fatalf("port.Write: %v", err)
		}
	}
}

func writeByPixel(bmpImage image.Image, port io.ReadWriteCloser) {
	size := bmpImage.Bounds().Size()
	for y := 0; y < size.Y; y++ {
		for x := 0; x < size.X; x++ {

			rgb := bmpImage.At(x, y).(color.RGBA)
			rgbBytes := []byte{
				255,          // event
				byte(x >> 8), // x
				byte(x),
				byte(y >> 8), // y
				byte(y),
				rgb.R, rgb.G, rgb.B, // color
			}
			_, err := port.Write(rgbBytes)
			if err != nil {
				log.Fatalf("port.Write: %v", err)
			}
			continue
			var line = make([]byte, 24)
			n, err := port.Read(line)
			if err != nil {
				if strings.Contains(err.Error(), "file already closed") {
					break
				}
				fmt.Println(err)
			}
			if n == 0 {
				continue
			}
			fmt.Printf("%s == %d %d %d %d\n", line[:n], rgb.R, rgb.G, rgb.B, rgbTo8bit(rgb))
		}
	}
}

func lineReader(reader io.Reader) {
	for {
		var line = make([]byte, 17)
		n, err := reader.Read(line)
		if err != nil {
			if strings.Contains(err.Error(), "file already closed") {
				break
			}
			fmt.Println(err)
		}
		if n == 0 {
			continue
		}
		fmt.Printf("%s\n", line[:n])
		time.Sleep(time.Millisecond * 10)
	}
}

func rgbTo8bit(orig color.RGBA) uint8 {
	return (((orig.R / 31) << 5) & 0b1110_0000) | (((orig.G / 31) << 2) & 0b0001_1100) | ((orig.B / 63) & 0b0000_0011)
}

func rgb(pixel color.Color) (r uint32, g uint32, b uint32) {
	r, g, b, _ = pixel.RGBA()
	return
}

// ToRGB565 coverter.
func ToRGB565(r, g, b uint32) uint32 {
	return ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3)
}

//
//
