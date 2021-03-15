#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

class Kamera {  /// Kamera Class ı
public:
	char model[50];
	int date;
	double resolution;
	double zoom;
	double focus;
	double storage;
	double weight;
	double price;
	int bagAlani;
	
	Kamera(int p_bagAlani, const char *p_model, int p_date, double p_resolution, double p_zoom, double p_focus, double p_storage, double p_weight, double p_price) {
		strcpy_s(model, p_model);
		date = p_date;
		resolution = p_resolution;
		zoom = p_zoom;
		focus = p_focus;
		storage = p_storage;
		weight = p_weight;
		price = p_price;
		bagAlani = p_bagAlani;
	}

	int getSize() {
		return 106;
	}

};
class ArrayUrunAd {  /// Urun Adına göre mantıksal arama ve sıralama yapmak için oluşturulmuş class
public:
	char urunAd[500][50];
	int RRN[500];
	int i = 0;

	ArrayUrunAd() {
	}

	void set(char p_urunAd[50], int p_RRN) {
		strcpy_s(urunAd[i], p_urunAd);
		RRN[i] = p_RRN;
		i++;
	}
};  
class ArrayUrunFiyat {  /// Urun Fiyatına göre mantıksal arama ve sıralama yapmak için oluşturulmuş class
public:
	double urunFiyat[500];
	int RRN[500];
	int i = 0;

	ArrayUrunFiyat() {

	}

	void set(double p_urunFiyat, int p_RRN) {
		urunFiyat[i] = p_urunFiyat;
		RRN[i] = p_RRN;
		i++;
	}
};
class ArrayBagAlani { /// Bag Alanina göre ekleme silme ve güncelleme yapmak için oluşturulmuş class

public:
	int bagAlani[500];
	int RRN[500];
	int i = 0;

	ArrayBagAlani() {

	}

	void set(int p_bagAlani, int p_RRN) {
		bagAlani[i] = p_bagAlani;
		RRN[i] = p_RRN;
		i++;
	}
};


