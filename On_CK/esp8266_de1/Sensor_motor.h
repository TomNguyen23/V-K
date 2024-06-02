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
    h2 {text-align:center; }
    .btn-status {
      padding: 10px 20px;
      font-size: 16px;
      border: none;
      border-radius: 5px;
      background-color: #4CAF50;
      color: white;
      cursor: pointer;
    }

    .btn-off {
      background-color: #f44336;
    }
    </style>
    <title>Cuối kì</title>
  </head>
  <body>
    <h1><p id="DHT11Value"> None </p><h1><br>

    <h1><p id="lightStatus"> None </p><h1><br>

    <div id="motor_controller">
      <p>Điều khiển động cơ</p>
      Góc quay: <input class="degrees-input" type="text" id="degrees" value="">
      <button class="btn btn-send">Send</button>
    </div>

    <h2>Bật/ tắt LED</h2>
    <button class='btn-status'>TẮT ĐÈN</button>

    <script>
      let canSendRequest = true;

      setInterval(function() {
        if (!canSendRequest) {
          return;
        }
        var DHT11Value = document.getElementById('DHT11Value');
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            DHT11Value.innerHTML = this.responseText;
          }
        };
        xhttp.open('GET', '/readDHT11', true);
        xhttp.send();
      }, 2000); 

      setInterval(function() {
        if (!canSendRequest) {
          return;
        }
        var lightStatus = document.getElementById('lightStatus');
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            lightStatus.innerHTML = this.responseText;
          }
        };
        xhttp.open('GET', '/readLight', true);
        xhttp.send();
      }, 2000);


      // function sendValue() { 
      //   var degreesInput = document.getElementById('degrees'); 
      //   var xhttp2 = new XMLHttpRequest(); 
      //   var degrees = degreesInput.value; 
      //   xhttp2.open('POST', '/sendValue', true); 
      //   xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded'); 
      //   xhttp2.send('degrees=' + degrees); 
      // }

      document.querySelector('.btn-send').addEventListener('click', function() {
        var degreesInput = document.getElementById('degrees'); 
        var xhttp2 = new XMLHttpRequest(); 
        var degrees = degreesInput.value; 
        canSendRequest = false;
        xhttp2.open('POST', '/sendValue', true); 
        xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded'); 
        xhttp2.send('degrees=' + degrees); 
        xhttp2.onreadystatechange = function() {
          if (this.status == 200) {
            canSendRequest = true;
          }
        };
      });

      const btnStatus = document.querySelector('.btn-status');
      btnStatus.addEventListener('click', () => {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4 && xhr.status == 200) {
                if (xhr.responseText == '0') {
                    btnStatus.innerHTML = 'BẬT ĐÈN';
                    btnStatus.classList.add('btn-off');
                } else {
                    btnStatus.innerHTML = 'TẮT ĐÈN';
                    btnStatus.classList.remove('btn-off');
                }
            }
        };
        xhr.open('GET', '/LEDstatus', true);
        xhr.send();
      });
    </script>
  </body>
</html>
)=====";