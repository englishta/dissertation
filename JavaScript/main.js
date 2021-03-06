var canvas = document.getElementById("myCanvas");
var ctx = canvas.getContext("2d");
var ballRadius = 10;
var x = canvas.width/2;
var y = canvas.height-30;
var x_ = canvas.width/2;
var y_ = canvas.height-30;

// var dx = Math.round(Math.random()*2)+1;
// var dy = -1*(Math.round(Math.random()*2)+1);
var dx = 4; // ボール1の移動速度
var dy = -4;
// var dx_ = -1*(Math.round(Math.random()*2)+1);
// var dy_ = -1*(Math.round(Math.random()*2)+1);
var dx_ = -3; // ボール2の移動速度
var dy_ = -3;

var dx_b = 2; // ブロックの移動速度
var dy_b = 2;
var brick_move_x = 0; // ブロックの移動距離x
var brick_move_y = 0; // ブロックの移動距離y
var last_brick_x = 0; // 最後のブロックの座標を記録
var last_brick_y = 0;
var score = 0;

// アンダーバーの寸法など
var paddleHeight = 10;
var paddleWidth = 100;
// var paddleWidth = 650; //テスト用
var paddleX = (canvas.width-paddleWidth)/2;

// ブロックの寸法など
var brickRowCount = 3;
var brickColumnCount = 5;
var brickWidth = 95;
var brickHeight = 30;
var brickPadding = 20;
var brickOffsetTop = 30;
var brickOffsetLeft = 30;

// ブロックの初期化
var bricks = [];
for(var c=0; c<brickColumnCount; c++) {
    bricks[c] = [];
    for(var r=0; r<brickRowCount; r++) {
        bricks[c][r] = { x: 0, y: 0, status : 1 };
    }
}

var brickX = (c*(brickWidth+brickPadding))+brickOffsetLeft;
var brickY = (r*(brickHeight+brickPadding))+brickOffsetTop;

function drawBricks() {
for(var c=0; c<brickColumnCount; c++) {
    for(var r=0; r<brickRowCount; r++) {
        // ブロックが消去済みであれば描写しない
        if(bricks[c][r].status == 0) continue;
        var brickX = (c*(brickWidth+brickPadding))+brickOffsetLeft+brick_move_x;
        var brickY = (r*(brickHeight+brickPadding))+brickOffsetTop+brick_move_y;
        bricks[c][r].x = brickX;
        bricks[c][r].y = brickY;
        ctx.beginPath();
        ctx.rect(brickX, brickY, brickWidth, brickHeight);
        ctx.fillStyle = "#0095DD";
        ctx.fill();
        ctx.closePath();
    }
}
}
// キーボードの操作に関する変数,ボタンが押されるとTrue
var rightPressed = false;
var leftPressed = false;

document.addEventListener("keydown", keyDownHandler, false);
document.addEventListener("keyup", keyUpHandler, false);

function keyDownHandler(e) {
    if(e.key == "Right" || e.key == "ArrowRight" || e.key == "l") {
        rightPressed = true;
    }
    else if(e.key == "Left" || e.key == "ArrowLeft" || e.key == "j") {
        leftPressed = true;
    }
}

function keyUpHandler(e) {
    if(e.key == "Right" || e.key == "ArrowRight" || e.key == "l") {
        rightPressed = false;
    }
    else if(e.key == "Left" || e.key == "ArrowLeft" || e.key == "j") {
        leftPressed = false;
    }
}
function congratulation(){
    alert("おめでとうございます！！ ゲームクリアです！！");
    document.location.reload();
    clearInterval(interval);
}