ArrayUrunAd urunAdDizisiOkuSirala() { // Sırali binary dosyayı, urun adına göre siralı bir şekilde array a doldurur
	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // okunan bilgileri alabilmek için temp oluşturuldu
	ArrayUrunAd dizi;  // okunan bilgiler bu değişkene aktarılır

	ifstream fileRead; 
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in); // dosya okuma işlemi başlatıldı
	for (int i = 0; true; i++) { // i sayacı sürekli bir arttılırılarak döngü başlatıldı
		
			fileRead.seekg((i*temp.getSize()), ios::beg);   // kayıtları tek tek dolaşabilmek için kaydın byte uzaklığına gidildi
			fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
			fileRead.read(temp.model, 50);
			fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
			fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));  // kayıtlar tek tek okunup temp e gönderildi
		
			if (fileRead.eof())
			{
				break;  // dosyanın sonuna ulaşıldıysa döngüden çıkıldı
			}
			if (temp.model[0] != '*')
			{
				dizi.set(temp.model, i);  // eğer kayıt silinmediyse diziye eklendi
			}
			
	}
	fileRead.close();  // buraya kadar dosyadaki verilerin model ini ve rrn sini ram da tutulan geçici diziye aktardık.
	

	// şimdi dizi sıralanacak (Bouble sort kullanıldı)
	char tempUrunAd[50];  	int tempRRN;
	for (int i = 0; i < dizi.i; i++) { 
		for (int j = i - 1; j >= 0; j--) {
			if (strcmp(dizi.urunAd[j], dizi.urunAd[j + 1]) > 0) {
				strcpy_s(tempUrunAd, dizi.urunAd[j]);
				strcpy_s(dizi.urunAd[j], dizi.urunAd[j + 1]);
				strcpy_s(dizi.urunAd[j + 1], tempUrunAd);

				tempRRN = dizi.RRN[j];
				dizi.RRN[j] = dizi.RRN[j + 1];
				dizi.RRN[j + 1] = tempRRN;
			}
			else {
				break;
			}
		}
	}

	return dizi; // diziyi sıraladıktan sonra return ettik.
	// sıralamamızın amacı index dosyasında(geçici dizi) arama yapmak için binary search kullanılacak. 
	
}
ArrayUrunFiyat urunFiyatDizisiOkuSirala() { // Sırali binary dosyayı, urun fiyatına göre siralı bir şekilde array a doldurur

	// urunAdDizisiOkuSirala dizisindeki işlemlerin benzeri yapıldı. (anlatılmaya gerek duyulmadı)

	ArrayUrunFiyat dizi;

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);
	for (int i = 0; true; i++) {
		
			fileRead.seekg((i*temp.getSize()), ios::beg);  
			fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
			fileRead.read(temp.model, 50);
			fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
			fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
			
			
			if (fileRead.eof())
			{
				break;
			}
			if (temp.model[0] != '*')
			{
				dizi.set(temp.price, i);
			}
			
	}
	fileRead.close();

	double tempUrunFiyat;
	int tempRRN;
	for (int i = 0; i < dizi.i; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (double(dizi.urunFiyat[j + 1]) < double(dizi.urunFiyat[j])) {
				tempUrunFiyat = dizi.urunFiyat[j];
				dizi.urunFiyat[j] = dizi.urunFiyat[j + 1];
				dizi.urunFiyat[j + 1] = tempUrunFiyat;

				tempRRN = dizi.RRN[j];
				dizi.RRN[j] = dizi.RRN[j + 1];
				dizi.RRN[j + 1] = tempRRN;

			}
			else {
				break;
			}
		}
	}


	return dizi;
	
}
ArrayBagAlani bagAlaniDizisiOkuSirala() { // Sırali binary dosyayı, urun fiyatına göre siralı bir şekilde array a doldurur

										  // urunAdDizisiOkuSirala dizisindeki işlemlerin benzeri yapıldı. (anlatılmaya gerek duyulmadı)

	ArrayBagAlani dizi;

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);
	for (int i = 0; true; i++) {

		fileRead.seekg((i*temp.getSize()), ios::beg);  
		fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
		fileRead.read(temp.model, 50);
		fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
		fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
		

		if (fileRead.eof())
		{
			break;
		}
		if (temp.model[0] != '*')
		{
			dizi.set(temp.bagAlani, i);
		}
		
	}
	fileRead.close();

	int tempBagAlani;
	int tempRRN;
	for (int i = 0; i < dizi.i; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (double(dizi.bagAlani[j + 1]) < double(dizi.bagAlani[j])) {
				tempBagAlani = dizi.bagAlani[j];
				dizi.bagAlani[j] = dizi.bagAlani[j + 1];
				dizi.bagAlani[j + 1] = tempBagAlani;

				tempRRN = dizi.RRN[j];
				dizi.RRN[j] = dizi.RRN[j + 1];
				dizi.RRN[j + 1] = tempRRN;

			}
			else {
				break;
			}
		}
	}


	return dizi;

}
void urunFiyatinaGoreSirala() { // Urun fiyatina göre siralayip ekrana yazdirir

	ArrayUrunFiyat dizi = urunFiyatDizisiOkuSirala();  // dosyadan ürün fiyatları ve ve rrn leri okunur sıralanır dizi değişkenine aktarılır

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // okunan bilgileri alabilmek için temp oluşturuldu

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in); // dosya açılır
	
	for (int i = 0; i < dizi.i; i++) {  // döngü dizideki eleman sayısı kadar döner

		fileRead.seekg((dizi.RRN[i]*temp.getSize()), ios::beg);   // dizideki sralanmış elemanın rrn siyle dosyadaki kayıta gidilir
		fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
		fileRead.read(temp.model, 50);
		fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
		fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));// veriler tek tek okunur ve temp e aktarılır
		printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price); 
		// son olarak bililer yazdırılır

	}
	fileRead.close(); 
}
void urunAdinaGoreSirala() { // Urun adina göre siralayip ekrana yazdirir

	//urunFiyatinaGoreSirala fonksiyonuna benzer işlemler yapıldı (anlatılmaya gerek duyulmadı)
	
	ArrayUrunAd dizi = urunAdDizisiOkuSirala();

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);

	for (int i = 0; i < dizi.i; i++) {

		fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);  
		fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
		fileRead.read(temp.model, 50);
		fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
		fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
		printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);

	}
	fileRead.close();
}
void bagAlaninaGoreSirala() { // bag alanina göre siralayip ekrana yazdirir

	//urunFiyatinaGoreSirala fonksiyonuna benzer işlemler yapıldı

	ArrayBagAlani dizi = bagAlaniDizisiOkuSirala();

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); 

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);

	for (int i = 0; i < dizi.i; i++) {

		fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   
		fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
		fileRead.read(temp.model, 50);
		fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
		fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
		fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
		printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);

	}
	fileRead.close();
}
int sonBagAlaniSiraliListe() { // sıralı listedeki yazılmış son kaydın bag alanını verir
	
	ArrayBagAlani dizi = bagAlaniDizisiOkuSirala(); // bağ alanları diziye aktarıldı

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // okunan bilgileri alabilmek için temp oluşturuldu

	int bagAlani;

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);

	for (int i = 0; i < dizi.i; i++) {  // dizi son elemana kadar ilerler ve bağ alanını alır
	
		if (i == dizi.i -1) // eğer sonuncu elemana gelindiyse bağ alanını alır
		{
			fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);
			fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
			fileRead.read(temp.model, 50);
			fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
			fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
			bagAlani = temp.bagAlani;
		}
	}
	fileRead.close();

	return bagAlani;  // sonuncu bağ alanını sonuc olarak döner. 
}


