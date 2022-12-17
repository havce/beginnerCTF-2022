# hidden-flag
## Description
> I forgot where i put the flag, can you help me find it?

## Flag
`havceCTF{alw4ys_remember_to_ch3ck_robots.txt}`

## Writeup
The robot image suggests you to take a look at the robots.txt file, (it's often present on website not just on this CTF). You can see the `/soucecode` endpoint, follow it so you can see the souce of the application.

``` javascript
app.get('/GoToThis3ndP0intTOGetd4Fl4g', (req, res) => {
    res.send(process.env.FLAG);
})
```
This is the endpoint fot the flag.