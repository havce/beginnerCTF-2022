# syntax=docker/dockerfile:1
FROM golang:1.19-alpine AS build
ENV CGO_ENABLED=0

WORKDIR /app

COPY ./main.go ./

RUN go build -o quiz ./main.go

FROM gcr.io/distroless/static

COPY --from=build /app/quiz /quiz

EXPOSE 1337

USER nonroot
CMD ["/quiz"]
