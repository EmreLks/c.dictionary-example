#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
void TurkceKelimeSorgula();
void IngilizceKelimeSorgula();
void SozlukAyir();
unsigned  int askidondur(char );
int karsilastir(char [],char []);
void anamenu();
main()
{
	setlocale(LC_ALL,"Turkish");
	system("color 1F");
	SozlukAyir();
	anamenu();
}
void anamenu()
{
	int islem;
	printf("\t\t**********   ISLEM SECINIZ:                 **********\n");
	printf("\t\t**********   TURKCE KELIME ARAMA    =>[1]   **********\n");
	printf("\t\t**********   INGILIZCE KELIME ARAMA =>[2]   **********\n");
	printf("\t\t**********   CIKIS                  =>[3]   **********\n\n");
	printf("Secim: ");scanf("%d",&islem);
	system("cls");
	switch(islem)
	{
		case 1:
			TurkceKelimeSorgula();
			anamenu();
			break;
		case 2:
			IngilizceKelimeSorgula();
			anamenu();
			break;
		case 3:
			exit(0);
		defaut:
			printf("Yanlis Islem Secimi!!!\n");
			anamenu();

	}
}
unsigned int askidondur(char deger)
{
	int sonuc;
	char yabanci[]={'ç','ð','ý','ö','þ','ü'};
	char harf[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','v','y','z'};
	for(int i=0;i<23;i++)
	{
		if(deger==harf[i])
		{
			sonuc=deger*2;
		}
		else if(i<6 && deger==yabanci[i])
		{
			if(deger=='ç')
				sonuc=2*'c'+1;
			else if(deger=='ð')
				sonuc=2*'g'+1;
			else if(deger=='ý')
				sonuc=2*'i'-1;
			else if(deger=='ö')
				sonuc=2*'o'+1;
			else if(deger=='þ')
				sonuc=2*'s'+1;
			else if(deger=='ü')
				sonuc=2*'u'+1;
		}
	}
	return sonuc;
}
int karsilastir(char kelime1[],char kelime2[])
{
	int deger;
	int sayac=0;
	while(kelime1[sayac]!=NULL)
	{
		if(askidondur(kelime1[sayac]) == askidondur(kelime2[sayac]) && strlen(kelime1)==strlen(kelime2))
		{
			deger=0;
		}
		else if(askidondur(kelime1[sayac]) < askidondur(kelime2[sayac]))
		{
			deger=-1;
			break;
		}
		else if(askidondur(kelime1[sayac]) > askidondur(kelime2[sayac]))
		{
			deger=1;
			break;
		}
		sayac++;
	}

	return deger;

}
void SozlukAyir()
{
	int i=0;
	FILE *tr,*ing,*dic;
	char ingkelime[120][25],trkelime[120][25],trindexkelime[25],ingindexkelime[25];

	if((dic=fopen("sozluk.txt","r"))==NULL)
	{
		printf("Sozluk.txt Acilmadi!!!");
	}
	if((ing=fopen("ingilizce.txt","w+"))==NULL)
	{
		printf("ingilizce.txt Acilmadi!!!");
	}
	if((tr=fopen("turkce.txt","w+"))==NULL)
	{
		printf("Turkce.txt Acilmadi!!!");
	}
	while(!feof(dic))
	{
		fscanf(dic,"%s%s",trkelime[i],ingkelime[i]);
		i++;
	}
	for(int k=0;k<i-1;k++)
	{
		for(int l=k+1;l<i;l++)
		{

			if(karsilastir(trkelime[k],trkelime[l]) > 0 )
			{
				strcpy(trindexkelime,trkelime[k]);
				strcpy(trkelime[k],trkelime[l]);
				strcpy(trkelime[l],trindexkelime);
				/////////////////////////////////
				strcpy(ingindexkelime,ingkelime[k]);
				strcpy(ingkelime[k],ingkelime[l]);
				strcpy(ingkelime[l],ingindexkelime);
			}
		}

	}


	for(int m=0;m<i;m++)
	{
		fprintf(tr,"%s\n",trkelime[m]);
		fprintf(ing,"%s\n",ingkelime[m]);
	}
	fclose(tr);
	fclose(ing);
	fclose(dic);

}
void TurkceKelimeSorgula()
{
	FILE *tr,*ing;
	int bulundu=0;
	char trkelime[25],trindex[25],ingindex[25];
	if((tr=fopen("turkce.txt","r"))==NULL)
	{
		printf("turkce.txt Acilmadi!!!");
	}
	if((ing=fopen("ingilizce.txt","r"))==NULL)
	{
		printf("ingilizce.txt Acilmadi!!!");
	}
	printf("Turkce Kelimeyi Giriniz: ");scanf("%s",trkelime);
	while(!feof(tr) )
	{
		fscanf(tr,"%s\n",trindex);
		fscanf(ing,"%s\n",ingindex);
		if(karsilastir(trkelime,trindex)==0)
		{
			printf("Sonuc: %s\n",ingindex);
			bulundu=1;
		}
	}
	if(bulundu==0)
	{
		printf("\nKelime Bulunamadi!!!\n");
	}
	fclose(tr);
	fclose(ing);
}
void IngilizceKelimeSorgula()
{
	FILE *tr,*ing;
	int bulundu=0;
	char ingkelime[25],trindex[25],ingindex[25];
	if((tr=fopen("turkce.txt","r"))==NULL)
	{
		printf("turkce.txt Acilmadi!!!");
	}
	if((ing=fopen("ingilizce.txt","r"))==NULL)
	{
		printf("ingilizce.txt Acilmadi!!!");
	}
	printf("Ingilizce Kelimeyi Giriniz: ");scanf("%s",ingkelime);
	while(!feof(ing) )
	{
		fscanf(ing,"%s\n",ingindex);
		fscanf(tr,"%s\n",trindex);
		if(strcmp(ingkelime,ingindex)==0)
		{
			printf("Sonuc: %s\n",trindex);
			bulundu=1;
		}
	}
	if(bulundu==0)
	{
		printf("\nKelime Bulunamadi!!!\n");
	}
	fclose(tr);
	fclose(ing);

}
