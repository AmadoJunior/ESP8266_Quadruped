
const char *MainPage = R"=====(
<HTML>
	<HEAD>
			<TITLE>GamePad</TITLE>
            <style>
                body{
    
                }
                #slider{

                }
            </style>
            
	</HEAD>
<BODY>
    <p id="gamepadInfo" ></p>

            <script type="text/javascript">
                //GamePad
                var interval;
                var gamepadInfo = document.getElementById("gamepadInfo");
                var loading;

                if (!('ongamepadconnected' in window)) {
                // No gamepad events available, poll instead.
                interval = setInterval(pollGamepads, 500);
                }

                function pollGamepads() {
                var gamepads = navigator.getGamepads ? navigator.getGamepads() : (navigator.webkitGetGamepads ? navigator.webkitGetGamepads : []);
                for (var i = 0; i < gamepads.length; i++) {
                    var gp = gamepads[i];
                    if (gp) {
                    gamepadInfo.innerHTML = "Gamepad Connected";
                    gameLoop();
                    clearInterval(interval);
                    }
                }
                }
                
                function applyDeadzone(number, threshold){
                percentage = (Math.abs(number) - threshold) / (1 - threshold);

                if(percentage < 0)
                    percentage = 0;

                return percentage * (number > 0 ? 1 : -1);
                }

                function gameLoop() {
                    if(navigator.webkitGetGamepads) {
                    var gp = navigator.webkitGetGamepads()[0];
                    } else {
                    var gp = navigator.getGamepads()[0];
                    }
                    //JoyStick One
                    var joyOneX = applyDeadzone(gp.axes[0], 0.25);
                    var joyOneY = applyDeadzone(gp.axes[1], 0.25);
                    //JoyStick Two
                    let joyTwoX = applyDeadzone(gp.axes[2], 0.25);
                    let joyTwoY = applyDeadzone(gp.axes[3], 0.25);

                    //console.log(joyOneX + ", " + joyOneY);

                    if(joyOneX < 0 && !loading){
                        dirData = "l";
                        //data += joyOneX;
                        connection.send(dirData);
                        loading = true;
                    } else if(joyOneX > 0 && !loading){
                        dirData = "r";
                        //data += joyOneX;
                        connection.send(dirData);
                        loading = true;
                    } else if(joyOneY < 0 && !loading){
                        dirData = "u";
                        //data += joyOneY;
                        connection.send(dirData);
                        loading = true;
                    } else if(joyOneY > 0 && !loading){
                        dirData = "d";
                        //data += joyOneY;
                        connection.send(dirData);
                        loading = true;
                    } else if(joyTwoX > 0 && !loading){
                        dirData = "e";
                        connection.send(dirData);
                        loading = true;
                    } else if(joyTwoX < 0 && !loading){
                        dirData = "t";
                        connection.send(dirData);
                        loading = true;
                    }

                
                    var start = requestAnimationFrame(gameLoop);
                };


                //Socket Connection
                    var connection = new WebSocket('ws://' + window.location.hostname + ':81/');

                    connection.onopen = function () {

                    connection.send('New Connection ' + new Date());
                    
                    };

                    connection.onerror = function (error) {

                        console.log('WebSocket Error ', error);

                    };

                    connection.onmessage = function (e) {

                        console.log('Server: ', e.data);
                        loading = false;

                    };

                    connection.onclose = function () {

                        console.log('WebSocket Connection Closed');

                    };


                    //Send Data to Socket
                    function sendData (dir, value) {

                        connection.send("Hello");
                        console.log("Data Being Sent");

                    }
            </script>
</BODY>
</HTML>
)=====";