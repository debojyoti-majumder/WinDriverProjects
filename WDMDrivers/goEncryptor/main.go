package main

import (
	"fmt"
	"os"
)

func processFile(filePath string) {
	fmt.Println("Processing files")
}

func processFolders(folderPath string) {
	fmt.Println("Processing the folder")
}

func main() {
	// Basic command line checking
	argCount := len(os.Args)

	if argCount < 1 {
		fmt.Println("Invalid usage")
		return
	} else if argCount == 3 {
		// Some verbose output
		keyName := os.Args[1]
		entityName := os.Args[2]
		fmt.Println("Encrypt Using key", keyName)
		fmt.Println("On entity:", entityName)

		fileInformation, err := os.Stat(entityName)
		if err == nil {
			if fileInformation.IsDir() {
				// Processing the folder
				processFolders(entityName)
			} else {
				processFile(entityName)
			}
		}
	} else if argCount == 2 {
		fmt.Println("Decrypt file content")
	}
}
