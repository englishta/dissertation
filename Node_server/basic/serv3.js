const fs = require("fs");
const data = "hello node";
try{
    fs.writeFileSync("file1.txt", data);
    console.log("正常に書き込みが完了しました");
}
catch(e){
    console.log(e.mesage());
}
console.log("最後まで実行しました");

