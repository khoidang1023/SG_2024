🌿 Smart Garden – Hệ thống giám sát và điều khiển nhà kính thông minh
🧩 Giới thiệu

Smart Garden là một hệ thống giám sát và điều khiển tự động môi trường nhà kính, giúp người dùng theo dõi và điều chỉnh các yếu tố như nhiệt độ, độ ẩm, ánh sáng, và mực nước.
Dự án sử dụng ESP32 làm bộ xử lý trung tâm, kết hợp với các cảm biến, relay, màn hình OLED và giao thức MQTT để hỗ trợ điều khiển – giám sát từ xa qua Internet.

⚙️ Thành phần hệ thống
Thành phần	Chức năng chính
ESP32	Vi điều khiển trung tâm, kết nối WiFi và giao tiếp MQTT
Cảm biến DHT22	Đo nhiệt độ và độ ẩm không khí
Cảm biến HC-SR04	Đo mực nước trong bể chứa
Cảm biến LDR	Đo cường độ ánh sáng
Màn hình OLED SSD1306	Hiển thị thông tin cảm biến và trạng thái hệ thống
Relay Module	Bật/tắt thiết bị (đèn, quạt, bơm, phun sương)
Button (Nút nhấn)	Chuyển đổi chế độ hoặc điều khiển thủ công
LED cảnh báo	Hiển thị trạng thái hoạt động của hệ thống
🖥️ Tính năng chính

🌡️ Giám sát nhiệt độ, độ ẩm, ánh sáng, và mực nước theo thời gian thực

💧 Tự động bật/tắt thiết bị (bơm, quạt, đèn) theo ngưỡng cài đặt

📡 Kết nối WiFi và giao tiếp MQTT để điều khiển, giám sát từ xa qua ứng dụng hoặc dashboard

🧠 Hỗ trợ chế độ thủ công thông qua nút nhấn

📺 Màn hình OLED SSD1306 hiển thị thông tin cảm biến và trạng thái hệ thống

🔔 LED cảnh báo hiển thị hoạt động hoặc lỗi của hệ thống

🧰 Phần mềm và thư viện sử dụng

Arduino IDE / PlatformIO

Thư viện Arduino cho ESP32

DHT sensor library

Adafruit SSD1306 & GFX library

PubSubClient (MQTT)

NewPing (cho cảm biến HC-SR04)
