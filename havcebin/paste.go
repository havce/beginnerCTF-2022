package havcebin

import "context"

type Paste struct {
	Name    string
	Content string
}

type PasteService interface {
	SavePaste(ctx context.Context, name string, content string) error
	LoadPaste(ctx context.Context, name string) (string, error)
}
