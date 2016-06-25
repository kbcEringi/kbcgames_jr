#include"CDataLoad.h"
#include<stdio.h>
#include<Windows.h>


int CDataLoad::LoadData()
{
	FILE* fp;

	if ((fp = fopen("Data/StageData.txt", "a+b")) == NULL)
	{
		MessageBox(0, TEXT("error"), NULL, MB_OK);
	}
	int num;

	num = getc(fp);

	fclose(fp);

	return num;
}

void CDataLoad::SetData(int num)
{
	FILE* fp;

	if ((fp = fopen("Data/StageData.txt", "wb")) == NULL)
	{
		MessageBox(0, TEXT("error"), NULL, MB_OK);
	}

	fputc(num, fp);

	fclose(fp);
}