// ブロックに衝突するかを調べる
function collisionDetection() {
    for(var c=0; c<brickColumnCount; c++) {
        for(var r=0; r<brickRowCount; r++) {
            var b = bricks[c][r];
            if(score >= 14 && b.status == 1){
                last_brick_x = b.x+brickWidth/2;
                last_brick_y = b.y+brickHeight/2;
            }
            if(b.status == 1){
                if(x > b.x && x < b.x+brickWidth && y > b.y && y < b.y+brickHeight) {
                    dy = -dy;
                    if(score<14) b.status = 0; //最後のブロックは消さない
                    score++;
                }
                if(x_ > b.x && x_ < b.x+brickWidth && y_ > b.y && y_ < b.y+brickHeight) {
                    dy_ = -dy_;
                    if(score<14) b.status = 0; //最後のブロックは消さない
                    score++;
                }
            }
        }
    }
    if(score >=18) congratulation();
}
function drawBall() {
    ctx.beginPath();
    ctx.arc(x, y, ballRadius, 0, Math.PI*2);
    ctx.arc(x_, y_, ballRadius, 0, Math.PI*2);

    ctx.fillStyle = "#0095DD";
    ctx.fill();
    ctx.closePath();
}
function drawPaddle() {
    ctx.beginPath();
    ctx.rect(paddleX, canvas.height-paddleHeight, paddleWidth, paddleHeight);
    ctx.fillStyle = "#0095DD";
    ctx.fill();
    ctx.closePath();
}
function drawScore(){
    ctx.font = "26px Arial";
    ctx.fillStyle = "green";
    ctx.fillText("Score: "+score, 8, 300);
}
function mht(x1, y1, x2, y2){
    return Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

// 描写の関数
function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawBall();
    drawPaddle();
    collisionDetection();
    drawScore();
    drawBricks();

    if(x + dx > canvas.width-ballRadius || x + dx < ballRadius) {
        dx = -dx;
    }
    if(x_ + dx_ > canvas.width-ballRadius || x_ + dx_ < ballRadius) {
        dx_ = -dx_;
    }
    if(y+dy < ballRadius){
        dy = -dy;
    }
    if(y_+dy_ < ballRadius){
        dy_ = -dy_;
    }
    if(y+dy > canvas.height-ballRadius){
        if(x >= paddleX && x <= paddleX + paddleWidth){
            dy = -dy;
        }else{
            alert("GAME OVER");
            document.location.reload();
            clearInterval(interval);
        }
    }
    if(y_+dy_ > canvas.height-ballRadius){
        if(x_ >= paddleX && x_ <= paddleX + paddleWidth){
            dy_ = -dy_;
        }else{
            alert("GAME OVER");
            document.location.reload();
            clearInterval(interval);
        }
    }

    if(rightPressed && paddleX < canvas.width-paddleWidth) {
        paddleX += 7;
    }
    else if(leftPressed && paddleX > 0) {
        paddleX -= 7;
    }

    x += dx;
    y += dy;
    x_ += dx_;
    y_ += dy_;
    if(score >= 14){// 最後の一つになったら、大きく動く
        if(brick_move_y > 450 || brick_move_y < -20) dy_b = -dy_b;
        if(brick_move_x > 350 || brick_move_x < -20) dx_b = -dx_b;
        // ブロックとボール1,2間のマンハッタン距離を求める
        var mht_dist1 = mht(x, last_brick_x, y, last_brick_y); // 今のマンハッタン距離
        var mht_dist2 = mht(x_, last_brick_x, y_, last_brick_y);
        // var mht_dist_next1 = mht(x+dx, last_brick_x+dx_b, y+dy, last_brick_y+dy_b);
        // var mht_dist_next2 = mht(x_+dx_, last_brick_x+dx_b, y_+dy_, last_brick_y+dy_b);
        var mht_dist_next_x1 = mht(x+dx, last_brick_x+dx_b, y, last_brick_y); // 変化後のマンハッタン距離
        var mht_dist_next_x2 = mht(x_+dx_, last_brick_x+dx_b, y_, last_brick_y);
        var mht_dist_next_y1 = mht(x, last_brick_x, y+dy, last_brick_y+dy_b); // 変化後のマンハッタン距離
        var mht_dist_next_y2 = mht(x_, last_brick_x, y_+dy_, last_brick_y+dy_b);
        
        if(mht_dist1<100 || mht_dist2<100){
            if(mht_dist1 > mht_dist_next_x1 || mht_dist2 > mht_dist_next_x2){
                dx_b = -dx_b;
            }else{
                brick_move_x += 2*dx_b;
            }
            if(mht_dist1 > mht_dist_next_y1 || mht_dist2 > mht_dist_next_y2){
                dy_b = -dy_b;
            }else{
                brick_move_y += 2*dy_b;
            }
        }
        brick_move_x += dx_b;
        brick_move_y += dy_b;
    }else{
        if(brick_move_y > 130 || brick_move_y < -15) dy_b = -dy_b;
        if(brick_move_x > 20 || brick_move_x < -20) dx_b = -dx_b;
        brick_move_x += dx_b;
        brick_move_y += dy_b;
    }
}
var interval = setInterval(draw, 10);