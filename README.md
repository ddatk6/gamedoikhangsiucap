# narutovssasuke
       ĐẠI HỌC QUỐC GIA HÀ NỘI   	CỘNG HÒA XÃ HỘI CHỦ NGHĨA VIỆT NAM
TRƯỜNG ĐẠI HỌC CÔNG NGHỆ                 	Độc lập - Tự do - Hạnh phúc
                  	c&d                                      	====================
BÁO CÁO BÀI TẬP LỚP MÔN LẬP TRÌNH NÂNG CAO
Sinh viên: Doãn Minh Đạt           Sinh ngày:19/10/2006
Ngành học:Công Nghệ Thông Tin  Lớp: INT2215 5
Tên game : Naruto vs Sasuke
Lối chơi, logic của game:
Lối chơi
Đối kháng 1 đối 1:
 Game mang tính chất đối kháng giữa hai nhân vật (ví dụ: Naruto và Sasuke). Mỗi người chơi điều khiển một nhân vật với các chiêu thức riêng biệt.


Hệ thống chiêu thức đa dạng:
 Nhân vật có thể di chuyển, nhảy, tấn công cơ bản và sử dụng các chiêu đặc biệt có nhiều giai đoạn (ví dụ: các action index 7, 8, 9, 10 cho chiêu đặc biệt).


Quản lý năng lượng & thời gian hồi chiêu (cooldown):
 Mỗi hành động có mức tiêu hao năng lượng và một thời gian hồi (cooldown) được định nghĩa trong mảng constants. Người chơi phải cân nhắc chiến thuật, không thể spam chiêu liên tục.


Logic game
Cập nhật trạng thái thông qua ECS:
 Mô hình Entity-Component-System được áp dụng để quản lý trạng thái, animation, input và collision. Các thành phần như Transform, Sprite, Animation, HealthEnergy, Collider và Controller tương tác nhằm tạo nên logic hoạt động của game.


Hệ thống animation:
 AnimationComponent xử lý chuyển đổi giữa các trạng thái (đứng, chạy, nhảy, tấn công, chiêu đặc biệt, và trạng thái “bị đánh”) dựa trên input và thời gian. Hệ thống sử dụng biến skillPhase để điều chỉnh giai đoạn của chiêu đặc biệt và cập nhật cooldown sau khi animation kết thúc.


Collision & Damage:
 Hệ thống va chạm dựa trên phương pháp AABB kiểm tra các đối tượng. Khi một đối thủ bị trúng chiêu có sát thương (damage > 0), hàm tryDecreaseHealth() được gọi để trừ HP và kích hoạt hiệu ứng “hit stun”, hiển thị animation bị đánh (action index được định nghĩa riêng).

Đồ họa, âm thanh:
Âm thanh
SDL_mixer:
 Dự án tích hợp SDL_mixer để xử lý âm thanh. Các file âm thanh được load từ thư mục “assest” bao gồm các hiệu ứng như:


moveSound: Âm thanh khi di chuyển.


punchSound & cutSound: Âm thanh khi thực hiện các chiêu tấn công cơ bản.


rasenganSound & ChidoriSound: Âm thanh của chiêu đặc biệt.


hurtSound & K_O: Âm thanh khi nhân vật nhận damage hoặc bị hạ gục.


Phối hợp âm thanh – đồ họa:
 Âm thanh được phát đồng bộ với các hành động của nhân vật (di chuyển, tấn công, sử dụng chiêu) để tăng tính sống động và tạo trải nghiệm hấp dẫn cho người chơi.


Đồ họa
Sprite Sheets & Animation:
 Game sử dụng sprite sheets để hiển thị nhiều trạng thái của nhân vật. Các thông số về vị trí, kích thước, số frame, tốc độ animation, sát thương, tiêu hao năng lượng, và thời gian hồi được định nghĩa trong các mảng constants (Player1Constants và Player2Constants).


Hiệu ứng đặc biệt:
 Khi nhân vật nhận damage, hiệu ứng “bị đánh” (hit animation) được hiển thị, kèm theo hiệu ứng màu (ví dụ, chuyển sang màu đỏ) để thể hiện trạng thái “hit stun”.


