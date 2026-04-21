![image](https://github.com/username/repo/blob/main/image.png)

![image](https://github.com/username/repo/blob/main/image.png)



# 🌱 Irrigation system 🌱

---

# 📌 نظرة عامة على المشروع

هذا المشروع عبارة عن **نظام ري ذكي** باستخدام الأردوينو. يقوم النظام بقراءة مستوى رطوبة التربة باستخدام حساس الرطوبة، ثم تشغيل أو إيقاف مضخة المياه تلقائياً باستخدام وحدة Relay. كما يتم عرض مستوى الرطوبة وحالة المضخة على شاشة LCD تعمل بتقنية I2C.

---

# 🔌 المكونات المطلوبة

* Arduino UNO
* Soil Moisture Sensor
* Relay Module
* Water Pump
* شاشة LCD 16×2 تعمل بتقنية I2C
* Jumper Wires

---

# 🔧 التوصيلات

| المكون              | منفذ الأردوينو |
| ------------------- | -------------- |
| خرج حساس الرطوبة AO | A0             |
| Relay IN            | D2             |
| LCD SDA             | A4             |
| LCD SCL             | A5             |
| LCD VCC             | 5V             |
| LCD GND             | GND            |
| Relay VCC           | 5V             |
| Relay GND           | GND            |

---

# ⚙️ شرح الكود

## 1️⃣ استدعاء المكتبات

هذه المكتبات تسمح للأردوينو بالتواصل مع شاشة LCD باستخدام بروتوكول I2C.

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

---

## 2️⃣ تهيئة الشاشة

يتم هنا تحديد عنوان الشاشة وحجمها (16 عمود × صفين).

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

---

## 3️⃣ تعريف أطراف التوصيل

يتم تحديد أطراف الأردوينو المتصلة بالحساس والريلاي.

```cpp
const int moisturePin = A0;
const int relayPin = 2;
```

---

## 4️⃣ دالة الإعداد Setup

يتم تنفيذها مرة واحدة عند تشغيل الأردوينو. تقوم بتهيئة الاتصال التسلسلي، وضبط وضع الريلاي، وإظهار رسالة البداية على الشاشة.

```cpp
void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM STARTING");
  delay(3000);
  lcd.clear();
}
```

---

## 5️⃣ قراءة قيمة الحساس

يتم قراءة القيمة التناظرية من حساس الرطوبة.

```cpp
int value = analogRead(moisturePin);
```

---

## 6️⃣ عرض قيمة الحساس على Serial Monitor

يتم عرض قيمة الرطوبة على شاشة Serial Monitor لمتابعة القراءات.

```cpp
Serial.print("Moisture value: ");
Serial.println(value);
```

---

## 7️⃣ التحكم في تشغيل المضخة

إذا كانت التربة جافة يتم تشغيل المضخة، وإذا كانت رطبة يتم إيقافها.

```cpp
if (value > 950) {
  digitalWrite(relayPin, LOW);
  lcd.print("Pump: ON ");
} else {
  digitalWrite(relayPin, HIGH);
  lcd.print("Pump: OFF");
}
```

---

## 8️⃣ تحديد مستوى الرطوبة

يقسم النظام مستوى الرطوبة إلى ثلاث مستويات:

HIGH → التربة رطبة
MID → رطوبة متوسطة
LOW → التربة جافة

```cpp
if (value < 300) {
  lcd.print("Moisture: HIGH ");
} else if (value >= 300 && value <= 950) {
  lcd.print("Moisture: MID  ");
} else {
  lcd.print("Moisture: LOW  ");
}
```

---

## 9️⃣ التأخير بين القراءات

يضيف تأخير بسيط قبل قراءة الحساس مرة أخرى.

```cpp
delay(500);
```

---

# ✅ ملخص عمل النظام

1. قراءة مستوى رطوبة التربة
2. عرض القيمة على الشاشة
3. تشغيل المضخة عند جفاف التربة
4. إيقاف المضخة عند زيادة الرطوبة
5. تحديث الحالة كل نصف ثانية

---

# 🚀 تطوير المشروع مستقبلاً

* إضافة إشعارات على الهاتف
* إضافة جدول ري تلقائي
* إضافة حساس مستوى المياه
* التحكم عن بعد باستخدام WiFi

# 🌱 Smart Irrigation System – Arduino + Soil Moisture Sensor + Relay + I2C LCD

---

# 📌 Project Overview

This project is a **smart irrigation system** using Arduino. It reads soil moisture using a moisture sensor and automatically turns the water pump ON or OFF using a relay module. The moisture level and pump status are displayed on an I2C LCD screen.

---

# 🔌 Components Required

* Arduino UNO
* Soil Moisture Sensor
* Relay Module
* Water Pump
* I2C LCD (16x2)
* Jumper Wires

---

# 🔧 Hardware Connections

| Component            | Arduino Pin |
| -------------------- | ----------- |
| Moisture Sensor (AO) | A0          |
| Relay IN             | D2          |
| LCD SDA              | A4          |
| LCD SCL              | A5          |
| LCD VCC              | 5V          |
| LCD GND              | GND         |
| Relay VCC            | 5V          |
| Relay GND            | GND         |

---

# ⚙️ Code Explanation

## 1️⃣ Including Libraries

These libraries allow Arduino to communicate with the LCD using the I2C protocol.

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

---

## 2️⃣ LCD Initialization

Defines the LCD address and its size (16 columns × 2 rows).

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

---

## 3️⃣ Pin Definitions

Defines which Arduino pins are connected to the sensor and relay.

```cpp
const int moisturePin = A0;
const int relayPin = 2;
```

---

## 4️⃣ Setup Function

Runs once when the Arduino starts. It initializes Serial Monitor, relay mode, and LCD startup message.

```cpp
void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM STARTING");
  delay(3000);
  lcd.clear();
}
```

---

## 5️⃣ Reading Sensor Value

Reads the analog value from the moisture sensor.

```cpp
int value = analogRead(moisturePin);
```

---

## 6️⃣ Display Sensor Value in Serial Monitor

Prints the moisture value for debugging and monitoring.

```cpp
Serial.print("Moisture value: ");
Serial.println(value);
```

---

## 7️⃣ Pump Control Logic

If soil is dry → pump turns ON.
If soil is wet → pump turns OFF.

```cpp
if (value > 950) {
  digitalWrite(relayPin, LOW);
  lcd.print("Pump: ON ");
} else {
  digitalWrite(relayPin, HIGH);
  lcd.print("Pump: OFF");
}
```

---

## 8️⃣ Moisture Level Classification

The system divides moisture into three levels:

HIGH → Wet soil
MID → Medium moisture
LOW → Dry soil

```cpp
if (value < 300) {
  lcd.print("Moisture: HIGH ");
} else if (value >= 300 && value <= 950) {
  lcd.print("Moisture: MID  ");
} else {
  lcd.print("Moisture: LOW  ");
}
```

---

## 9️⃣ Delay Between Readings

Adds a small delay before the next sensor reading.

```cpp
delay(500);
```

---

# ✅ System Behavior Summary

1. Reads soil moisture level
2. Displays value on LCD
3. Turns pump ON if soil is dry
4. Turns pump OFF if soil is wet
5. Updates status every 0.5 seconds

---

# 🚀 Future Improvements

* Add mobile notification support
* Add automatic scheduling
* Add water level sensor
* Add IoT control using WiFi
