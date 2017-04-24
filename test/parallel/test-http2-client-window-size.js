'use strict';

// Tests that window size is correctly set

const common = require('../common');
const h2 = require('http2');

{
  const server = h2.createServer();
  server.on('stream', (stream, headers, flags) => {
    const c = (cb) => {
    // new Promise(resolve => {
      stream.on('error', err => {
        console.error(err);
      });
      const buffer = Buffer.allocUnsafe(1<<14 + 100);
      const drained = stream.write(buffer, 'buffer');
      console.log('server', drained);
      if (drained) {
        setTimeout(cb, 1000);
      } else {
        stream.once('drain', () => {
          setTimeout(cb, 1000);
        });
      }
    // }).then(() => {
    // });
    };
    c(() => stream.end());
  });
  server.listen(8080);

  server.on('listening', common.mustCall(function() {
    const port = this.address().port;

    const maybeClose = common.mustCall((client) => {
      client.socket.destroy();
      setImmediate(() => server.close());
    });

    const client =
      h2.connect({
        authority: 'localhost',
        protocol: 'http',
        port
      }, {
        settings: {
          initialWindowSize: 1
        }
      }).on('connect', common.mustCall(() => {
        const res = client.request({
          ':method': 'GET',
          ':path': '/'
        });
        res.on('data', data => {
          console.log('client', data[0], data.length);
        });
        res.on('end', data => {
          console.log('client', 'eof');
        });
      }));
  }));
}
