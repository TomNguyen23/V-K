const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
    <meta charset='utf-8'>
    <style>
      html {
        font-family: Helvetica;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
    .button {
      background-color: #4CAF50;
      border: none;
      color: white;
      padding: 16px 40px;
      text-decoration: none;
      font-size: 30px;
      margin: 2px;
      cursor: pointer;
    }
    .button2 {
      background-color: #555555;
    }
    .btn{
      background-color: #4CAF50;
      border: none;
      color: white;
      padding: 8px 20px;
      text-decoration: none;
      font-size: 16px;
      margin: 2px;
      cursor: pointer;
    }
    .degrees-input {
      width: 60px;
      height: 30px;
      font-size: 20px;
      text-align: center;
    }
    </style>
    <title>Cảm biến DHT và động cơ bước</title>
  </head>
  <body>
    <h1><p id="serialMonitor"> None </p><h1><br>
      <div id="motor_controller">
        <p>Điều khuyển động cơ bước</p>
        Degrees: <input class="degrees-input" type="text" id="degrees" value="">
        <button class="btn" onclick="sendValue()">Send</button>
      </div>

    <script>
      window.onload = function() {
        readSerial();
      };

      function readSerial() {
        var serialMonitor = document.getElementById('serialMonitor');
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            serialMonitor.innerHTML = this.responseText;
            setTimeout(readSerial, 500);
          }
        };
        xhttp.open('GET', 'readSerial', true);
        xhttp.send();
      }

      
      function sendValue() { 
        var degreesInput = document.getElementById('degrees'); 
        var xhttp2 = new XMLHttpRequest(); 
        var degrees = degreesInput.value; 
        xhttp2.open('POST', 'sendValue', true); 
        xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded'); 
        xhttp2.send('degrees=' + degrees); 
      }
    </script>
  </body>
</html>
)=====";