package http

import (
	"context"
	"fmt"
	"havcebin"
	"havcebin/http/html"
	"html/template"
	"net"
	"net/http"
	"time"

	"github.com/go-chi/chi/v5"
)

const ShutdownTimeout = time.Second * 5

type Server struct {
	ln     net.Listener
	server *http.Server
	router chi.Router

	// Bind address & domain for the server's listener.
	Addr string

	// Services used by the HTTP routes.
	PasteService havcebin.PasteService

	// Templates
	CodeTemplate *template.Template
}

func NewServer() *Server {
	s := &Server{
		server: &http.Server{},
		router: chi.NewRouter(),
	}

	s.router.Get("/", s.handleIndex)
	s.router.Get("/paste", s.handlePasteGet)
	s.router.Post("/paste", s.handlePastePost)

	s.server.Handler = s.router

	return s
}

func (s *Server) handleIndex(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte(html.GetIndex()))
}

// Port returns the TCP port for the running server.
// This is useful in tests where we allocate a random port by using ":0".
func (s *Server) Port() int {
	if s.ln == nil {
		return 0
	}
	return s.ln.Addr().(*net.TCPAddr).Port
}

// URL returns the local base URL of the running server.
func (s *Server) URL() string {
	port := s.Port()

	domain := "localhost"

	// Return without port if using standard ports.
	if port == 80 {
		return fmt.Sprintf("http://%s", domain)
	}
	return fmt.Sprintf("http://%s:%d", domain, s.Port())
}

// Open validates the server options and begins listening on the bind address.
func (s *Server) Open() (err error) {
	if s.ln, err = net.Listen("tcp", s.Addr); err != nil {
		return err
	}

	// Begin serving requests on the listener. We use Serve() instead of
	// ListenAndServe() because it allows us to check for listen errors (such
	// as trying to use an already open port) synchronously.
	go s.server.Serve(s.ln)

	return nil
}

// Close gracefully shuts down the server.
func (s *Server) Close() error {
	ctx, cancel := context.WithTimeout(context.Background(), ShutdownTimeout)
	defer cancel()
	return s.server.Shutdown(ctx)
}