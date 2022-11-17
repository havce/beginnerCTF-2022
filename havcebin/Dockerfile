# syntax=docker/dockerfile:1

FROM golang:1.19-buster AS build
ENV CGO_ENABLED=0

WORKDIR /app

COPY ./havcebin ./

RUN go build -o havcebin ./cmd/havcebind 

FROM gcr.io/distroless/static

WORKDIR /

COPY --from=build /app/havcebin /havcebin
COPY ./flag.txt /
COPY --chown=nonroot:nonroot ./HelloWorld /code/HelloWorld

EXPOSE 8080

USER nonroot:nonroot

ENTRYPOINT ["/havcebin"]