Kamera strToClass(string str) { // txt dosyasından alınan satırı Kamera class ına dönüştürür

	// str parametresi dosyadan alınmış herhangi bir satırdır

	Kamera kamera(0,"asd", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // alınan bu satır parçalara bölünüp kamera değişkenine yazılacak
	int dizi[7]; // alınan str deki '\t' lerin bulunduğu indexler bu diziye yazılacak
	int dizi_i = 0;

	for (int i = 0; i < str.length(); i++) { // '\t' nin bulunduğu indexleri yazdırmak için kullanılan döngü
		if (str[i] == '\t')
		{
			dizi[dizi_i++] = i; // '\t' gördüğü yerdeki indexi aktarıyor
		}
	}
	strcpy_s(kamera.model, &str.substr(0, dizi[0] - 0)[0]);
	kamera.date = stoi(str.substr(dizi[0], dizi[1] - dizi[0]));
	kamera.resolution = stod(str.substr(dizi[1], dizi[2] - dizi[1]));
	kamera.zoom = stod(str.substr(dizi[2], dizi[3] - dizi[2]));
	kamera.focus = stod(str.substr(dizi[3], dizi[4] - dizi[3]));
	kamera.storage = stod(str.substr(dizi[4], dizi[5] - dizi[4]));
	kamera.weight = stod(str.substr(dizi[5], dizi[6] - dizi[5]));
	kamera.price = stod(str.substr(dizi[6], str.length() - dizi[6]));
	// dizinin her indexi bir tane '\t' nin konumunu tuttuğu için her iki index arasında bir veri vardır. o verileri sırasıyla 
	// kamera değişkenine yazdırıyoruz

	return kamera; // kamera değişkeninde artık dosya satırlarındaki veriler bulunuyor. bu sayede verilere teker teker ulaşabileceğiz.
}
void siraliDosyaOlustur() { // Sırali binary dosyasını burada oluşturur

	// bu fonksiyonda camera.txt dosyasındaki veriler okunacak kameralarSıraliDosya.bin dosyasına yazılacak
	Kamera temp(0,"", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // kameralarSıraliDosya dosyasından çektiğimiz veriler geçici olarak burada tutulacak

	ofstream fileWrite("kameralarSiraliDosya.bin", ios::binary | ios::out | ios::trunc); // yazmak için açılan dosya
	ifstream dosyaOku("Camera.txt"); // okumak içinaçılan dosya
	string satir = ""; // camera dosyasıdan okuduğumuz satır bu değişkene aktarılacak
	if (dosyaOku.is_open()) {
		int sayac = 0;
		while (getline(dosyaOku, satir)) {  // Camera dosyasında satır olduğu sürece okuyup satır değişkenine yazacak 
			sayac++;
			if (sayac > 2) { // ilk iki satırda veri olmadığı için o kısımları atlıyoruz
				int bag = sayac - 3; // sayacımız atladığımız satırdan dolayı her zaman 3 fazla olacak. bunun için sayacdan 3 çıkarıp bağ alanını sıfırlıyoruz

				temp = strToClass(satir); // bu fonksiyon alınan satırı parçalara ayırıp Kamera veri tipindeki değişkene dönüştürüyor.
				fileWrite.write(reinterpret_cast<const char*>(&(bag)), sizeof(int));
				fileWrite.write(temp.model, 50);
				fileWrite.write(reinterpret_cast<const char*>(&(temp.date)), sizeof(int));
				fileWrite.write(reinterpret_cast<const char*>(&(temp.resolution)), sizeof(double));
				fileWrite.write(reinterpret_cast<const char*>(&(temp.zoom)), sizeof(double));
				fileWrite.write(reinterpret_cast<const char*>(&(temp.focus)), sizeof(double));
				fileWrite.write(reinterpret_cast<const char*>(&(temp.storage)), sizeof(double));
				fileWrite.write(reinterpret_cast<const char*>(&(temp.weight)), sizeof(double));
				fileWrite.write(reinterpret_cast<const char*>(&(temp.price)), sizeof(double));
				// temp değişkenindeki veriler teker teker kameralarSiraliDosya dosyasına yazıldı
			}
		}
	}
	dosyaOku.close();
	fileWrite.close();
	//dosyalar kapatıldı. Camera dosyasındaki verileri kameralarSiraliDosya dosyasına aktarmış olduk.
}
void boslarListesiOlustur() { // Boslar listesi olusturur
	//boşlar listesinni oluşturmamızdaki amac program sildiği elemanların bağ elemanlarını aktarmak için boşlar listesinin varlığını kontrol edecek
	ofstream fileWrite("boslarListesi.bin", ios::binary | ios::out | ios::trunc);
	if (fileWrite.is_open()) {
		
	}
	fileWrite.close();

	// dosya oluşturuldu

}
void siraliDosyaOku() { // Sıralı dosyayı olduğu gibi okur

	//Bu fonksiyon sıralı dosyayı okuyup consola yazdırmak için kullanıldı

	Kamera temp(0 ,"", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // okunan bilgileri alabilmek için temp oluşturuldu

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in); // okumak için dosya açıldı
	for (int i = 0; true; i++) { // sonsuz döngüye başlatıldı.dosyanın sonunda çıkılacak
		
			fileRead.seekg((i*temp.getSize()), ios::beg);   // dosyanın başına gidildi. Döngü her döndüğünde bir kayıt uzunluğu kadar ileri gidilecek
			fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
			fileRead.read(temp.model, 50);
			fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
			fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
			fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
			// veriler sırasıyla temp değişkenine alındı
			if (fileRead.eof())
			{
				break; // dosyanın sonuna ulaşıldığında döngüden çıkılır
			}
			printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n",temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);
			// temp değişkenine alınan veriler sırasyla ekrana bastırıldı
	}
	fileRead.close();
}
void boslarListesiOku() { // Boslar listesini olduğu gibi okur
	// projeyi kodlarken log lama kontrolü için yazıldı(projede kullanlmıyor)
	int bagAlani;
	int isaret;

	ifstream fileRead;
	fileRead.open("boslarListesi.bin", ios::binary | ios::in);
	for (int i = 0; true; i++) {

		fileRead.seekg((i*8), ios::beg);   // dosyanın başından itibaren 0 byte ileri gidildi. çünkü bilgiler ilk 24 byte yazıldı
		fileRead.read(reinterpret_cast<char*>(&(bagAlani)), sizeof(int));
		fileRead.read(reinterpret_cast<char*>(&(isaret)), sizeof(int));

		if (fileRead.eof())
		{
			break;
		}
		printf("%-4d %-4d\n", bagAlani, isaret);

	}
	fileRead.close();
}
int boslarListesiSilinmisEleman() { // silinmiş eleman varsa bağ alanını döner yoksa -1 döner
	
	// boşlar listesindeki silinmiş  ilk elemanın bağ alanını verir. boşlar listesinde silinmiş eleman yoksa -1 döner
	
	int bagAlani = -1;
	int isaret;

	ifstream fileRead;
	fileRead.open("boslarListesi.bin", ios::binary | ios::in); // boşlar listesini okumak için açıldı
	for (int i = 0; true; i++) {

		fileRead.seekg((i * 8), ios::beg);   // dosyanın başına gidildi. sırasıyla kayıtlar dolaşılacak
		fileRead.read(reinterpret_cast<char*>(&(bagAlani)), sizeof(int));
		fileRead.read(reinterpret_cast<char*>(&(isaret)), sizeof(int));
		// bağ alanı ile işaret okundu. işaret okunan bağ alanının kullanılabilir olup olmadığını belirtir
		// eğer işaret 0 ise o bağ alanı kullanılabilir. işaret 1 ise bağ alanı kullanılamaz

		if (fileRead.eof())
		{
			return -1;  // dosyanın sonuna gelindiyse kullanılacak bağ alanı bulunamamıştır
		}
		if (isaret == 0)
		{
			return bagAlani;  // işaretin 0 olduğu kayıtdaki bağ alanını kullanabilmek için sonuc olarak dönüyoruz
		}

	}
	fileRead.close();
}


int binarySearch(double x, double dizi[], int lenght) { // urun fiyatına göre ikiliarama yapar RRN bilgisini döner

	// Burada standart binarySearch algoritması kullanıldı.
	// alınan 1. parametre aranan eleman, 2. parametre elemanın aranacağı sırali dizi, 3. parametre dizi uzunluğu
	// bulduğu elemanın bulunduğu RRN sini sonuc olarak döner, bulamassa -1 döner
	int bas = 0;
	int orta = lenght / 2;
	int son = lenght;

	while (bas + 1 != son)
	{
		if (dizi[orta] == x)
		{
			return orta;
		}
		else if (dizi[orta] < x) {
			bas = orta;
			orta = (bas + son) / 2;
		}
		else if (dizi[orta] > x) {
			son = orta;
			orta = (bas + son) / 2;
		}
	}
	if (dizi[bas] == x)
	{
		return bas;
	}
	else if (dizi[son] == x)
	{
		return son;
	}
	else {
		return -1;
	}
}
int binarySearch(char urun[50], char dizi[][50], int lenght) { // urun adına göre ikiliarama yapar RRN bilgisini döner

	// Burada standart binarySearch algoritması kullanıldı.
	// alınan 1. parametre aranan eleman, 2. parametre elemanın aranacağı sırali dizi, 3. parametre dizi uzunluğu
	// bulduğu elemanın bulunduğu RRN sini sonuc olarak döner, bulamassa -1 döner

	int bas = 0;
	int orta = lenght / 2;
	int son = lenght;

	while (bas + 1 != son)
	{
		if (strcmp(dizi[orta], urun) == 0)
		{
			return orta;
		}
		else if (strcmp(dizi[orta],urun) < 0) {
			bas = orta;
			orta = (bas + son) / 2;
		}
		else if (strcmp(dizi[orta], urun) > 0) {
			son = orta;
			orta = (bas + son) / 2;
		}
	}
	if (strcmp(dizi[bas], urun) == 0)
	{
		return bas;
	}
	else if (strcmp(dizi[son], urun) == 0)
	{
		return son;
	}
	else {
		return -1;
	}
}
int binarySearch(int x, int dizi[], int lenght) { // urun fiyatına göre ikiliarama yapar RRN bilgisini döner

	// Burada standart binarySearch algoritması kullanıldı.
	// alınan 1. parametre aranan eleman, 2. parametre elemanın aranacağı sırali dizi, 3. parametre dizi uzunluğu
	// bulduğu elemanın bulunduğu RRN sini sonuc olarak döner, bulamassa -1 döner

	int bas = 0;
	int orta = lenght / 2;
	int son = lenght;

	while (bas + 1 != son)
	{
		if (dizi[orta] == x)
		{
			return orta;
		}
		else if (dizi[orta] < x) {
			bas = orta;
			orta = (bas + son) / 2;
		}
		else if (dizi[orta] > x) {
			son = orta;
			orta = (bas + son) / 2;
		}
	}
	if (dizi[bas] == x)
	{
		return bas;
	}
	else if (dizi[son] == x)
	{
		return son;
	}
	else {
		return -1;
	}
}
void urunFiyatinaGoreAra(double fiyat) { // urun fiyatına göre arama yapıp ekrana yazdırır


	ArrayUrunFiyat dizi = urunFiyatDizisiOkuSirala();  // siralı dosyadan okunan veriler sıralanıp diziye aktarılır

	///////////////////////////////// dosya işlemi ilk kısım 

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); 

	ifstream fileRead;  //  Dosya okumak için açıldı
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);
	
	///////////////////////////////// dosya işlemi ilk kısım

	if (binarySearch(fiyat, dizi.urunFiyat, dizi.i)!=-1) // eğer aranan fiyat ürün fiyat dizisinde varsa for döngüleri hem alt kısmındki verileri hemde üst kısımdaki verileri okumak için başlar
	{
		for (int i = binarySearch(fiyat, dizi.urunFiyat, dizi.i); true; i--) {
			if (dizi.urunFiyat[i] == fiyat)
			{
				fileRead.seekg((dizi.RRN[i]*temp.getSize()), ios::beg);   // aradığımızfiyatın bulunduğurrn ye gider
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);

				// bulunan indexin alt kısmındaki verilerde aradağımız fiyattaki verilerde 
				//olabileceği içindöngü alt kısımdaki verilerde bakar eğer fiyat aradığımız
				// fiyata eşitse ekrana yazdırı değilse else bloğunda döngüyü snlandırı

			}
			else {
				break;
			}

		}
		for (int i = binarySearch(fiyat, dizi.urunFiyat, dizi.i)+1; true; i++) {
			if (dizi.urunFiyat[i] == fiyat)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   // aradığımızfiyatın bulunduğurrn ye gider
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);

				// bulunan indexin üst kısmındaki verilerde aradağımız fiyattaki verilerde 
				//olabileceği içindöngü üst kısımdaki verilerde bakar eğer fiyat aradığımız
				// fiyata eşitse ekrana yazdırı değilse else bloğunda döngüyü snlandırı

			}
			else {
				break;
			}

		}



	}
	else {
		cout << "Kayit bulunamadi"<<endl; // aranan eleman bulunamadıysa kayıt bulunamadı yazısını ekrana basar
	}


	///////////////////////////////// dosya işlemi son kısım

	fileRead.close();

	///////////////////////////////// dosya işlemi son kısım
}
void urunAdinaGoreAra(char urun[50]) { // urun adına göre arama yapıp ekrana yazdırır

	//urunFiyatinaGoreAra fonksiyondaki kodlarlar aynı işlemleri yapar (Anlatılmaya gerek duyulmadı)

	ArrayUrunAd dizi = urunAdDizisiOkuSirala();

	///////////////////////////////// dosya işlemi ilk kısım

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);

	///////////////////////////////// dosya işlemi ilk kısım

	if (binarySearch(urun, dizi.urunAd, dizi.i) != -1)
	{
		for (int i = binarySearch(urun, dizi.urunAd, dizi.i); true; i--) {
			if (strcmp(dizi.urunAd[i], urun) == 0)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				

			}
			else {
				break;
			}
			printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);
		}
		for (int i = binarySearch(urun, dizi.urunAd, dizi.i) + 1; true; i++) {
			if (strcmp(dizi.urunAd[i], urun) == 0)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   // dosyanın başından itibaren 0 byte ileri gidildi. çünkü bilgiler ilk 24 byte yazıldı
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));

			}
			else {
				break;
			}				
			printf("%-4d %-30s %-5d %-6.0f %-6.0f %-4.0f %-4.0f %-4.0f %-6.0f\n", temp.bagAlani, temp.model, temp.date, temp.resolution, temp.zoom, temp.focus, temp.storage, temp.weight, temp.price);

		}



	}
	else {
		cout << "Kayit bulunamadi" << endl;
	}


	///////////////////////////////// dosya işlemi son kısım

	fileRead.close();

	///////////////////////////////// dosya işlemi son kısım
}
int bagAlaninaGoreAra(int bag) { // bag alanına göre arama yapip indexini döner

	//urunFiyatinaGoreAra fonksiyondaki kodlarlar aynı işlemleri yapar tek fark bulduğu kaydın indexini döner (anlatılmaya gerek duyulmadı)

	ArrayBagAlani dizi = bagAlaniDizisiOkuSirala();

	///////////////////////////////// dosya işlemi ilk kısım

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);

	///////////////////////////////// dosya işlemi ilk kısım

	if (binarySearch(bag, dizi.bagAlani, dizi.i) != -1)
	{
		for (int i = binarySearch(bag, dizi.bagAlani, dizi.i); true; i--) {
			if (dizi.bagAlani[i] == bag)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg); 
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				return i;
			}
			else {
				break;
			}

		}
		for (int i = binarySearch(bag, dizi.bagAlani, dizi.i) + 1; true; i++) {
			if (dizi.bagAlani[i] == bag)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				return i;
			}
			else {
				break;
			}

		}



	}
	else {
		return -1;
	}


	///////////////////////////////// dosya işlemi son kısım

	fileRead.close();

	///////////////////////////////// dosya işlemi son kısım
}
Kamera bagAlaninaGöreKayitAra(int bag) { // bag alanına göre arama yapıp kayıt döner

	//urunFiyatinaGoreAra fonksiyondaki kodlarlar aynı işlemleri yapar tek fark bulduğu kayıtı sonuc olarak döner (anlatılmaa gerek duyulmadı)

	ArrayBagAlani dizi = bagAlaniDizisiOkuSirala();

	///////////////////////////////// dosya işlemi ilk kısım

	Kamera temp(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	ifstream fileRead;
	fileRead.open("kameralarSiraliDosya.bin", ios::binary | ios::in);

	///////////////////////////////// dosya işlemi ilk kısım

	if (binarySearch(bag, dizi.bagAlani, dizi.i) != -1)
	{
		for (int i = binarySearch(bag, dizi.bagAlani, dizi.i); true; i--) {
			if (dizi.bagAlani[i] == bag)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				return temp;
			}
			else {
				break;
			}

		}
		for (int i = binarySearch(bag, dizi.bagAlani, dizi.i) + 1; true; i++) {
			if (dizi.bagAlani[i] == bag)
			{
				fileRead.seekg((dizi.RRN[i] * temp.getSize()), ios::beg);   
				fileRead.read(reinterpret_cast<char*>(&(temp.bagAlani)), sizeof(int));
				fileRead.read(temp.model, 50);
				fileRead.read(reinterpret_cast<char*>(&(temp.date)), sizeof(int));
				fileRead.read(reinterpret_cast<char*>(&(temp.resolution)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.zoom)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.focus)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.storage)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.weight)), sizeof(double));
				fileRead.read(reinterpret_cast<char*>(&(temp.price)), sizeof(double));
				return temp;
			}
			else {
				break;
			}

		}



	}
	else {
		return temp;
	}


	///////////////////////////////// dosya işlemi son kısım

	fileRead.close();

	///////////////////////////////// dosya işlemi son kısım
}


