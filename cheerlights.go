package main

import (
	"github.com/huin/goserial"
	"io/ioutil"
	"log"
	"net/http"
	"time"
)

func get_colour() (string, error) {
	colours := map[string]string{
		"red":       "255000000",
		"green":     "000255000",
		"blue":      "000000255",
		"cyan":      "000255255",
		"purple":    "128000128",
		"magenta":   "255000255",
		"yellow":    "255255000",
		"orange":    "255165000",
		"warmwhite": "255233233",
		"white":     "255255255",
		"black":     "000000000",
	}
	url := "http://api.thingspeak.com/channels/1417/field/1/last.txt"
	resp, err := http.Get(url)
	if err != nil {
		log.Printf("Failed to fetch the message")
		log.Printf("%v", err)
		return "", err
	}
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Printf("%v", err)
		return "", err
	}
	log.Printf("%v", body)
	intColour, ok := colours[string(body)]
	if !ok {
		log.Printf("No colour match")
		return "", err
	}
	log.Printf("%v", intColour)
	defer resp.Body.Close()
	return intColour, nil
}

func main() {
	c := &goserial.Config{Name: "/dev/ttyUSB0", Baud: 9600}
	s, _ := goserial.OpenPort(c)
	//defer s.Close()
	oldColour := ""
	for {
		colour, err := get_colour()
		colour = "000000000"
		if err == nil && colour != oldColour {
			s.Write([]byte(colour))
			time.Sleep(10 * time.Second)
			oldColour = colour
		}
	}
}
