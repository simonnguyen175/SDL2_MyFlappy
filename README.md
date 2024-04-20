### SDL2 Game Project `FLappyHunter`
### Sinh viên: Nguyễn Sỹ Mạnh 
### MSV: 23020107  

### GIỚI THIỆU GAME 
* Game FlappyHunter dựa theo ý tưởng game FLappyBird, có bổ sung thêm các tính năng, trạng thái của cột để tăng độ khó cho game,  
ngoài ra còn thêm các threats ở các ống và súng cho nhân vật đi diệt threats và đi qua ống và bổ sung thêm phép bổ trợ tăng tốc
cho nhân vật. 
* Người chơi cũng có thể đổi nhân vật nếu muốn.
* Link demo game: https://drive.google.com/file/d/1EqwtNpUgxOd1Z6pkwuX9t9p2CzTwhfcU/view?usp=sharing
***
### CÀI ĐẶT GAME
* Bạn cần cài đặt compiler GCC về máy: https://www.msys2.org/
* Tải hoặc clone repo về máy tính.
* Nhấn vào file main.exe để chạy và chơi game.
* Nếu muốn phát triển game bạn tải Visual Studio Code về máy, mở folder game đã được giải nén trên Vscode, và phát triển game theo
ý bạn.
* Lưu ý để chạy được game trên Vscode bạn cần một file Makefile như dưới đây: 
  ```php
  all: main run
  main: src/main.cpp
        g++ -std=c++17 -Iinclude -Iinclude/SDL2 -Iinclude/headers -Llib src/*.cpp -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
  run: main 
      ./main.exe
  .PHONY: all run
  ```
 * Và chạy lệnh này ở terminal để chạy game:
 ```php
 mingw32-make
 ```
***
### HƯỚNG DẪN CHƠI
* Khi vào giao diện ban đầu của game bạn nhấn `Esc` hiện ra menu của game, khi hiện menu có các tùy chọn đổi nhân vật, tắt/bật  
âm thanh. Ở phía góc trái dưới màn hình hiển thị `Help`, bạn nhấn vào để xem cách chơi, góc phải dưới màn hình hiển thị `Exit` để
bạn thoát game.
* Bạn nhấn click chuột để bắt đầu chơi game.
***
### TÀI LIỆU THAM KHẢO 
* Tham khảo các hàm trong thư viện SDL2 trên https://lazyfoo.net/
* Tham khảo các hướng dẫn về lập trình game FLappy Bird.
***
### NGƯỠNG ĐIỂM MONG MUỐN 
* 9 ~ 9.5
* Lí do em mong muốn được ngưỡng điểm trên do em đã bổ sung đáng kể về nội dung đáng kể và các tính năng mới so với game FlappyBird, đồ họa
đẹp, chuyển động mượt mà, và âm thanh sống động.  
