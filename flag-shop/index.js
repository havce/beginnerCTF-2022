var express = require('express')
const bodyParser = require('body-parser');
var session = require('express-session')
var path = require('path');

const port = 3000

var app = express()

const ITEMS = {
  "mucca": { "price": 1, path: "mucca" },
  "orso": { "price": 2, path: "orso" },
}

app.set('view engine', 'ejs');
app.use('/assets', express.static('assets'))

app.use(session({
  secret: 'keyboard cat',
  resave: false,
  saveUninitialized: true
}))

app.use(bodyParser.urlencoded({ extended: true }));

app.use(function (req, res, next) {
  if (!req.session.credito) {
    req.session.credito = 1000
  }

  next()
})

app.get('/', function (req, res, next) {
  res.render('index', { credito: req.session.credito })
})

app.post('/compera', function (req, res, next) {
  const obj = req.body.object
  const qty = req.body.qty
  const credito = req.session.credito

  const price = ITEMS[obj].price
  if (price === undefined) {
    res.status(404).send("non ce l'abbiamo mica quell'affare lì")
    return
  }

  if (credito < qty * price) {
    res.status(402).send("non c'hai na lira")
    return
  }

  req.session.credito = credito - qty * price

  res.render(ITEMS[obj].path, { qty })
})

app.get('/flag', function (req, res) {
  if (req.session.credito >= 10000000) {
    res.send(process.env.FLAG)
    return
  }

  res.status(402).send("non c'hai na lira")
})

app.listen(port, () => {
  console.log(`flag-shop listening on port ${port}`)
})
