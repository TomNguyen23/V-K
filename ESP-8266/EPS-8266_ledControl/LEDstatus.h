const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
    <meta charset='utf-8'>
    <style>
      body {
        font-family: Arial, sans-serif; 
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
      }
      h2 {text-align:center; }
      button {
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
    <title>Điều khiển LED</title>
  </head>
  <body>
    <h2>Bật/ tắt LED</h2>

    <button class='btn-status'>TẮT ĐÈN</button>

    <script>
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
