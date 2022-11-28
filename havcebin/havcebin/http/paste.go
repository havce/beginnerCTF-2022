package http

import (
	"havcebin/generate"
	"log"
	"net/http"
)

func (s *Server) handlePasteGet(w http.ResponseWriter, r *http.Request) {
	if err := r.ParseForm(); err != nil {
		http.Error(w, "There was an error parsing your request.", http.StatusBadRequest)
		return
	}

	if !r.Form.Has("key") {
		http.Error(w, "Missing 'key' parameter.", http.StatusBadRequest)
		return
	}

	key := r.Form.Get("key")
	if key == "" {
		http.Error(w, "Key must not be empty.", http.StatusBadRequest)
		return
	}

	code, err := s.PasteService.LoadPaste(r.Context(), key)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	if r.Form.Has("raw") {
		w.Write([]byte(code))
		return
	}

	if err := s.CodeTemplate.Execute(w, struct{ Code string }{code}); err != nil {
		http.Error(w, "Failed to render template.", http.StatusInternalServerError)
	}
}

func (s *Server) handlePastePost(w http.ResponseWriter, r *http.Request) {
	if err := r.ParseForm(); err != nil {
		http.Error(w, "There was an error parsing you request.", http.StatusBadRequest)
		return
	}

	code := r.Form.Get("code")
	if code == "" {
		http.Error(w, "The paste content cannot be empty.", http.StatusBadRequest)
		return
	}

	name, err := generate.StringFromAlphabet(8, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
	if err != nil {
		http.Error(w, "There was an error generating a random name for your paste.", http.StatusInternalServerError)
		log.Println(err)
		return
	}

	if err := s.PasteService.SavePaste(r.Context(), name, code); err != nil {
		http.Error(w, "There was an error saving your paste.", http.StatusInternalServerError)
		log.Println(err)
		return
	}

	http.Redirect(w, r, "/paste?key="+name, http.StatusFound)
}
