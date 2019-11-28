package main

import (
	"fmt"
	"os"
)

func main() {
	// Basic command line checking
	argCount := len(os.Args)
	if argCount < 3 {
		fmt.Println("Invalid usage")
		return
	}

	// Some verbose output
	keyName := os.Args[1]
	entityName := os.Args[2]
	fmt.Println("Using key", keyName)
	fmt.Println("On entity:", entityName)
}
