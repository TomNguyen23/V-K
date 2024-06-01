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
    </style>
    <title>Giá trị cảm biến ánh sáng</title>
  </head>
  <body>
    <h1><p id="serialMonitor"> None </p><h1><br>

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
    </script>
  </body>
</html>
)=====";