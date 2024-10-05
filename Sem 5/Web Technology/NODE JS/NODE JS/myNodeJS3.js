var http = require('http');
const fs = require('fs');

http.createServer(function (req, res) {
  res.writeHead(200, { 'Content-Type': 'text/html' });

  path = './SERVER_PAGE/'

  if (req.url == '/sep')
    path = path + 'sep.html';

  else if (req.url == '/sep2')
    path = path + 'sep2.html';

  else
    path = path + 'sep3.html';


  fs.readFile(path, (err, data) => {
    if (err) {
      console.log(err);
      res.end();
    }
    else {
      res.end(data);
    }
  })


}).listen(8080);