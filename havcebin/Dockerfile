# syntax=docker/dockerfile:1

FROM golang:1.19-alpine AS build
ENV CGO_ENABLED=0

WORKDIR /app

COPY ./go.mod ./
COPY ./go.sum ./

RUN go mod download

COPY ./ ./

RUN go build -o havcebin ./cmd/havcebind 

FROM alpine:3.17

COPY --from=build /app/havcebin /havcebin

RUN adduser -D -S havcebin

RUN mkdir -p /home/havcebin/.storage && chown -R havcebin /home/havcebin

USER havcebin
CMD ["/bin/sh", "-c", "echo \"${FLAG}\" > /home/havcebin/flag.txt && /havcebin -save-dir ~/.storage"]
