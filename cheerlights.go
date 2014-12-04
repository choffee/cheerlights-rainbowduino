package main

import (
    "net/http"
    "log"
    "io/ioutil"
    "github.com/huin/goserial"
    "time"
)



func get_colour () string {
    colours := map[string]string{
        "magenta": "255255255",
    }
    url := "http://api.thingspeak.com/channels/1417/field/1/last.txt"
    resp, err := http.Get(url)
    if err != nil {
        log.Printf("Failed to fetch the message")
        log.Printf("%v", err)
    }
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        log.Printf("%v", err)
    }
    log.Printf("%v", body)
    intColour, ok := colours[string(body)]
    if !ok  {
        log.Printf("No colour match")
    }
    log.Printf("%q", intColour)
    defer resp.Body.Close()
    return intColour
}

func main () {
    c := &goserial.Config{Name: "/dev/ttyUSB0", Baud: 9600}
    s, _ := goserial.OpenPort(c)
    oldColour := ""
    for {
        colour := get_colour()
        if colour != oldColour {
            s.Write([]byte(colour))
            time.Sleep(10 * time.Second)
            oldColour = colour
        }
    }
}

