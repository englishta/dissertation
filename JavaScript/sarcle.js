var canvas = document.getElementById("myCanvas");
var ctx = canvas.getContext("2d");
var r = 200.0;
var r2 = 90.0;
var omega = Math.PI/200.0;
var omega2 = Math.PI/100.0;
var ballRadius = 15;
var ballRadius2 = 12;
var x = canvas.width/2; var y = canvas.height/2-r;// 地球
var x2 = canvas.width/2; var y2 = canvas.height/2-r-r2;// 惑星
var cx = canvas.width/2;
var cy = canvas.height/2;
var t = 0;

function drawball(){
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.beginPath();
    ctx.arc(x, y, ballRadius, 0, Math.PI*2);
    ctx.arc(x2, y2, ballRadius2, 0, Math.PI*2);
    ctx.arc(cx, cy, ballRadius, 0, Math.PI*2);
    ctx.fillStyle = "#0095DD";
    ctx.fill();
    ctx.closePath();
}
// 描写の関数
function draw() {
    drawball();
    x = r*Math.cos(omega*t)+cx;
    y = r*Math.sin(omega*t)+cy;
    x2 = r2*Math.cos(omega2*t)+x;
    y2 = r2*Math.sin(omega2*t)+y;
    t+=1
    if(t>1000000) t = 0; //オーバーフロー対策
}
var interval = setInterval(draw, 10);