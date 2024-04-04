# Cub3D Projesi
Bu proje, 42 (Fransız eğitim kurumu) programının bir parçası olarak sunulan Cub3D projesinin çözümünü içerir. Cub3D, Wolfenstein 3D tarzında basit bir 3D grafik motoru oluşturmayı amaçlar.
## Başlangıç
Bu projeyi klonlamak için aşağıdaki komutu kullanabilirsiniz:
```shell
git clone https://github.com/sizin-kullanici-adi/cub3d.git
```
## Kurulum
Projeyi çalıştırmak için `make` komutunu kullanarak bir Makefile oluşturun:
```shell
make
```
Bu, `Cub3D` adında bir yürütülebilir dosya oluşturacaktır. Oluşturulan dosyayı çalıştırarak programı başlatabilirsiniz:
```shell
./Cub3D harita.cub
```
Not: `harita.cub`, başlatmak istediğiniz harita dosyasının adıdır.
## Kullanım
Cub3D, `.cub` uzantılı bir harita dosyasını alarak çalışır. Harita dosyası, oyun dünyasının oluşturulması ve ayarlarının belirlenmesi için kullanılır. Örnek bir harita dosyası aşağıdaki gibi olabilir:
```
R 1920 1080
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
S ./textures/sprite.xpm
F 220,100,0
C 0,0,255
1111111111111
1000000000001
1010022200101
1034567890101
1010022200101
1000000000001
1111111111111
```
Harita dosyasının içeriğinde çeşitli ayarlar ve harita verileri bulunur.
