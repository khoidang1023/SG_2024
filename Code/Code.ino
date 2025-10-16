#include <Wire.h>                // Thư viện hỗ trợ giao tiếp I2C, cần thiết để giao tiếp với các thiết bị I2C như MPU6050.
#include <MPU6050_tockn.h>       // Thư viện hỗ trợ làm việc với cảm biến MPU6050, cung cấp các hàm để đọc dữ liệu từ cảm biến.
#include <Adafruit_GFX.h>        // Thư viện đồ họa cơ bản hỗ trợ việc vẽ và hiển thị văn bản trên màn hình OLED.
#include <Adafruit_SSD1306.h>    // Thư viện hỗ trợ màn hình OLED SSD1306, cho phép vẽ đồ họa và hiển thị văn bản trên màn hình OLED.
#include <ESP32Servo.h>          // Thư viện điều khiển servo cho ESP32, cung cấp các hàm để điều khiển các servo motor.
#include <freertos/FreeRTOS.h>  // Thư viện chính của FreeRTOS, cung cấp các định nghĩa và hàm cần thiết cho việc sử dụng hệ điều hành thời gian thực trên ESP32
#include <freertos/task.h>      // Thư viện chứa các hàm liên quan đến task, cho phép tạo, xóa và quản lý các task trong FreeRTOS

#define SCREEN_WIDTH 128         // Định nghĩa độ rộng của màn hình OLED là 128 pixel.
#define SCREEN_HEIGHT 64         // Định nghĩa độ cao của màn hình OLED là 64 pixel.
#define OLED_RESET    -1         // Định nghĩa chân reset của màn hình OLED. -1 có nghĩa là không sử dụng chân reset, vì màn hình OLED SSD1306 không yêu cầu chân reset để hoạt động.

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Khởi tạo đối tượng display thuộc lớp Adafruit_SSD1306

MPU6050 mpu6050(Wire); // Khởi tạo đối tượng mpu6050 thuộc lớp MPU6050

// Chân điều khiển các servo
#define SERVO_X_PIN 14  // Định nghĩa chân 14 của ESP32 kết nối SERVO_X
#define SERVO_Y_PIN 12  // Định nghĩa chân 12 của ESP32 kết nối SERVO_Y
#define SERVO_Z_PIN 13  // Định nghĩa chân 13 của ESP32 kết nối SERVO_Z

Servo servoX;  // Khởi tạo đối tượng Servo cho servo X
// Tạo một đối tượng servoX từ lớp Servo.
// Đối tượng này sẽ được sử dụng để điều khiển servo kết nối với chân SERVO_X_PIN.

Servo servoY;
Servo servoZ;  

float accelX, accelY, accelZ; // Gia tốc theo trục X, Y, Z (m/s²)
float gyroX, gyroY, gyroZ;    // Con quay hồi chuyển theo trục X, Y, Z (°/sec)
float angleX, angleY, angleZ; // Góc nghiêng trên các trục X, Y, Z (°)
int servoXPos, servoYPos, servoZPos;  // Góc của servo X, Y, Z (°)

// Task handles
TaskHandle_t TaskReadMPUHandle = NULL;    // Con trỏ để quản lý task đọc dữ liệu từ cảm biến MPU6050
TaskHandle_t TaskPrintHandle = NULL;      // Con trỏ để quản lý task in dữ liệu ra (ví dụ như Serial Monitor)
TaskHandle_t TaskDisplayHandle = NULL;    // Con trỏ để quản lý task hiển thị dữ liệu lên màn hình (ví dụ: OLED, LCD)
TaskHandle_t TaskServoHandle = NULL;      // Con trỏ để quản lý task điều khiển servo

