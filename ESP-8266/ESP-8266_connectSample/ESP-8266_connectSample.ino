// Đây là HTTP Header, thông thường nên để nó như vậy
String httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
// Đây là code HTML sẽ gử i cho truy cập, chỉnh sửa code HTML dưới đây
// để thay đổi nội dung trang web
String html = R"=====(
                <!DOCTYPE html>
                <html>
                  <head>
                    <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
                    <meta charset='utf-8'>
                    <meta http-equiv='refresh' content='1'>
                    <style>
                      h2 {text-align:center; }
                      p {text-align:center;}
                    </style>
                    <title>Web Server với NodeMCU, tự động refresh</title>
                  </head>
                  <body>
                    <h2>Tự động update với HTML</h2>

                    <div id='count'>
                      <p>Thời gian từ khi server khởi động: %time% giây</p>
                    </div>
                  </body>
                </html>
              )=====";
// Sử dụng R"=====( cho phép ta tạo string trên nhi ều dòng

# include <ESP8266WiFi.h>
# define TENWIFI "Huu Chin"
# define PASSWIFI "9999@9999"
WiFiServer server(80);


void setup(){
  Serial.begin(115200);
  WiFi.begin(TENWIFI, PASSWIFI);
  Serial.print("\n Đang thử kết nối");
  while (WiFi.status() != WL_CONNECTED) {
    delay (500); 
    Serial.print(".");
  }

  Serial.print("\n Kết nối thanh công. IP address: ");
  Serial.println(WiFi.localIP());
  server.begin(); // Khởi động server.
  Serial.print("Server đã khởi động.");
}
void loop() {
  // Kiểm tra nếu có client,
  WiFiClient client = server.available();
  if (!client) return; 
  // client == 0 khi không có người truy cập

  String htmlPage = html;
  htmlPage.replace("%time%", String(millis()/1000));
  // thay thế chuỗi '%time%' bằng thời gian đã trôi qua

  client.flush(); // bỏ qua thông tin client gử i
  client.print(httpHeader);// viết HTTP Header ra trình duyệt trước
  client.print(htmlPage);// viết code HTML ra trình duyệt
  delay(5); // chờ một chút để trình duyệt xử lý
  // Khi hàm loop kết thúc
  // đối tượng client sẽ tự bị hủy và tự disconnect
}