package main

import (
	"context"
	"flag"
	"fmt"
	"havcebin/filesystem"
	"havcebin/http"
	"havcebin/http/html"
	"log"
	"os"
	"os/signal"
	"os/user"
	"path/filepath"
	"strings"
)

func main() {
	// Setup signal handler. We want to call Done() when os.Interrupt (i.e. Ctrl+c)
	// arrives.
	ctx, _ := signal.NotifyContext(context.Background(), os.Interrupt)

	m := NewMain()

	// Parse command line flags.
	if err := m.ParseFlags(ctx, os.Args[1:]); err == flag.ErrHelp {
		os.Exit(1)
	} else if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	// Execute program.
	if err := m.Run(ctx); err != nil {
		m.Close()
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	// Wait for CTRL-C.
	<-ctx.Done()

	// Clean up program.
	if err := m.Close(); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

type Main struct {
	Config     Config
	HTTPServer *http.Server
}

func NewMain() *Main {
	return &Main{
		HTTPServer: http.NewServer(),
	}
}

// Run executes the program. The configuration should already be set up before
// calling this function.
func (m *Main) Run(ctx context.Context) (err error) {
	// Instantiate filesystem-backed services.
	pasteService := filesystem.NewPasteService(m.Config.SaveDirectory)

	// Copy configuration settings to the HTTP server.
	m.HTTPServer.Addr = m.Config.ListenAddress

	// Attach underlying services to the HTTP server.
	m.HTTPServer.PasteService = pasteService

	// Get template for displaying paste.
	tmpl, err := html.GetCodeTemplate()
	if err != nil {
		return nil
	}

	m.HTTPServer.CodeTemplate = tmpl

	// Start the HTTP server.
	if err := m.HTTPServer.Open(); err != nil {
		return err
	}

	log.Printf("running: url=%q", m.HTTPServer.URL())

	return nil
}
func (m *Main) Close() error {
	if m.HTTPServer != nil {
		if err := m.HTTPServer.Close(); err != nil {
			return err
		}
	}
	return nil
}

type Config struct {
	// The HTTP listen address, default 0.0.0.0:8080.
	ListenAddress string
	// The location where the pastebins sill be saved.
	SaveDirectory string
}

// ParseFlags parses the command line arguments.
func (m *Main) ParseFlags(ctx context.Context, args []string) error {

	// Our flag set is very simple. It only includes a config path.
	fs := flag.NewFlagSet("havcebind", flag.ContinueOnError)
	fs.StringVar(&m.Config.ListenAddress, "listen", ":8080", "listen address")
	fs.StringVar(&m.Config.SaveDirectory, "save-dir", "./code", "save directory")
	err := fs.Parse(args)
	if err != nil {
		return err
	}

	// The expand() function is here to automatically expand "~" to the user's
	// home directory.
	m.Config.SaveDirectory, err = expand(m.Config.SaveDirectory)
	if err != nil {
		return err
	}

	return nil
}

// expand returns path using tilde expansion. This means that a file path that
// begins with the "~" will be expanded to prefix the user's home directory.
func expand(path string) (string, error) {
	// Ignore if path has no leading tilde.
	if path != "~" && !strings.HasPrefix(path, "~"+string(os.PathSeparator)) {
		return path, nil
	}

	// Fetch the current user to determine the home path.
	u, err := user.Current()
	if err != nil {
		return path, err
	} else if u.HomeDir == "" {
		return path, fmt.Errorf("home directory unset")
	}

	if path == "~" {
		return u.HomeDir, nil
	}
	return filepath.Join(u.HomeDir, strings.TrimPrefix(path, "~"+string(os.PathSeparator))), nil
}