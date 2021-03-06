#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <windows.h>

int sem;

void wait()
{
	while (!sem)
		int a = 12;
}

void signal()
{
	sem = 1;
}

int main()
{
	int bufCommon,bufPrivate;
	for (int life = 0; life < 10; life++)//жизненный цикл
	{
		sem = 0;
#pragma omp parallel num_threads(4)
		{
			int myID = omp_get_thread_num();
			if (!myID)//запись сообщения
			{
				bufCommon = rand() % 30;
				printf("%d - %d\n", myID, bufCommon);
				signal();
			}
			else//ждут пока запишется
			{
				wait();
			}
		}

		sem = 0;
#pragma omp parallel num_threads(4)
		{
			int myID = omp_get_thread_num();
			if (myID)//переписываем в свою переменную
			{
				bufPrivate = bufCommon;
				printf("%d - %d\n",myID,bufPrivate);
				signal();
			}
			else//ждем пока перепишут
			{
				wait();
			}
		}
		printf("\n");
	}
	getchar();
    return 0;
}

