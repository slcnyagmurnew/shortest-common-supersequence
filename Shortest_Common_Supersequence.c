#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

// elde edilen yeni string in uzunluðu
int lenght; 
// baþlangýç ve bitiþ zamanlarýný tutacak olan struct yapýlarý
struct timeval  tv1, tv2; 
/* kullanýcýnýn girdiði her string ikilisinin
toplam sayýsýnýn bulunduðu dizi */
int len_inputs[20];
/* kullanýcýnýn girdileriyle elde edilen her bir yeni
string in uzunluðunun bulunduðu dizi*/
int len_outputs[20];
/* her bir string oluþturma iþlemi için geçen sürelerin
tutulduðu dizi */
double time_values[20];

/* iki string birleþimi için bir önceki sütun veya
bir önceki satýrýn deðerlerini karþýlaþtýran
ve küçük olaný döndüren fonksiyon */
int min(int a, int b){ 
	if(a < b) return a;
    return b;
} 
/* yeni string in oluþturulduðu fonksiyon.
yukarýda tanýmlanan "lenght" deðiþkenine 
deðer atamasý burada yapýlýr. ayrýca
bulunan string in ekrana yazdýrýldýðý fonksiyon*/
void makeString(char X[], char Y[]) { 
    int m = strlen(X); // X kelimesinin uzunluðu
    int n = strlen(Y); // Y kelimesinin uzunluðu
    
    /* iki kelime için de baþlangýçta denk gelen 
	matris hücresine 0 dan kelime uzunluðuna kadar
	atama yapýlýr.
	bu iþlem için kullanýlacak matrisin tanýmý*/
    int Matrix[m + 1][n + 1]; 
  	int i, j;

    for (i = 0; i <= m; i++){ 
        for (j = 0; j <= n; j++){ 
            if(i == 0) 
            /* ilk string için her bir harfin bulunduðu
			matris hücresine ilgili indis atamasý 
			0 dan uzunluðun 1 eksiðine kadar yapýlýr*/ 
                Matrix[i][j] = j; 
            else if(j == 0) 
            /* ikinci string için her bir harfin bulunduðu 
			matris hücresine sütun doðrultusunda ilgili indis
			atamasý 0 dan uzunluðun 1 eksiðine kadar yapýlýr*/
                Matrix[i][j] = i; 
            else if(X[i - 1] == Y[j - 1]) 
            /* iki string içindeki harflerin ayný olmasý durumunda
			o harfin yeni stringte daha önce gelmesini saðlamak için
			bulunulan matris hücresine, sol çapraz hücresindeki
			sayýsal deðerin bir fazlasý yerleþtirilir*/
                Matrix[i][j] = 1 + Matrix[i - 1][j - 1]; 
            else
            /* iki string içindeki harflerin ayný olmamasý durumunda
			harfin yerleþtirileceði indisin atamasý, içinde bulunulan
			matris hücresinin bir sol ve bir üst deðerlerinin 
			minimumunun bir fazlasýnýn alýnmasýyla yapýlýr.*/
                Matrix[i][j] = 1 + min(Matrix[i - 1][j], Matrix[i][j - 1]); 
        } 
    } 
    
    int index = Matrix[m][n]; // string uzunluðunu içerir
    char newString[20]; // yeni oluþturulacak string
  
    /* bundan sonraki kýsýmda stringlerde sondan baþa doðru gidilir
	her iþlemde indisler birer azaltýlýr
	iki stringten herhangi birinin uzunluðunun 0 lanmasý durumunda
	döngüden çýkýlýr
	yeni string in oluþturulmasý için "string concatenation"
	iþlemi (strncat gömülü fonksiyonu) kullanýlýr.*/
    i = m; j = n; 
    while (i > 0 && j > 0){ 
        if (X[i - 1] == Y[j - 1]){ 
        	/* string içeriklerinin ayný olmasý durumunda
        	(herhangi birinin) son harf yazýlmaya baþlanýr
			iki string için de ayný olduðundan
			iki indis de azaltýlýr */
            strncat(newString, &X[i - 1], 1); 
            i--, j--, index--; 
        } 
        else if (Matrix[i - 1][j] > Matrix[i][j - 1]){ 
    		/* sol hücrenin bir üst hücreden büyük olmasý
			durumunda ikinci string in harfi yazýlýr çünkü
			sütun sýralamasý Y dedir ve küçük olan önceliklidir*/
            strncat(newString, &Y[j - 1], 1); 
            j--, index--; 
        } 
        else{ 
        	/* bir önceki durumun tam tersidir
			sol hücre bir üst hücreden küçüktür
			satýr sýralamasý X tedir ve küçük olan önceliklidir*/
            strncat(newString, &X[i - 1], 1); 
            i--, index--; 
        } 
    } 
    
  	/* yukarýdaki "while" döngüsünden çýkýþ. 
	iki string ten birinin artýk bakýlacak bir indisinin
	kalmamasý yani m ya da n in 0 lanmasý */
    while (i > 0){
		/* ilk olarak verilen string (X)
		yeni string oluþumunda ortak harfler de
		bittikten sonra önceliklidir*/ 
        strncat(newString, &X[i - 1], 1); 
        i--, index--; 
    } 
    while (j > 0){ 
    	/* ilk verilen stringte harf kalmamasý durumunda
		ikinci string in harflerine geçilir
		bitene kadar, yeni string e harf ekleme iþlemi devam eder*/
        strncat(newString, &Y[j - 1], 1); 
        j--, index--; 
    } 
    
    /* baþlangýçta belirtildiði gibi string e harf 
	ekleme iþlemi sondan baþa doðrudur, elde edilen 
	string, asýl olmasý gereken string in ters halidir
	bunun için string in tersini (reverse) alan
	gömülü "strrev" fonksiyonu kullanýlýr*/
    strrev(newString); 
    /* string sonunda fazladan harf, rakam vb olmamasý için
	uzunluðun 1 eksiðine (son indise)
	bitiþ göstergesi konur*/
    newString[strlen(newString) - 1] = '\0';
    // lenght deðiþkenine atama
    lenght = strlen(newString);
    printf("Result of string: %s\n", newString);
}
/* çalýþmada istenen görsellik 
her bir çalýþma zamaný için "*" iþareti ile
yapýldý.parametre olarak kodun o anki çalýþma
süresini alýr*/
void print_star(double value){
	/* yazdýrýlabilir bir deðer elde etmek için
	her bir sayý 10 ile çarpýlýp integer bir 
	deðere dönüþtürülür*/
	int new_value = value * 10;
	int i;
	for(i = 0; i<new_value; i++){ 
		// asterisk iþareti ekrana bastýrýlýyor
		printf("*");
	}
	/* histogramýn düzgün görünmesi için
	geri kalan kýsma boþluk bastýrýldý*/
	for(i = 0; i<50 - new_value; i++){
		printf(" ");
	}
}
int main(){ 
	// kullanýcýnýn gireceði stringler
    char X[15], Y[15]; 
    /* kullanýcýnýn programdan çýkýþ yapýp yapmadýðýný
	kontrol etmek için kullanýlacak deðiþken
	0 ise devam 1 ise çýkýþ */
    int flag = 0;
    /* baþlangýçta tanýmlanan input-output-time
	dizilerinin her bir girdi için atamasýnda 
	kullanýlacak olan indis*/
    int in_out_index = 0;
    do{
    	/* iþlem süresinin tutulduðu deðiþken*/
    	double time_result;
    	printf("Enter the first string:");
    	scanf("%s",&X);
    	printf("Enter the second string:");
    	scanf("%s",&Y);
    	/* iþlem baþlamadan önce zaman alýnýyor*/
        gettimeofday(&tv1, NULL);
        /* alýnan stringlerin uzunluklarý toplamý
		ilgili diziye yerleþtirilir*/
    	len_inputs[in_out_index] = (strlen(X) + strlen(Y));
    	// asýl iþlemin yapýldýðý fonksiyon çaðrýlýyor
    	makeString(X, Y);
    	//fonksiyon içinde bulunan lenght ekrana yazdýrýlýyor
    	printf("Length of the shortest supersequence is %d\n", lenght);
    	/* bulunan yeni string uzunluðu
		ilgili diziye yerleþtiriliyor*/
		len_outputs[in_out_index] = lenght;	
		// iþlem bittikten sonra yeniden zaman alýnýyor
    	gettimeofday(&tv2, NULL);
    	// alýnan iki zaman deðerinin farký bulunuyor
    	time_result = (double) (tv2.tv_sec + tv2.tv_usec) / 1e6 - (double) (tv1.tv_sec - tv1.tv_usec) / 1e6;
    	// bulunan fark ilgili diziye yerleþtiriliyor
    	time_values[in_out_index] = time_result;
    	//yeni iþlem için indis deðeri 1 arttýrýlýyor
    	in_out_index++;
		printf ("Total time = %f seconds\n", time_result);
    	printf("---------------------------------------------\n");
    	printf("Do you want to continue?\nEnter 0 to continue or 1 to exit:");
    	scanf("%d",&flag);
	}while(flag == 0);
    
    /* kullanýcý programdan çýktýktan sonra
	bir histogram görüntüsü ekrana verilir
	her bir string girdilerinin ve yeni string in
	toplamý için, baþlangýçta oluþturulan dizilerden
	sýrasý ile veriler alýnýr.*/
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
