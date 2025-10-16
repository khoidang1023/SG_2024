🌿 Smart Garden – Hệ thống nhà kính thông minh
🧩 Giới thiệu

Smart Garden là hệ thống giám sát và điều khiển tự động môi trường nhà kính, cho phép theo dõi và điều chỉnh nhiệt độ, độ ẩm, ánh sáng và mực nước một cách thông minh.
Dự án sử dụng ESP32 làm bộ xử lý trung tâm, kết hợp với cảm biến, màn hình OLED, module relay và giao thức MQTT để giám sát – điều khiển từ xa qua Internet.

☁️ Công nghệ IoT

ESP32 đóng vai trò vi điều khiển trung tâm, kết nối Wi-Fi để thu thập và truyền dữ liệu.

Giao thức MQTT được sử dụng để:

Gửi dữ liệu cảm biến lên broker.

Nhận lệnh điều khiển thiết bị từ người dùng.

Kiểm thử và giám sát qua công cụ MQTT.fx hoặc dashboard.

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




PubSubClient (MQTT)

NewPing (HC-SR04)
