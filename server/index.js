const express = require("express");

const fs = require("fs");

const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.get("/", (req, res) => {
	res.send("Hello World!");
});

app.post("/iot", (req, res) => {
    console.log("Hello world")
	console.log(req.query);
	fs.appendFileSync("./data.txt", JSON.stringify(req.query) + "\n");

	return res.send("OK to go");
});

app.get("/messages", (req, res) => {
	const messages = fs.readFileSync("./data.txt", "utf8");
	res.send(messages);
});

app.listen(8000, () => {
	console.log("listening on port 8000");
});