window.requestAnimFrame = (function(callback){
    return window.requestAnimationFrame ||
    window.webkitRequestAnimationFrame ||
    window.mozRequestAnimationFrame ||
    window.oRequestAnimationFrame ||
    window.msRequestAnimationFrame ||
    function(callback){
        window.setTimeout(callback, 1000 / 60);
    };
})();
 
function initBalls(){
    balls = [];
    var red = "#EF2B36";
    var orange = "#F5821D"
    var yellow = "#FFC636";
    var green = "#02A817";
    var blue = "#3A5BCD";
 
    // i
	 balls.push(new Ball(50, 20, 0, 0, red));
	 balls.push(new Ball(50, 42, 0, 0, red));
	 balls.push(new Ball(50, 58, 0, 0, red));
    balls.push(new Ball(50, 74, 0, 0, red));
    balls.push(new Ball(50, 90, 0, 0, red));
    
    //m
    balls.push(new Ball(70, 42, 0, 0, orange));
    balls.push(new Ball(70, 58, 0, 0, orange));
    balls.push(new Ball(70, 74, 0, 0, orange));
    balls.push(new Ball(70, 90, 0, 0, orange));
    balls.push(new Ball(70, 42, 0, 0, orange));
    balls.push(new Ball(80, 28, 0, 0, orange));
    balls.push(new Ball(90, 28, 0, 0, orange));
    balls.push(new Ball(100, 42, 0, 0, orange));
    balls.push(new Ball(100, 58, 0, 0, orange));
    balls.push(new Ball(110, 28, 0, 0, orange));
    balls.push(new Ball(120, 28, 0, 0, orange));
    balls.push(new Ball(130, 42, 0, 0, orange));
    balls.push(new Ball(130, 58, 0, 0, orange));
    balls.push(new Ball(133, 74, 0, 0, orange));
    balls.push(new Ball(140, 88, 0, 0, orange));
    balls.push(new Ball(156, 90, 0, 0, orange));
    
    //6
    balls.push(new Ball(170, 80, 0, 0, yellow));
    balls.push(new Ball(184, 90, 0, 0, yellow));
    balls.push(new Ball(200, 90, 0, 0, yellow));
    balls.push(new Ball(210, 75, 0, 0, yellow));
    balls.push(new Ball(207, 60, 0, 0, yellow));
    balls.push(new Ball(192, 50, 0, 0, yellow));
    balls.push(new Ball(184, 36, 0, 0, yellow));
    balls.push(new Ball(170, 64, 0, 0, yellow));
    balls.push(new Ball(175, 48, 0, 0, yellow));
    balls.push(new Ball(195, 22, 0, 0, yellow));
    balls.push(new Ball(208, 12, 0, 0, yellow));
    
    //3
    balls.push(new Ball(230, 28, 0, 0, green));
    balls.push(new Ball(240, 20, 0, 0, green));
    balls.push(new Ball(256, 20, 0, 0, green));
    balls.push(new Ball(266, 30, 0, 0, green));
    balls.push(new Ball(261, 45, 0, 0, green));
    balls.push(new Ball(248, 55, 0, 0, green));
    balls.push(new Ball(261, 65, 0, 0, green));
    balls.push(new Ball(266, 80, 0, 0, green));
    balls.push(new Ball(256, 90, 0, 0, green));
    balls.push(new Ball(240, 90, 0, 0, green));
    balls.push(new Ball(230, 82, 0, 0, green));

    //3
    balls.push(new Ball(290, 28, 0, 0, blue));
    balls.push(new Ball(300, 20, 0, 0, blue));
    balls.push(new Ball(316, 20, 0, 0, blue));
    balls.push(new Ball(326, 30, 0, 0, blue));
    balls.push(new Ball(321, 45, 0, 0, blue));
    balls.push(new Ball(308, 55, 0, 0, blue));
    balls.push(new Ball(321, 65, 0, 0, blue));
    balls.push(new Ball(326, 80, 0, 0, blue));
    balls.push(new Ball(316, 90, 0, 0, blue));
    balls.push(new Ball(300, 90, 0, 0, blue));
    balls.push(new Ball(290, 82, 0, 0, blue));
    
    return balls;
}
 
function getMousePos(canvas, evt){
    // get canvas position
    var obj = canvas;
    var top = 0;
    var left = 0;
    while (obj.tagName != 'BODY') {
        top += obj.offsetTop;
        left += obj.offsetLeft;
        obj = obj.offsetParent;
    }
 
    // return relative mouse position
    var mouseX = evt.clientX - left + window.pageXOffset;
    var mouseY = evt.clientY - top + window.pageYOffset;
    return {
        x: mouseX,
        y: mouseY
    };
}
 
