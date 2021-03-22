const dgram = require("dgram");
const udpServer = dgram.createSocket("udp4");
const address = "127.0.0.1";
udpServer.bind(9000);

udpServer.on("listening", () => {
    const addr = udpServer.address();
    console.log("UDP Server listening port: " + addr.port);
});

const message = Buffer.from("hihihihihihi");

udpServer.send(message, 0, message.length, 9000, address);
udpServer.close();
