const express = require('express');
const app = express()
var path = require('path');
const port = 3000

app.get('/', (req, res) => {
    var options = {
        root: path.join(__dirname)
    };
    var fileName = 'public/img/rob.jpg';
    res.sendFile(fileName, options, function (err) {
        if (err) {
            next(err);
        } else {
            console.log('Sent:', fileName);
        }
    });
})

app.get('/sourcecode', (req, res) => {
    var options = {
        root: path.join(__dirname)
    };
    var fileName = 'index.js';
    res.sendFile(fileName, options, function (err) {
        if (err) {
            next(err);
        } else {
            console.log('Sent:', fileName);
        }
    });
})

app.get('/robots.txt', (req, res) => {
    var options = {
        root: path.join(__dirname)
    };
    var fileName = 'robots.txt';
    res.sendFile(fileName, options, function (err) {
        if (err) {
            next(err);
        } else {
            console.log('Sent:', fileName);
        }
    });
})

app.get('/GoToThis3ndP0intTOGetd4Fl4g', (req, res) => {
    var options = {
        root: path.join(__dirname)
    };
    var fileName = 'flag.txt';
    res.sendFile(fileName, options, function (err) {
        if (err) {
            next(err);
        } else {
            console.log('Sent:', fileName);
        }
    });
})



app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})