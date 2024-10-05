var http = require('http');

http.createServer(function (req, res) {
  res.writeHead(200, { 'Content-Type': 'text/html' });
  res.write('<body bgcolor="orange">');
  res.write('<p>Hello World in NodeJS program...!</p>');
  res.write('</body>');
  res.end();
}).listen(8080, 'localhost', () => { console.log('server started...') });