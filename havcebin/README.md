# havcebin
## Description
> I made this awesome pastebin clone.
> Everyone knows that Go is super secure and still unhacked to this day.

## Solution
The service that implements the interaction with the filesystem (i.e. `filesystem/filesystem.go`)
is vulnerable to a path traversal attack.

There are a coiple of gotchas that permit this in Go.

`filepath.Clean` does not remove `..` from a path **if it doesn't begin with a `/`** (i.e. the path isn't *rooted*) as one can see in the [official docs](https://pkg.go.dev/path/filepath#Clean).

```golang
// name is user-controlled, so it may not begin with a slash.
filepath.Join(p.BasePath, filepath.Clean(name))
```

Before passing the path to the `os.Open` function there is a function
that replaces everything that matches a blocklist with a empty string. 

This simple (and insecure) filter can be abused sending a path containing `....//`, 
which results in `../`.

Sending a request along the lines of this reveals the flag:
```
http://havcebin.chals.beginner.havce.it:8080/paste?key=....//....//....//....//home/havcebin/flag.txt
```

## Remediation
Make sure the path passed to `filepath.Clean` starts with a slash (`/`).

## Flag
`havceCTF{d0t_d0t_d0t_d0t_s14sh_s1l4sh_k1nd4_un3xpec13d}`