void setup() {
  Serial.begin(115200);  // Khởi tạo Serial Monitor với tốc độ 115200 baud

  Wire.begin();  // Khởi tạo giao tiếp I2C và màn hình OLED
 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Bắt đầu giao tiếp với màn hình OLED SSD1306.
    // - `SSD1306_SWITCHCAPVCC` chỉ định rằng màn hình sẽ sử dụng điện áp nguồn từ chân VCC.
    // - `0x3C` là địa chỉ I2C của màn hình OLED
    
    Serial.println(F("OLED không thể khởi tạo!"));
    // Nếu màn hình OLED không khởi tạo thành công, in thông báo lỗi ra Serial Monitor.
    // Hàm `F()` giúp giảm sử dụng bộ nhớ bằng cách lưu chuỗi ký tự trong bộ nhớ chương trình thay vì RAM.

    while (1);
    // Vòng lặp vô hạn để dừng chương trình nếu màn hình không khởi tạo được.
  }

  display.clearDisplay();
  // Xóa màn hình OLED để chuẩn bị cho việc hiển thị dữ liệu mới.

  mpu6050.begin();
  // Khởi tạo cảm biến MPU6050. 

  mpu6050.calcGyroOffsets(true);
  // Tính toán các bù trừ cho con quay hồi chuyển của MPU6050.
  // Tham số `true` chỉ định rằng quá trình tính toán bù trừ nên thực hiện và cảm biến cần thời gian đứng yên.

  // Khởi tạo các servo
  servoX.attach(SERVO_X_PIN);  // Kết nối servo X vào chân 14
  // Kết nối servo X với chân GPIO 14 của ESP32
  // Hàm `attach` thiết lập chân GPIO để điều khiển servo motor và cung cấp tín hiệu PWM cần thiết cho servo hoạt động.

  servoY.attach(SERVO_Y_PIN); 
  servoZ.attach(SERVO_Z_PIN);


  // Thiết lập các task trong FreeRTOS
  xTaskCreate(
    TaskReadMPU6050,     // Tên của hàm thực thi sẽ được gọi khi tác vụ chạy
    "TaskReadMPU",       // Tên của tác vụ để nhận diện trong hệ thống
    2048,                // Kích thước bộ nhớ (stack size) dành cho tác vụ, tính bằng byte
    NULL,                // Con trỏ đến dữ liệu đầu vào cho tác vụ (NULL nếu không cần truyền dữ liệu)
    1,                   // Mức ưu tiên của tác vụ (1 là mức ưu tiên thấp)
    &TaskReadMPUHandle                // Con trỏ đến handle của tác vụ (NULL nếu không cần lưu handle)
  );

  xTaskCreate(TaskPrint, "TaskPrint", 2048, NULL, 1, &TaskPrintHandle);
  xTaskCreate(TaskDisplayOLED, "TaskDisplay", 2048, NULL, 1, &TaskDisplayHandle);
  xTaskCreate(TaskControlServo, "TaskServo", 2048, NULL, 1, &TaskServoHandle);
}

void loop() {
  // Không sử dụng loop() vì các task được quản lý bởi FreeRTOS.
}

// Task 1: Đọc dữ liệu từ cảm biến MPU6050
void TaskReadMPU6050(void* pvParameters) {
  while (1) {
    mpu6050.update(); // Cập nhật dữ liệu từ cảm biến MPU6050

    accelX = mpu6050.getAccX() * 9.8; // Đọc giá trị gia tốc theo trục X từ cảm biến và chuyển đổi từ g (gia tốc trọng trường) sang m/s²
    accelY = mpu6050.getAccY() * 9.8;
    accelZ = mpu6050.getAccZ() * 9.8;

    gyroX = mpu6050.getGyroX(); // Đọc giá trị con quay hồi chuyển theo trục X từ cảm biến (đơn vị là độ/giây)
    gyroY = mpu6050.getGyroY(); 
    gyroZ = mpu6050.getGyroZ();

    angleX = mpu6050.getAngleX(); // Đọc giá trị góc nghiêng theo trục X từ cảm biến (đơn vị là độ)
    angleY = mpu6050.getAngleY(); 
    angleZ = mpu6050.getAngleZ(); 

    vTaskDelay(200 / portTICK_PERIOD_MS); // Tạm dừng tác vụ trong 200ms để tránh tiêu tốn quá nhiều tài nguyên CPU
  }
}

