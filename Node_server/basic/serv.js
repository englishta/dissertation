const express = require("express");
const app  = express();
const port = 3000;

// ルーティングの設定
app.get("/", (req, res) =>{
  res.sendFile(`${__dirname}/aaa.html`);
  console.log("/ へアクセスがありました");
});

// HTTPサーバを起動する
app.listen(port, () => {
  console.log(`listening at http://localhost:${port}`);
});
