FROM ghcr.io/google/nsjail/nsjail:latest

RUN mkdir -p /task
WORKDIR /task
ADD ./psw_checker /task/psw_checker

CMD ["sh", "-c", "nsjail -Ml --port 3001 --user 1000 --group 1000 --disable_proc --chroot /task -E FLAG -R /lib/x86_64-linux-gnu/libpthread.so.0 -R /lib/x86_64-linux-gnu/libdl.so.2 -R /lib/x86_64-linux-gnu/libpcre.so.3 -R /lib/x86_64-linux-gnu/libselinux.so.1 -R /lib/x86_64-linux-gnu/ld-2.27.so -R /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 -R /lib/x86_64-linux-gnu/libc-2.27.so -R /lib/x86_64-linux-gnu/libc.so.6 -R /lib64/ -R /bin/sh -R /bin/ls -R /bin/cat /psw_checker"]