function updateBalls(canvas, balls, timeDiff, mousePos){
    var context = canvas.getContext("2d");
    var collisionDamper = 0.3;
    var floorFriction = 0.0008 * timeDiff;
    var mouseForceMultiplier = 0.7 * timeDiff;
    var restoreForce = 0.002 * timeDiff;
 
    for (var n = 0; n < balls.length; n++) {
        var ball = balls[n];
        // set ball position based on velocity
        ball.y += ball.vy;
        ball.x += ball.vx;
 
        // restore forces
        if (ball.x > ball.origX) {
            ball.vx -= restoreForce;
        }
        else {
            ball.vx += restoreForce;
        }
        if (ball.y > ball.origY) {
            ball.vy -= restoreForce;
        }
        else {
            ball.vy += restoreForce;
        }
 
        // mouse forces
        var mouseX = mousePos.x;
        var mouseY = mousePos.y;
 
        var distX = ball.x - mouseX;
        var distY = ball.y - mouseY;
 
        var radius = Math.sqrt(Math.pow(distX, 2) +
        Math.pow(distY, 2));
 
        var totalDist = Math.abs(distX) + Math.abs(distY);
 
        var forceX = (Math.abs(distX) / totalDist) *
        (1 / radius) *
        mouseForceMultiplier;
        var forceY = (Math.abs(distY) / totalDist) *
        (1 / radius) *
        mouseForceMultiplier;
 
        if (distX > 0) { // mouse is left of ball
            ball.vx += forceX;
        }
        else {
            ball.vx -= forceX;
        }
        if (distY > 0) { // mouse is on top of ball
            ball.vy += forceY;
        }
        else {
            ball.vy -= forceY;
        }
 
        // floor friction
        if (ball.vx > 0) {
            ball.vx -= floorFriction;
        }
        else if (ball.vx < 0) {
            ball.vx += floorFriction;
        }
        if (ball.vy > 0) {
            ball.vy -= floorFriction;
        }
        else if (ball.vy < 0) {
            ball.vy += floorFriction;
        }
 
        // floor condition
        if (ball.y > (canvas.height - ball.radius)) {
            ball.y = canvas.height - ball.radius - 2;
            ball.vy *= -1;
            ball.vy *= (1 - collisionDamper);
        }
 
        // ceiling condition
        if (ball.y < (ball.radius)) {
            ball.y = ball.radius + 2;
            ball.vy *= -1;
            ball.vy *= (1 - collisionDamper);
        }
 
        // right wall condition
        if (ball.x > (canvas.width - ball.radius)) {
            ball.x = canvas.width - ball.radius - 2;
            ball.vx *= -1;
            ball.vx *= (1 - collisionDamper);
        }
 
        // left wall condition
        if (ball.x < (ball.radius)) {
            ball.x = ball.radius + 2;
            ball.vx *= -1;
            ball.vx *= (1 - collisionDamper);
        }
    }
}
 
function Ball(x, y, vx, vy, color){
    this.x = x;
    this.y = y;
    this.vx = vx;
    this.vy = vy;
    this.color = color;
    this.origX = x;
    this.origY = y;
    this.radius = 8;
}

function draw_logo( canvas, balls ) {
	var context = canvas.getContext("2d");
	    // clear
    context.clearRect(0, 0, canvas.width, canvas.height);
 
    // render
    
    for (var n = 0; n < balls.length; n++) {
        var ball = balls[n];
        context.beginPath();
        context.arc(ball.x, ball.y, ball.radius, 0, 2 * Math.PI, false);
        context.fillStyle = ball.color;
        context.fill();
    }
}

function animate(canvas, balls, lastTime, mousePos){
    
 
    // update
    var date = new Date();
    var time = date.getTime();
    var timeDiff = time - lastTime;
    updateBalls(canvas, balls, timeDiff, mousePos);
    lastTime = time;
 
    draw_logo(canvas, balls);
 
    // request new frame
    if ( canvas.bounce == 1 ) {
       requestAnimFrame(function(){
           animate(canvas, balls, lastTime, mousePos);
       });
    } else
    {
     draw_logo(canvas, new initBalls() );
    
    	}
}



function bounce_logo_switch() {
	 var canvas = document.getElementById("logo");
    var balls = initBalls();
    var date = new Date();
    var time = date.getTime();
    if ( canvas.bounce == 0 ) {
    	canvas.bounce = 1;
        var mousePos = {
           x: 9999,
           y: 9999
        }
        canvas.addEventListener("mousemove", function(evt){
        var pos = getMousePos(canvas, evt);
           mousePos.x = pos.x;
           mousePos.y = pos.y;
    });

    canvas.addEventListener("mouseout", function(evt){
           mousePos.x = 9999;
           mousePos.y = 9999;
    });
    animate(canvas, balls, time, mousePos);
    }
    else {
       canvas.bounce = 0;
    }
}

window.onload = function(){
    var canvas = document.getElementById("logo");
    var context = canvas.getContext("2d");
    var balls = initBalls();
    var date = new Date();
    var time = date.getTime();
    canvas.bounce = 0;
     var mousePos = {
           x: 9999,
           y: 9999
        }
    animate(canvas, balls, time, mousePos);
    canvas.addEventListener( "click", bounce_logo_switch, false );
}