// Task 2: In giá trị ra Serial
void TaskPrint(void* pvParameters) {
  while (1) {
    // Hiển thị các giá trị gia tốc trên cùng một hàng
    Serial.print("Gia toc (m/s²) X: ");
    Serial.print(accelX);  // In giá trị gia tốc theo trục X
    Serial.print(", Y: ");
    Serial.print(accelY);  // In giá trị gia tốc theo trục Y
    Serial.print(", Z: ");
    Serial.println(accelZ);  // In giá trị gia tốc theo trục Z và kết thúc dòng

    // Hiển thị các giá trị con quay hồi chuyển trên cùng một hàng
    Serial.print("Con quay (°/sec) X: ");
    Serial.print(gyroX);
    Serial.print(", Y: ");
    Serial.print(gyroY);
    Serial.print(", Z: ");
    Serial.println(gyroZ);

    // Hiển thị các góc nghiêng trên cùng một hàng
    Serial.print("Goc (°) X: ");
    Serial.print(angleX);
    Serial.print(", Y: ");
    Serial.print(angleY);
    Serial.print(", Z: ");
    Serial.println(angleZ);

    // Hiển thị giá trị góc quay của các servo trên cùng một hàng
    Serial.print("Servo (°) X: ");
    Serial.print(servoXPos);
    Serial.print(", Y: ");
    Serial.print(servoYPos);
    Serial.print(", Z: ");
    Serial.println(servoZPos);

    // Delay giữa các lần in
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Task 3: Hiển thị lên OLED
void TaskDisplayOLED(void* pvParameters) {
  while (1) {  // Vòng lặp vô hạn để task tiếp tục chạy liên tục
    display.clearDisplay();  // Xóa màn hình OLED để chuẩn bị cho việc hiển thị dữ liệu mới

    display.setTextSize(1); // Thiết lập kích thước chữ nhỏ
    display.setTextColor(WHITE); // Thiết lập màu chữ là trắng

    // Hiển thị giá trị góc X
    display.setCursor(0, 0);  // Đặt con trỏ hiển thị ở vị trí (0, 0), dòng đầu tiên của màn hình
    display.print("Goc X: "); // In tiêu đề cho giá trị góc X
    display.print(angleX, 1); // In giá trị góc X với 1 chữ số thập phân

    // Hiển thị giá trị góc Y
    display.setCursor(0, 16); 
    display.print("Goc Y: "); 
    display.print(angleY, 1); 

    // Hiển thị giá trị góc Z
    display.setCursor(0, 32); 
    display.print("Goc Z: "); 
    display.print(angleZ, 1); 

    display.display(); // Cập nhật màn hình OLED với các thay đổi vừa thực hiện

    vTaskDelay(500 / portTICK_PERIOD_MS); 
  }
}

// Task 4: Điều khiển servo dựa trên góc nghiêng
void TaskControlServo(void* pvParameters) {
  while (1) { 
    // Chuyển đổi góc nghiêng X (-90 đến 90 độ) thành giá trị góc cho servo (0 đến 180 độ)
    servoXPos = constrain(map(angleX, -90, 90, 0, 180), 0, 180); 
    // `map` chuyển đổi giá trị góc nghiêng X từ phạm vi -90 đến 90 độ sang phạm vi góc servo từ 0 đến 180 độ
    // `constrain` đảm bảo giá trị góc servo không vượt quá phạm vi 0 đến 180 độ

    servoYPos = constrain(map(angleY, -90, 90, 0, 180), 0, 180); 
    servoZPos = constrain(map(angleZ, -90, 90, 0, 180), 0, 180); 

    // Điều khiển servo X với giá trị góc đã tính toán
    servoX.write(servoXPos); 
    // Gửi tín hiệu điều khiển đến servo X để điều chỉnh góc của nó

    servoY.write(servoYPos); 
    servoZ.write(servoZPos); 

    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}