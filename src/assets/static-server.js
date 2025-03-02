const http = require('http');
const fs = require('fs');
const path = require('path');

// Define the port to listen on
const PORT = 3000;

// Function to handle requests
function serveStaticFile(res, filePath) {
    const fileStream = fs.createReadStream(filePath);
    console.log(`static file [${filePath}]`)
    if (filePath.endsWith('.wasm')) {
        res.writeHead(200, { 'Content-Type': 'application/wasm' });
    } else {
        res.writeHead(200, { 'Content-Type': 'text/html' });
    }
    fileStream.pipe(res);
}

// Function to get the absolute path of a given file
function resolvePath(requestUrl) {
    const filePath = path.join(process.cwd(), requestUrl);

    // Ensure that the requested file is within the current directory
    if (filePath.indexOf(process.cwd()) !== 0) {
        return null;
    }

    return filePath;
}

// Create an HTTP server and listen on the specified port
http.createServer((req, res) => {
    const filePath = resolvePath(req.url);

    if (!filePath) {
        res.writeHead(403);
        res.end('Forbidden');
        return;
    }

    fs.stat(filePath, (err, stats) => {
        if (err || !stats.isFile()) {
            res.writeHead(404);
            res.end('Not Found');
            return;
        }
        serveStaticFile(res, filePath);
    });
}).listen(PORT);

console.log(`Server running at http://localhost:${PORT}`);