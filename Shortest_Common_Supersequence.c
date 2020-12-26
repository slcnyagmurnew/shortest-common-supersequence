#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

// elde edilen yeni string in uzunlu�u
int lenght; 
// ba�lang�� ve biti� zamanlar�n� tutacak olan struct yap�lar�
struct timeval  tv1, tv2; 
/* kullan�c�n�n girdi�i her string ikilisinin
toplam say�s�n�n bulundu�u dizi */
int len_inputs[20];
/* kullan�c�n�n girdileriyle elde edilen her bir yeni
string in uzunlu�unun bulundu�u dizi*/
int len_outputs[20];
/* her bir string olu�turma i�lemi i�in ge�en s�relerin
tutuldu�u dizi */
double time_values[20];

/* iki string birle�imi i�in bir �nceki s�tun veya
bir �nceki sat�r�n de�erlerini kar��la�t�ran
ve k���k olan� d�nd�ren fonksiyon */
int min(int a, int b){ 
	if(a < b) return a;
    return b;
} 
/* yeni string in olu�turuldu�u fonksiyon.
yukar�da tan�mlanan "lenght" de�i�kenine 
de�er atamas� burada yap�l�r. ayr�ca
bulunan string in ekrana yazd�r�ld��� fonksiyon*/
void makeString(char X[], char Y[]) { 
    int m = strlen(X); // X kelimesinin uzunlu�u
    int n = strlen(Y); // Y kelimesinin uzunlu�u
    
    /* iki kelime i�in de ba�lang��ta denk gelen 
	matris h�cresine 0 dan kelime uzunlu�una kadar
	atama yap�l�r.
	bu i�lem i�in kullan�lacak matrisin tan�m�*/
    int Matrix[m + 1][n + 1]; 
  	int i, j;

    for (i = 0; i <= m; i++){ 
        for (j = 0; j <= n; j++){ 
            if(i == 0) 
            /* ilk string i�in her bir harfin bulundu�u
			matris h�cresine ilgili indis atamas� 
			0 dan uzunlu�un 1 eksi�ine kadar yap�l�r*/ 
                Matrix[i][j] = j; 
            else if(j == 0) 
            /* ikinci string i�in her bir harfin bulundu�u 
			matris h�cresine s�tun do�rultusunda ilgili indis
			atamas� 0 dan uzunlu�un 1 eksi�ine kadar yap�l�r*/
                Matrix[i][j] = i; 
            else if(X[i - 1] == Y[j - 1]) 
            /* iki string i�indeki harflerin ayn� olmas� durumunda
			o harfin yeni stringte daha �nce gelmesini sa�lamak i�in
			bulunulan matris h�cresine, sol �apraz h�cresindeki
			say�sal de�erin bir fazlas� yerle�tirilir*/
                Matrix[i][j] = 1 + Matrix[i - 1][j - 1]; 
            else
            /* iki string i�indeki harflerin ayn� olmamas� durumunda
			harfin yerle�tirilece�i indisin atamas�, i�inde bulunulan
			matris h�cresinin bir sol ve bir �st de�erlerinin 
			minimumunun bir fazlas�n�n al�nmas�yla yap�l�r.*/
                Matrix[i][j] = 1 + min(Matrix[i - 1][j], Matrix[i][j - 1]); 
        } 
    } 
    
    int index = Matrix[m][n]; // string uzunlu�unu i�erir
    char newString[20]; // yeni olu�turulacak string
  
    /* bundan sonraki k�s�mda stringlerde sondan ba�a do�ru gidilir
	her i�lemde indisler birer azalt�l�r
	iki stringten herhangi birinin uzunlu�unun 0 lanmas� durumunda
	d�ng�den ��k�l�r
	yeni string in olu�turulmas� i�in "string concatenation"
	i�lemi (strncat g�m�l� fonksiyonu) kullan�l�r.*/
    i = m; j = n; 
    while (i > 0 && j > 0){ 
        if (X[i - 1] == Y[j - 1]){ 
        	/* string i�eriklerinin ayn� olmas� durumunda
        	(herhangi birinin) son harf yaz�lmaya ba�lan�r
			iki string i�in de ayn� oldu�undan
			iki indis de azalt�l�r */
            strncat(newString, &X[i - 1], 1); 
            i--, j--, index--; 
        } 
        else if (Matrix[i - 1][j] > Matrix[i][j - 1]){ 
    		/* sol h�crenin bir �st h�creden b�y�k olmas�
			durumunda ikinci string in harfi yaz�l�r ��nk�
			s�tun s�ralamas� Y dedir ve k���k olan �nceliklidir*/
            strncat(newString, &Y[j - 1], 1); 
            j--, index--; 
        } 
        else{ 
        	/* bir �nceki durumun tam tersidir
			sol h�cre bir �st h�creden k���kt�r
			sat�r s�ralamas� X tedir ve k���k olan �nceliklidir*/
            strncat(newString, &X[i - 1], 1); 
            i--, index--; 
        } 
    } 
    
  	/* yukar�daki "while" d�ng�s�nden ��k��. 
	iki string ten birinin art�k bak�lacak bir indisinin
	kalmamas� yani m ya da n in 0 lanmas� */
    while (i > 0){
		/* ilk olarak verilen string (X)
		yeni string olu�umunda ortak harfler de
		bittikten sonra �nceliklidir*/ 
        strncat(newString, &X[i - 1], 1); 
        i--, index--; 
    } 
    while (j > 0){ 
    	/* ilk verilen stringte harf kalmamas� durumunda
		ikinci string in harflerine ge�ilir
		bitene kadar, yeni string e harf ekleme i�lemi devam eder*/
        strncat(newString, &Y[j - 1], 1); 
        j--, index--; 
    } 
    
    /* ba�lang��ta belirtildi�i gibi string e harf 
	ekleme i�lemi sondan ba�a do�rudur, elde edilen 
	string, as�l olmas� gereken string in ters halidir
	bunun i�in string in tersini (reverse) alan
	g�m�l� "strrev" fonksiyonu kullan�l�r*/
    strrev(newString); 
    /* string sonunda fazladan harf, rakam vb olmamas� i�in
	uzunlu�un 1 eksi�ine (son indise)
	biti� g�stergesi konur*/
    newString[strlen(newString) - 1] = '\0';
    // lenght de�i�kenine atama
    lenght = strlen(newString);
    printf("Result of string: %s\n", newString);
}
/* �al��mada istenen g�rsellik 
her bir �al��ma zaman� i�in "*" i�areti ile
yap�ld�.parametre olarak kodun o anki �al��ma
s�resini al�r*/
void print_star(double value){
	/* yazd�r�labilir bir de�er elde etmek i�in
	her bir say� 10 ile �arp�l�p integer bir 
	de�ere d�n��t�r�l�r*/
	int new_value = value * 10;
	int i;
	for(i = 0; i<new_value; i++){ 
		// asterisk i�areti ekrana bast�r�l�yor
		printf("*");
	}
	/* histogram�n d�zg�n g�r�nmesi i�in
	geri kalan k�sma bo�luk bast�r�ld�*/
	for(i = 0; i<50 - new_value; i++){
		printf(" ");
	}
}
int main(){ 
	// kullan�c�n�n girece�i stringler
    char X[15], Y[15]; 
    /* kullan�c�n�n programdan ��k�� yap�p yapmad���n�
	kontrol etmek i�in kullan�lacak de�i�ken
	0 ise devam 1 ise ��k�� */
    int flag = 0;
    /* ba�lang��ta tan�mlanan input-output-time
	dizilerinin her bir girdi i�in atamas�nda 
	kullan�lacak olan indis*/
    int in_out_index = 0;
    do{
    	/* i�lem s�resinin tutuldu�u de�i�ken*/
    	double time_result;
    	printf("Enter the first string:");
    	scanf("%s",&X);
    	printf("Enter the second string:");
    	scanf("%s",&Y);
    	/* i�lem ba�lamadan �nce zaman al�n�yor*/
        gettimeofday(&tv1, NULL);
        /* al�nan stringlerin uzunluklar� toplam�
		ilgili diziye yerle�tirilir*/
    	len_inputs[in_out_index] = (strlen(X) + strlen(Y));
    	// as�l i�lemin yap�ld��� fonksiyon �a�r�l�yor
    	makeString(X, Y);
    	//fonksiyon i�inde bulunan lenght ekrana yazd�r�l�yor
    	printf("Length of the shortest supersequence is %d\n", lenght);
    	/* bulunan yeni string uzunlu�u
		ilgili diziye yerle�tiriliyor*/
		len_outputs[in_out_index] = lenght;	
		// i�lem bittikten sonra yeniden zaman al�n�yor
    	gettimeofday(&tv2, NULL);
    	// al�nan iki zaman de�erinin fark� bulunuyor
    	time_result = (double) (tv2.tv_sec + tv2.tv_usec) / 1e6 - (double) (tv1.tv_sec - tv1.tv_usec) / 1e6;
    	// bulunan fark ilgili diziye yerle�tiriliyor
    	time_values[in_out_index] = time_result;
    	//yeni i�lem i�in indis de�eri 1 artt�r�l�yor
    	in_out_index++;
		printf ("Total time = %f seconds\n", time_result);
    	printf("---------------------------------------------\n");
    	printf("Do you want to continue?\nEnter 0 to continue or 1 to exit:");
    	scanf("%d",&flag);
	}while(flag == 0);
    
    /* kullan�c� programdan ��kt�ktan sonra
	bir histogram g�r�nt�s� ekrana verilir
	her bir string girdilerinin ve yeni string in
	toplam� i�in, ba�lang��ta olu�turulan dizilerden
	s�ras� ile veriler al�n�r.*/
    printf("\n\n\t\t\t--------------HISTOGRAM--------------\n\n\n");
    int m;
    for(m = 0; m<in_out_index; m++){
    	print_star(time_values[m]);
    	printf("\t");
    	printf("For input lenght %d - output lenght %d ",len_inputs[m], len_outputs[m]);
    	printf("\n");
	}
    return 0; 
} 
