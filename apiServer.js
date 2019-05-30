const express = require("express");
const cors = require("cors");
const bodyParser = require("body-parser");
const path = require("path");
const uuid = require("uuid/v4");

const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(
  cors({
    allowedHeaders: ["Content-Type"],
    exposedHeaders: ["Content-Type"],
    origin: "*",
    methods: "GET,HEAD,PUT,PATCH,POST,DELETE",
    preflightContinue: false
  })
);

const users = [
  {
    id: "1",
    firstName: "Tony",
    lastName: "Montana",
    email: "montananana@nanana.hu"
  }
];

app.get("/api/users", async (req, res, next) => {
  res.json({ users: users });
});

app.post("/api/user", async (req, res, next) => {
  const id = uuid();
  users.push({
    ...req.body,
    id
  });
  res.json({ success: true, createdUserId: id });
});

const PORT = process.env.PORT || 8000;

app.listen(PORT, () => {
  console.log(`App is running on port ${PORT}`);
});
