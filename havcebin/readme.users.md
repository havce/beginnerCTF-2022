# havcebin
Welcome to my Pastebin clone. It is written in Go, and I hope you'll like it.
I coded it defensively, using all the bells and whistles to make sure hackers
don't end up stealing files they shouldn't see.

## Contribute
In order to build havcebin you have two choices:
 - Use Docker.
 - Install the Go tooling.

Make sure to check the Dockerfile to see how things work behind the curtains! 😉

### Option 1: use Docker
Make sure you have [Docker](https://docs.docker.com/get-docker/) installed on your system.
Then, open a terminal and type the following:
```bash
cd havcebin
docker build -t havcebin .
docker run -d -eFLAG="havceCTF{this_is_a_dummy_flag}" -p8080:8080 havcebin
# You're set! Go to your browser on http://localhost:8080
```

### Option 2: use the Go tooling
Make sure you have Go installed on your system. Check the [installation instructions](https://go.dev/doc/install) for your operating system.
After that type the following:
```bash
cd havcebin
go run ./cmd/havcebind
# You're set! Head to http://localhost:8080
```