# Bomber Game

## 📝 Giới thiệu
Dự án này là một trò chơi đặt bom (Bomber Game) được phát triển bằng **MFC (Microsoft Foundation Class)**, trong khuôn khổ môn học **Lập trình hướng đối tượng**.  
Trò chơi tái hiện lối chơi cổ điển, nơi người chơi đặt bom để phá vật cản, tiêu diệt kẻ thù, và vượt qua các màn chơi với độ khó tăng dần.

Dự án được thực hiện bởi nhóm sinh viên **Trường Đại học Tây Nguyên**, dưới sự hướng dẫn của cô **Trương Thị Hương Giang**.

---

## ✨ Tính năng nổi bật
- **Điều khiển nhân vật**: Dễ dàng di chuyển bằng các phím `W` , `A` , `S` , `D`.
- **Hệ thống bom**: Đặt bom, phá vật cản và tiêu diệt kẻ thù.
- **Kẻ thù AI thông minh**: Di chuyển ngẫu nhiên hoặc bám sát người chơi.
### 🆙 Đang có ý tưởng nâng cấp.
- **Thu thập vật phẩm**: Tăng tốc độ, tăng số lượng bom, mở rộng phạm vi nổ.
- **Hiệu ứng đồ họa và âm thanh sống động**.
- **Hệ thống cấp độ**: Độ khó tăng dần qua từng màn chơi.

---

## 🛠 Công nghệ sử dụng
- **Ngôn ngữ lập trình**: C++
- **Thư viện giao diện**: Microsoft Foundation Class (MFC)
- **Công cụ phát triển**: Microsoft Visual Studio
- **Hệ thống thiết kế**: Lập trình hướng đối tượng (OOP)

---

## 💻 Yêu cầu hệ thống
- **Hệ điều hành**: Windows 7/8/10/11
- **Visual Studio**: Phiên bản 2019 trở lên
- **Thư viện hỗ trợ**:  
  - MFC (Microsoft Foundation Class)  
  - GDI+ (nếu sử dụng đồ họa mở rộng)

---

## 🚀 Hướng dẫn cài đặt và chạy

### Clone dự án từ GitHub
```bash
git clone https://github.com/HuyHoangI4t/J97.git
cd J97
```

### Mở dự án trong Visual Studio
- Tìm tệp `Bomb.sln` và mở bằng **Microsoft Visual Studio**.

### Cài đặt MFC trong Visual Studio
1. Mở **Visual Studio Installer**.
2. Chọn **Modify** cho phiên bản Visual Studio bạn đang sử dụng.
3. Đảm bảo đã bật tùy chọn **Desktop Development with C++** và **MFC/ATL Support**.

### Biên dịch và chạy dự án
1. Trong Visual Studio, nhấn **Ctrl + Shift + B** hoặc vào menu **Build > Build Solution** để biên dịch.
2. Sau khi biên dịch thành công, nhấn **F5** để chạy trò chơi.

---

## 📁 Cấu trúc thư mục
```plaintext
J97/
├── src/                  # Mã nguồn chính
│   ├── MainFrm.cpp       # Cửa sổ chính của trò chơi
│   ├── ChildView.cpp     # Logic xử lý trò chơi
│   ├── Player.cpp        # Quản lý nhân vật người chơi
│   ├── Enemy.cpp         # Xử lý hành vi của kẻ thù
│   └── Boom.cpp          # Điều khiển bom và vụ nổ
│   └── Maze.cpp          # Mê cung và hiệu ứng
├── res/                  # Tài nguyên trò chơi
│   ├── images/           # Hình ảnh nhân vật, chướng ngại vật, bom
│   ├── sounds/           # Âm thanh vụ nổ, di chuyển
├── docs/                 # Tài liệu liên quan
│   ├── report.pdf        # Báo cáo phát triển
│   └── design_docs/      # Thiết kế giao diện và logic
└── README.md             # Tệp hướng dẫn
```

---

## 🤝 Đóng góp cho dự án
Chúng tôi luôn chào đón các ý tưởng và cải tiến từ cộng đồng.

### Các bước đóng góp:
1. Fork repository này.
2. Tạo một nhánh mới để thực hiện thay đổi:
   ```bash
   git checkout -b feature-name
   ```
3. Commit thay đổi của bạn:
   ```bash
   git commit -m "Mô tả thay đổi"
   ```
4. Gửi pull request đến nhánh chính (main).

---

## 👨‍💻 Nhóm phát triển
- **Nguyễn Huy Hoàng**: Quản lý dự án, lập trình chính.
- **Nguyễn Thị Mỹ Duyên**: Phát triển giao diện.
- **Phạm Quang Đức**: Thiết kế đồ họa và hiệu ứng âm thanh.
- **Ngô Tuấn Kiệt**: Edit video và làm báo cáo.
- **Liên hệ nhóm**: 📩[huyhoangpro187@gmail.com](huyhoangpro187@gmail.com)

---

## 💌 Lời cảm ơn
Chúng tôi xin gửi lời cảm ơn sâu sắc đến cô **Trương Thị Hương Giang** và các thầy cô trong Khoa Khoa học Tự nhiên và Công nghệ, Trường Đại học Tây Nguyên, đã hỗ trợ và đồng hành trong quá trình thực hiện dự án này.

---
