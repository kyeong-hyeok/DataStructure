#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CircularQueue.h"

#define	CUS_COME_TERM	15		// ���� �ֹ� ����: �� ����

#define CHE_BUR		0		// ġ����� ��� 
#define BUL_BUR		1		// �Ұ����� ���
#define DUB_BUR		2		// ������� ���

#define CHE_TERM	12		// ġ����� ���� �ð�: �� ����
#define BUL_TERM	15		// �Ұ����� ���� �ð�: �� ����
#define DUB_TERM	24		// ������� ���� �ð�: �� ����
#define SIM_NUM		10000	// Simulation ��
int main(void)
{
	int makeProc=0;			// �ܹ��� ���� �����Ȳ
	int cheOrder=0, bulOrder=0, dubOrder=0;
	int sec;
	int fail = 0, fail_count = 0, num;

	Queue que;

	srand(time(NULL));

	for (num = 0; num < SIM_NUM; num++) {
		QueueInit(&que);
		makeProc = 0;
		// �Ʒ� for���� 1ȸ ȸ���� 1���� �ð� �帧�� �ǹ���
		for (sec = 0; sec < 3600; sec++)
		{
			if (sec % CUS_COME_TERM == 0)
			{
				switch (rand() % 3)
				{
				case CHE_BUR:
					if (Enqueue(&que, CHE_TERM))
						cheOrder += 1;
					else 
						fail = TRUE;
					break;

				case BUL_BUR:
					if (Enqueue(&que, BUL_TERM))
						bulOrder += 1;
					else
						fail = TRUE;
					break;

				case DUB_BUR:
					if (Enqueue(&que, DUB_TERM))
						dubOrder += 1;
					else
						fail = TRUE;
					break;
				}
			}

			if (fail) {
				fail = FALSE;
				fail_count++;
				break;
			}

			if (makeProc <= 0 && !QIsEmpty(&que))
				makeProc = Dequeue(&que);

			makeProc--;
		}
	}

	printf("Simulation Report! \n", QUE_LEN);
	printf(" - Cheese burger: %d \n", cheOrder);
	printf(" - Bulgogi burger: %d \n", bulOrder);
	printf(" - Double burger: %d \n", dubOrder);
	printf(" - Waiting room size: %d \n", QUE_LEN-1);
	printf("Waiting rood size: %d. Probability to serve customers: %lf", QUE_LEN-1, ((double)(SIM_NUM - fail_count) / SIM_NUM));
	return 0;
}