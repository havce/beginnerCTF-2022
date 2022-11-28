package html

import (
	_ "embed"
	"html/template"
)

//go:embed index.html
var indexPage string

//go:embed code.html
var codePage string

func GetIndex() string {
	return indexPage
}

func GetCodeTemplate() (*template.Template, error) {
	return template.New("code").Parse(codePage)
}
