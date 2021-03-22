const dgram = require("dgram");

const client = dgram.createSocket("udp4");
const message = Buffer.from("hihihihihi");

const PORT = 9000;
const HOST = "127.0.0.1";

client.bind(9000);
client.send(message, PORT, HOST, (err, byte) => {
    if (err) {
        throw err;
    }
    console.log("전송완료");
    client.close();
});
