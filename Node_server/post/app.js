const express = require("express")
const ejs = require('ejs')
const bodyParser = require("body-parser")
const app = express()
const fs = require("fs");
var data = "yet";
const port = 3000;
 
app.set('ejs', ejs.renderFile)
 
app.use(bodyParser.urlencoded({ extended: false }))
 
app.get("/", (req, res) => {
    res.render("./index.ejs",
        {
            name: 'None',
            message: 'None'
        })
});
 
app.post("/", (req, res) => {
    res.render('index.ejs', {
        name: req.body.name,
        message: req.body.message
    })

    data = req.body.name+"さん : "+req.body.message;
    fs.appendFile("file1.txt", data+'\n', (err) => {
        if(err){
            console.log(`[error] ${err}`);
        }
        console.log(data);
    });
});


app.listen(port, () => {
  console.log(`listening at http://localhost:${port}`);
});
