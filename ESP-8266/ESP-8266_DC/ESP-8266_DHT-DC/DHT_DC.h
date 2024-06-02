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

    .button2 {
      background-color: #555555;
    }
    .btn {
      background-color: #4CAF50;
      border: none;
      color: white;
      padding: 16px 40px;
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
    <title>Cảm biến ánh sáng và DC motor</title>
  </head>
  <body>
    <h1><p id="serialMonitor"> None </p><h1><br>
      <div id="motor_controller">
        <p>Điều khuyển động cơ DC</p>
        <button class="btn btn-forward" onclick="goForward()">Tới</button>
        <button class="btn btn-backward" onclick="goBackward()">Lui</button> <br>

        <button class="btn btn-speedup" onclick="goSpeedUp()">Tăng tốc</button>
        <button class="btn btn-speeddown" onclick="goSpeedDown()">Giảm tốc</button> <br>
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
        xhttp.open('GET', '/readSerial', true);
        xhttp.send();
      }

      
      function goForward() { 
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == 'go forward') {
              console.log('OK');
              document.querySelector(".btn-forward").classList.add("button2");
              document.querySelector(".btn-backward").classList.remove("button2");
            } else {
              console.log('Error');
            }
          }
        };
        xhttp.open('GET', '/DCforward', true);
        xhttp.send();
      }

      function goBackward() { 
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == 'go backward') {
              console.log('OK');
              document.querySelector(".btn-backward").classList.add("button2");
              document.querySelector(".btn-forward").classList.remove("button2");
            } else {
              console.log('Error');
            }
          }
        };
        xhttp.open('GET', '/DCbackward', true);
        xhttp.send();
      }

      function goSpeedUp() { 
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == 'speedUp') {
              console.log('OK');
              document.querySelector(".btn-speedup").classList.add("button2");
              document.querySelector(".btn-speeddown").classList.remove("button2");
            } else {
              console.log('Error');
            }
          }
        };
        xhttp.open('GET', '/DCspeedup', true);
        xhttp.send();
      }

      function goSpeedDown() { 
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == 'speedDown') {
              console.log('OK');
              document.querySelector(".btn-speeddown").classList.add("button2");
              document.querySelector(".btn-speedup").classList.remove("button2");
            } else {
              console.log('Error');
            }
          }
        };
        xhttp.open('GET', '/DCspeeddown', true);
        xhttp.send();
      }
    </script>
  </body>
</html>
)=====";