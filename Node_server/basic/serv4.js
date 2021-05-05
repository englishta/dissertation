const fs = require("fs");
const data = "Hello Node";  // 書き込むデータ準備

// 書き込み
fs.writeFile("file1.txt", data, (err) => {
  if (err){
    console.log(`[error] ${err}`);
  }

  console.log("正常に書き込みが完了しました");
});

console.log("最後まで実行しました");