Render mượt mà:
 SDL_RenderCopy và các hàm liên quan được sử dụng để render sprite dựa trên srcRect và destRect được tính toán từ các thành phần của TransformComponent và AnimationComponent, đảm bảo hoạt ảnh mượt mà và đúng thời gian.



Cấu trúc của project game:
Tổ chức thư mục
Thư mục “ECS”:
 Chứa các file định nghĩa hệ thống Entity-Component-System như ECS.h, Components.h, và các component cụ thể (TransformComponent, SpriteComponent, AnimationComponent, ColliderComponent, HealthEnergyComponent, …).


Thư mục “assest”:
 Chứa các file hình ảnh (sprite sheets, map, UI) và âm thanh (file WAV cho các hiệu ứng âm thanh) được sử dụng trong game.


Các file nguồn chính:
 Các file như game.cpp, AnimationComponent.cpp, TextureManager.cpp, Collision.cpp,… đảm nhiệm khởi tạo cửa sổ, vòng lặp chính, cập nhật, render và dọn dẹp game.


Module hóa và tính mở rộng
Hệ thống ECS:
 Giúp tách rời logic cập nhật của từng thành phần, cho phép dễ dàng thêm, sửa hoặc loại bỏ các chức năng mà không ảnh hưởng đến toàn bộ hệ thống.


Manager:
 Quản lý vòng đời của các Entity, đảm bảo cập nhật và render theo thứ tự, làm sạch các Entity không còn hoạt động.



Các chức năng đã cài được cho game:Chức năng cơ bản
Di chuyển & Nhảy:
 Người chơi có thể điều khiển nhân vật di chuyển sang trái, phải và nhảy. Trạng thái di chuyển được phản ánh qua animation và âm thanh (moveSound).


Tấn công & Chiêu Đặc Biệt:


Các chiêu tấn công cơ bản (action index 3, 5, 6) có hiệu ứng âm thanh (punchSound, cutSound) và tiêu hao năng lượng.


Chiêu đặc biệt (với nhiều giai đoạn: 7, 8, 9, 10) cho phép tạo ra hiệu ứng tấn công mạnh mẽ và có hiệu ứng dash, đồng thời tiêu hao năng lượng và có thời gian hồi (cooldown).


Hệ thống HP & Năng lượng:
 HealthEnergyComponent quản lý HP và năng lượng của nhân vật, với các phương thức giảm HP (tryDecreaseHealth) khi bị tấn công và tăng năng lượng khi thực hiện các hành động nhất định.


Collision & Hiệu Ứng Bị Đánh:
 Khi một nhân vật bị tấn công và trúng đối thủ, hệ thống collision kiểm tra va chạm và kích hoạt hiệu ứng nhận damage. Nhân vật bị đánh sẽ hiển thị animation “bị đánh” (action index 11) trong khoảng thời gian hit stun, ngăn không cho điều khiển lại ngay lập tức.


Âm thanh & Phản hồi người chơi:
 Âm thanh được phát đồng bộ với các hành động của nhân vật để tạo ra phản hồi trực quan và âm thanh, giúp người chơi cảm nhận được mỗi hành động (di chuyển, tấn công, chiêu đặc biệt, nhận damage) một cách sống động.


Chức năng nâng cao
Hệ thống Cooldown:
 Mỗi hành động đều có thời gian hồi (cooldown) được định nghĩa trong constants, giúp ngăn chặn việc spam chiêu và tạo nên chiến thuật trong game.


Hiệu ứng âm thanh động:
 Âm thanh được tích hợp không chỉ cho các chiêu thức mà còn cho chuyển động, tạo nên một không gian game phong phú và sống động.


Tương tác đa nền tảng của các Component:
 Hệ thống ECS cho phép các thành phần như AnimationComponent, Controller, HealthEnergyComponent và ColliderComponent tương tác lẫn nhau một cách linh hoạt, tạo nên một game có logic phức tạp nhưng dễ bảo trì và mở rộng.


