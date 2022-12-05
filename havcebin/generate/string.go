package generate

import (
	"strings"
)

// StringFromAlphabet generates a n-length string from an alphabet
// using the system's secure random number generator.
func StringFromAlphabet(n int, alphabet string) (string, error) {
	arune := []rune(alphabet)

	bytes, err := RandomBytes(n)
	if err != nil {
		return "", err
	}

	var out strings.Builder

	for _, b := range bytes {
		out.WriteRune(arune[int(b)%len(arune)])
	}

	return out.String(), nil
}
