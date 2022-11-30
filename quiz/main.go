package main

import (
	"context"
	"crypto/rand"
	"errors"
	"fmt"
	"log"
	"math/big"
	"net"
	"os"
	"os/signal"
	"sync"
	"time"
)

type Server struct {
	ln net.Listener

	quit chan struct{}
	wg   sync.WaitGroup
}

func NewServer(ln net.Listener) *Server {
	return &Server{ln: ln, quit: make(chan struct{})}
}

func (s *Server) Serve() {
	s.wg.Add(1)
	go s.serve()
}

func Run(ctx context.Context) error {
	ln, err := net.Listen("tcp4", ":1337")
	if err != nil {
		return err
	}

	s := NewServer(ln)
	s.Serve()
	fmt.Println("Listening on :1337")

	<-ctx.Done()
	s.Close()
	return nil
}

func (s *Server) Close() {
	close(s.quit)
	s.ln.Close()
	s.wg.Wait()
}

func (s *Server) serve() {
	defer s.wg.Done()

	for {
		conn, err := s.ln.Accept()
		if err != nil {
			select {
			case <-s.quit:
				return
			default:
				log.Println("accept error", err)
			}
		} else {
			s.wg.Add(1)
			conn.SetDeadline(time.Now().Add(time.Second * 5))
			go func() {
				if err := s.handleConnection(conn); errors.Is(err, os.ErrDeadlineExceeded) {
					conn.SetDeadline(time.Now().Add(time.Second * 3))
					if _, err := fmt.Fprintln(conn, "Time's up! Please retry another time."); err != nil {
						log.Println(err)
					}
				} else if err != nil {
					log.Println(err)
				}
				conn.Close()
				s.wg.Done()
			}()
		}
	}
}

func generateBigInt() (*big.Int, error) {
	// Max value, a 130-bits integer, i.e 2^130 - 1
	var max *big.Int = big.NewInt(0).Exp(big.NewInt(2), big.NewInt(230), nil)
	// Generate cryptographically strong pseudo-random between [0, max)
	n, err := rand.Int(rand.Reader, max)
	if err != nil {
		return nil, err
	}

	return n, nil
}

func randomOperation() string {
	ops := []string{"+", "-", "*"}
	return ops[time.Now().UnixMicro()%3]
}

func (s *Server) handleConnection(c net.Conn) error {
	_, err := fmt.Fprintln(c, `
                    $$\           
                    \__|          
 $$$$$$\  $$\   $$\ $$\ $$$$$$$$\ 
$$  __$$\ $$ |  $$ |$$ |\____$$  |
$$ /  $$ |$$ |  $$ |$$ |  $$$$ _/ 
$$ |  $$ |$$ |  $$ |$$ | $$  _/   
\$$$$$$$ |\$$$$$$  |$$ |$$$$$$$$\ 
 \____$$ | \______/ \__|\________|
      $$ |                        
      $$ |                        
      \__|                        


		`)
	if err != nil {
		return err
	}
	_, err = fmt.Fprintln(c, `Hello wanderer! Welcome to the havce quiz.
You will be asked 50 questions on basic math.
You must answer in less than 5 seconds to win a juicy prize.
Let's start!`)
	if err != nil {
		return err
	}

	for i := 0; i < 50; i++ {
		a, err := generateBigInt()
		if err != nil {
			fmt.Fprintln(c, "ooooopsie, there was an error generating your numbers. quitting.")
			return err
		}

		b, err := generateBigInt()
		if err != nil {
			fmt.Fprintln(c, "ooooopsie, there was an error generating your numbers. quitting.")
			return err
		}

		op := randomOperation()
		var result *big.Int

		switch op {
		case "+":
			result = big.NewInt(0).Add(a, b)
		case "-":
			result = big.NewInt(0).Sub(a, b)
		case "*":
			result = big.NewInt(0).Mul(a, b)
		}

		if _, err := fmt.Fprintf(c, "Please submit %v %s %v\n> ", a, op, b); err != nil {
			return err
		}

		var user string
		if _, err := fmt.Fscanln(c, &user); err != nil {
			return err
		}

		i := big.NewInt(0)
		i.SetString(user, 10)

		if i.Cmp(result) != 0 {
			fmt.Fprintf(c, "Nope, you lost! The correct answer was: %v. Please retry another time.\n", result)
			return fmt.Errorf("user lost")
		}

		if _, err := fmt.Fprintln(c, "Good job!"); err != nil {
			return err
		}
	}

	flag := os.Getenv("flag")

	if _, err := fmt.Fprintf(c, "You won! Congrats, here's your flag: %s.", flag); err != nil {
		return err
	}

	return nil
}

func main() {
	ctx, _ := signal.NotifyContext(context.Background(), os.Interrupt)

	if err := Run(ctx); err != nil {
		fmt.Fprintf(os.Stderr, "error: %v", err)
		os.Exit(1)
	}
}