void kayitGuncelle() { // kayıt güncellemek için yazıldı

	int bagAlani;
	cout << "Guncellenecek Kayitin Bag Alani: ";
	cin >> bagAlani;
	int index = bagAlaninaGoreAra(bagAlani); // bu fonksyongirilen bağ alanının kaçıncı indexte tutulduğunu bulur
	// bulunan indexdegi rrn bilgisi güncellenecek olan kayıtın rrn sinidir
	if (index != -1) // index -1 e eşit değilse kayıt var demektir güncellenebilir
	{
		
		Kamera kamera(0, "Nikon", 1999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // güncellenecek bilgiler tutualcak

		
		char model[50];
		int date;
		double resolution;
		double zoom;
		double focus;
		double storage;
		double weight;
		double price;
		// kayıtları alabilmek için değişkenler tanımlandı
		cout << "Model: ";
		cin >> model;
		cout << "Date: ";
		cin >> date;
		cout << "Resolution: ";
		cin >> resolution;
		cout << "Zoom: ";
		cin >> zoom;
		cout << "Focus: ";
		cin >> focus;
		cout << "Storage: ";
		cin >> storage;
		cout << "Weight: ";
		cin >> weight;
		cout << "Price: ";
		cin >> price;
		// kayıtlar alındı
		strcpy_s(kamera.model, model);
		kamera.date = date;
		kamera.resolution = resolution;
		kamera.zoom = zoom;
		kamera.focus = focus;
		kamera.storage = storage;
		kamera.weight = weight;
		kamera.price = price;
		// bilgiler console ekranından alındı kamera sınıfına aktarıldı

		ArrayBagAlani dizi = bagAlaniDizisiOkuSirala(); // bilgilerin bağ alanları ve rrn leri sıralı bir şekilde okundu
		ofstream fileWrite;
		fileWrite.open("kameralarSiraliDosya.bin", ios::binary | ios::in | ios::out | ios::ate );
		fileWrite.seekp(kamera.getSize() * dizi.RRN[index], ios::beg); // bulunan indexdeki kayıtın rrn sine gidildi, kayıtlar üzerine yazılacak
		fileWrite.write(reinterpret_cast<const char*>(&(bagAlani)), sizeof(int));
		fileWrite.write(kamera.model, 50);
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.date)), sizeof(int));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.resolution)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.zoom)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.focus)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.storage)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.weight)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.price)), sizeof(double));
		fileWrite.close();
		// yazma işlemi bitti. Kayıt güncellendi.
		cout << "Kayit Basariyla Guncellendi" << endl;
	}
	else {
		cout << "Kayit Bulunamadi" << endl;
	}
}
void kayitSil() {// kayıt silmek için yazıldı

	int bagAlani;
	cout << "Silinecek Kayitin Bag Alani: ";
	cin >> bagAlani;
	int index = bagAlaninaGoreAra(bagAlani);  // silinecek kaydın bağ alanın bulunduğu indexi bulur
	if (index != -1) // index -1 den farklıysa böyle bir kayıt var demektir
	{

		Kamera kamera = bagAlaninaGöreKayitAra(bagAlani);  // kayıtları silindi olarak işaretlemek için bağ alanına göre bulunan kayıtın
		//  isim kısmına '*' işareti koymak gereklidir. bunun için kayıtı okuyup model kısımın başına '*' ekleyip güncellemek gerekecek
		char model[50] = "*";
		strcat_s(model, kamera.model); // model kısmı '*kameraismi' olarak güncellendi

		ArrayBagAlani dizi = bagAlaniDizisiOkuSirala(); // bag alanları ve rrnler sıralı bir şekilde okundu
		ofstream fileWrite;
		fileWrite.open("kameralarSiraliDosya.bin", ios::binary | ios::in | ios::out | ios::ate); // güncellemek için dosya açıldı
		fileWrite.seekp(kamera.getSize() * dizi.RRN[index], ios::beg); // belirlenen indexdeki rrn ye gidildi
		fileWrite.write(reinterpret_cast<const char*>(&(bagAlani)), sizeof(int));
		fileWrite.write(model, 50);
		// model güncellenmiş bir şekilde tekrar yazıldı
		fileWrite.close();
		cout << "Kayit Basariyla Silindi" << endl;

		// silinen kayıtın bağ alanını tekrar kullanabilmek için boşlar listesine eklendi ve 0 olarak işaretlendi.
		// 0 demek bu bağ alanına kayıt yazabilirsin demektir. bu işlemi yaparak hafızayı gereksiz yere doldurmamış olacağız
		int isaret = 0;
		ofstream fileWriter("boslarListesi.bin", ios::binary | ios::out | ios::in | ios::ate);
		if (fileWriter.is_open()) {
			fileWriter.seekp(0, ios::end);
			fileWriter.write(reinterpret_cast<const char*>(&(bagAlani)), sizeof(int));
			fileWriter.write(reinterpret_cast<const char*>(&(isaret)), sizeof(int));
			//boşlar listesine silinmiş kayıtın bağ alanı eklendi
		}
		fileWrite.close();
	}
	else {
		cout << "Kayit Bulunamadi" << endl;
	}
}
void kayitEkle() {// kayit eklemek için yazıldı
	//Kayıt ekleme bölümünde önce boşlar listesi kontrol edilir eğer kullanlabilir bağ alanı varsa o bağ alanına kayıt eklenir.
	// kullanılabilir bir bağ alanı yoksa kayıt dosyanın sonuna eklenir.
	int bagAlani = boslarListesiSilinmisEleman();  // eğer boşlar listesinde kullanılabilecek bir bağ alanı varsa döner, yoksa -1 döner.

	Kamera kamera(0, "Nikon", 1999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // dosyaya eklenecek bilgiler

	char model[50];
	int date;
	double resolution;
	double zoom;
	double focus;
	double storage;
	double weight;
	double price;
	cout << "Model: ";
	cin >> model;
	cout << "Date: ";
	cin >> date;
	cout << "Resolution: ";
	cin >> resolution;
	cout << "Zoom: ";
	cin >> zoom;
	cout << "Focus: ";
	cin >> focus;
	cout << "Storage: ";
	cin >> storage;
	cout << "Weight: ";
	cin >> weight;
	cout << "Price: ";
	cin >> price;

	strcpy_s(kamera.model, model);
	kamera.date = date;
	kamera.resolution = resolution;
	kamera.zoom = zoom;
	kamera.focus = focus;
	kamera.storage = storage;
	kamera.weight = weight;
	kamera.price = price;
	// buraya kadar eklenecek kayıt kullanıcıdan alındı ye kamera sınıfına kaydedildi
	if (bagAlani == -1) // bağ alanı -1 e eşitse dosyanın sonuna kayıt eklenecek
	{
		bagAlani = sonBagAlaniSiraliListe() +1; // yeni kaydın bağ alanı son kayyıttan 1 fazla olur
		
		
		

		ArrayBagAlani dizi = bagAlaniDizisiOkuSirala();
		ofstream fileWrite;
		fileWrite.open("kameralarSiraliDosya.bin", ios::binary | ios::in | ios::out | ios::ate);
		fileWrite.seekp(kamera.getSize() * bagAlani, ios::beg); // dosyanın sonuna gidildi kayıtlar buraya eklenecek
		fileWrite.write(reinterpret_cast<const char*>(&(bagAlani)), sizeof(int));
		fileWrite.write(kamera.model, 50);
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.date)), sizeof(int));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.resolution)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.zoom)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.focus)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.storage)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.weight)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.price)), sizeof(double));
		fileWrite.close();
		// kayıt ekleme işlemleri yapıldı

	}
	else // eğer boşlar listesinde yer varsa burası çalışacak
	{
		//  sirali listedeki silinmiş olan ilk elemanın bağ alanına kaydı ekler
		ArrayBagAlani dizi = bagAlaniDizisiOkuSirala();
		ofstream fileWrite;
		fileWrite.open("kameralarSiraliDosya.bin", ios::binary | ios::in | ios::out | ios::ate);
		fileWrite.seekp(kamera.getSize() * bagAlani, ios::beg); // boşlar listesinden alınan bağ alanına gidildi 
		fileWrite.write(reinterpret_cast<const char*>(&(bagAlani)), sizeof(int));
		fileWrite.write(kamera.model, 50);
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.date)), sizeof(int));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.resolution)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.zoom)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.focus)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.storage)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.weight)), sizeof(double));
		fileWrite.write(reinterpret_cast<const char*>(&(kamera.price)), sizeof(double));
		fileWrite.close();
		// kayıt ekleme işi yapıldı


		//// Boşlar listesindeki kullanılmış kaydın işaretini değiştirir
		// boşlar listesindeki bağ alanı kullanıldığı için işareti 1 yapılacak
		int tempBagAlani = -1;
		int tempIsaret;

		ifstream fileRead;
		fileRead.open("boslarListesi.bin", ios::binary | ios::in);
		for (int i = 0; true; i++) {

			fileRead.seekg((i * 8), ios::beg);   // dosyanın başından başlayarak kayıtlara bakılacak
			fileRead.read(reinterpret_cast<char*>(&(tempBagAlani)), sizeof(int));
			fileRead.read(reinterpret_cast<char*>(&(tempIsaret)), sizeof(int));
			// satırdaki kayıtlar hafızaya alındı
			if (fileRead.eof())
			{
				break; // dosyanın sonuna gelindiyse döngüden çıkacak
			}
			if (tempIsaret == 0) // gidilen kayıttaki işaret 0 ise 1 yapılacak bir dağa bu bağ alanı kullanılmasın
			{
				int isaretTrue = 1;
				ofstream fileWriter;
				fileWriter.open("boslarListesi.bin", ios::binary | ios::in | ios::out | ios::ate);
				fileWriter.seekp((i * 8), ios::beg);
				fileWriter.write(reinterpret_cast<const char*>(&(tempBagAlani)), sizeof(int));
				fileWriter.write(reinterpret_cast<const char*>(&(isaretTrue)), sizeof(int));
				fileWriter.close();
				break;
				// boşlar listesindeki kullanılan bağ alanını işareti 1 yapıldı artık burası kullanılmayacak
				// silme işlemi tekrar yapıldığında bir sonraki bağ alanına gidilecek
			}

		}
		cout << "Kayit Basariyla Eklendi" << endl;
		fileRead.close();
	}
}
void arayüz() { // Arayüzü göstermek için yazıldı


	int secimRoot;
	int secimKullanici;
	int secimYonetici;
	// secim değişkenleri kullanıcıya seçim yaptırmak için tanımlandı

	bool kullanici = false; // kullanici true olursa tekrar seçim yaptırmak ister kontrol döngler içinde sağlanır
	bool yonetici = false;  // yonetici true olursa tekrar seçim yaptırmak ister kontrol döngler içinde sağlanır
	do
	{
		kullanici = false;
		yonetici = false;

		cout << "URUN KATALOG SISTEMI" << endl;
		cout << "1. Kullanici" << endl;
		cout << "2. Yonetici" << endl;
		cout << "Secim: ";
		cin >> secimRoot;

		if (secimRoot == 1) // eğer seçim 1 se kullanici işlemleri gözükür
		{
			do
			{
				cout << endl;
				cout << "1. Urun Adina Gore Ara" << endl;
				cout << "2. Urun Fiyatina Gore Ara" << endl;
				cout << "3. Geri" << endl;
				cout << "Secim: ";
				cin >> secimKullanici;

				if (secimKullanici == 1)
				{
					char chr[50];
					cout << endl;
					cout << "Urun Adini Giriniz: " ;
					cin >> chr;
					cout << endl;
					urunAdinaGoreAra(chr);
					yonetici = true;
					break;
				}
				if (secimKullanici == 2)
				{
					double dbl;

					cout << endl;
					cout << "Urun Fiyatini Giriniz: " ;
					cin >> dbl;
					cout << endl;
					urunFiyatinaGoreAra(dbl);
					yonetici = true;
					break;
				}
				if (secimKullanici == 3)
				{
					kullanici = true;
					break;
				}
			} while (!(secimKullanici == 1 || secimKullanici == 2 || secimKullanici == 2)); // hatalı seçim yapılırsa tekrar seçim yaptırır
		}
		if (secimRoot == 2) // seçim 2 ise yönetici işlemleri gözükür
		{
			do
			{
				cout << endl;
				cout << "1. Urun Adina Gore Ara" << endl;
				cout << "2. Urun Fiyatina Gore Ara" << endl;
				cout << "3. Kayit Ekle" << endl;
				cout << "4. Kayit Sil" << endl;
				cout << "5. Kayit Guncelle" << endl;
				cout << "6. Kayitlari Urun Adina Gore Sirala" << endl;
				cout << "7. Kayitlari Urun Fiyatina Gore Sirala" << endl;
				cout << "8. Geri" << endl;
				cout << "Secim: ";
				cin >> secimYonetici;

				if (secimYonetici == 1)
				{

					char chr[50];
					cout << endl;
					cout << "Urun Adini Giriniz: " ;
					cin >> chr;
					cout << endl;
					urunAdinaGoreAra(chr);
					yonetici = true;
					break;
				}
				if (secimYonetici == 2)
				{
					double dbl;

					cout << endl;
					cout << "Urun Fiyatini Giriniz: ";
					cin >> dbl;
					cout << endl;
					urunFiyatinaGoreAra(dbl);
					yonetici = true;
					break;
				}
				if (secimYonetici == 3)
				{
					cout << endl;
					kayitEkle();
					yonetici = true;
					break;
				}
				if (secimYonetici == 4)
				{
					cout << endl;
					kayitSil();
					yonetici = true;
					break;
				}
				if (secimYonetici == 5)
				{
					cout << endl;
					kayitGuncelle();
					yonetici = true;
					break;
				}
				if (secimYonetici == 6)
				{
					cout << endl;
					urunAdinaGoreSirala();
					yonetici = true;
					break;
				}
				if (secimYonetici == 7)
				{
					cout << endl;
					urunFiyatinaGoreSirala();
					yonetici = true;
					break;
				}
				if (secimYonetici == 8)
				{
					yonetici = true;
					break;
				}
				if (secimYonetici == 10)
				{
					siraliDosyaOku();
					yonetici = true;
					break;
				}
				
			} while (!(secimYonetici == 1 || secimYonetici == 2 || secimYonetici == 3 || secimYonetici == 4 || secimYonetici == 5 || secimYonetici == 6 || secimYonetici == 7 || secimYonetici == 8)); // hatalı seçim yapılırsa tekrar seçim yaptırır
		}

		cout << endl;

	} while (!(secimRoot == 1 || secimRoot == 2) || kullanici || yonetici); // hatalı seçim yapılırsa tekrar seçim yaptırır ve kullanıcı ve yonetici true ise başa döner tekrar seçim yaptırır

}



int main()
{

	siraliDosyaOlustur();  // program calistirildiginda sirali liste olusturulmasi gerekir
	boslarListesiOlustur(); // program calistirildiginda boslar listesi olusturulmalı
	arayüz(); // kullaniciyi yonlendirecek arayuz
	
	system("PAUSE");

}

