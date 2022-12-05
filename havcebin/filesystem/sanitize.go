package filesystem

import "strings"

// sanitizeName removes suspect chars.
func sanitizeName(name string) string {
	name = strings.ReplaceAll(name, "$", "")
	name = strings.ReplaceAll(name, ";", "")
	name = strings.ReplaceAll(name, "{", "")
	name = strings.ReplaceAll(name, "}", "")
	name = strings.ReplaceAll(name, "\"", "")
	return strings.ReplaceAll(name, "../", "")
}
