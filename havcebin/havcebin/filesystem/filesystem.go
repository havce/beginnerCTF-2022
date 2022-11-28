package filesystem

import (
	"context"
	"havcebin"
	"os"
	"path"
)

// Ensure PasteService implements interface.
var _ havcebin.PasteService = (*PasteService)(nil)

type PasteService struct {
	BasePath string
}

func NewPasteService(base string) *PasteService {
	return &PasteService{
		BasePath: base,
	}
}

func (p *PasteService) LoadPaste(ctx context.Context, name string) (string, error) {
	// Sanitize name.
	name = sanitizeName(name)

	sanePath := path.Join(p.BasePath, path.Clean(name))

	paste, err := os.ReadFile(sanePath)
	if err != nil {
		return "", err
	}

	return string(paste), nil
}

func (p *PasteService) SavePaste(ctx context.Context, name string, content string) error {
	// Sanitize name.
	name = sanitizeName(name)

	sanePath := path.Join(p.BasePath, path.Clean(name))

	// We don't want other users to read our precious files.
	return os.WriteFile(sanePath, []byte(content), 0600)
}