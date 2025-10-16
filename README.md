🌿 Smart Garden – Hệ thống nhà kính thông minh
🧩 Giới thiệu

Smart Garden là một hệ thống giám sát và điều khiển tự động môi trường nhà kính, giúp người dùng theo dõi và điều chỉnh các yếu tố như nhiệt độ, độ ẩm, ánh sáng, và mực nước.
Dự án sử dụng ESP32 làm bộ xử lý trung tâm, kết hợp với các cảm biến, relay, màn hình OLED và giao thức MQTT để hỗ trợ điều khiển – giám sát từ xa qua Internet.

🖥️ Tính năng chính

🌡️ Giám sát nhiệt độ, độ ẩm, ánh sáng, và mực nước theo thời gian thực

💧 Tự động bật/tắt thiết bị (bơm, quạt, đèn) theo ngưỡng cài đặt

📡 Kết nối WiFi và giao tiếp MQTT để điều khiển, giám sát từ xa qua ứng dụng hoặc dashboard

🧠 Hỗ trợ chế độ thủ công thông qua nút nhấn

📺 Màn hình OLED SSD1306 hiển thị thông tin cảm biến và trạng thái hệ thống

🔔 LED cảnh báo hiển thị hoạt động hoặc lỗi của hệ thống

🔌 Cảm biến và Cơ cấu chấp hành

DHT22: Đo nhiệt độ và độ ẩm môi trường.

LDR Sensor: Đo cường độ ánh sáng.

HC-SR04: Đo mực nước trong bể chứa.

Module Relay: Điều khiển bật/tắt thiết bị (đèn, quạt, bơm nước, phun sương) dựa trên dữ liệu cảm biến hoặc lệnh người dùng.

Button (nút nhấn): Chuyển chế độ hoạt động (tự động/thủ công).

LED cảnh báo: Hiển thị trạng thái hoạt động của hệ thống.

🖥️ Hiển thị

Màn hình OLED SSD1306 hiển thị trực tiếp thông tin cảm biến và trạng thái thiết bị.

Cập nhật giá trị theo thời gian thực, giúp người dùng dễ dàng theo dõi điều kiện môi trường.

📊 Kết quả đạt được

Hoàn thiện mô hình mô phỏng nhà kính thông minh hoạt động ổn định.

Thu thập và hiển thị dữ liệu cảm biến theo thời gian thực qua giao thức MQTT.

Điều khiển thiết bị tự động (đèn, quạt, bơm) dựa trên ngưỡng cài đặt môi trường.

Hiển thị thông tin cảm biến và trạng thái thiết bị rõ ràng trên màn hình OLED.

MQTT hoạt động ổn định, cho phép kết nối từ xa và kiểm thử dễ dàng.

Cấu trúc mã được tách biệt thành từng module, dễ mở rộng và bảo trì.
