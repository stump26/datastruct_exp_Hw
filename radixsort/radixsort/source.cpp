#define NUMELTS 10
#include <stdio.h>
#include <math.h>
struct {
	int info;
	int next;
}node[NUMELTS];
void radixsort(int x[], int n)
{
	int front[10], rear[10];

	int exp, first, i, j, k, p, q, y, m;

	/* 연결 리스트를 초기화 */
	for (i = 0; i < n - 1; i++) {
		node[i].info = x[i];
		node[i].next = i + 1;
	}
	node[n - 1].info = x[n - 1];
	node[n - 1].next = -1;
	first = 0;
	/* 숫자를 2 개로 가정 */
	for (k = 1; k < 3; k++) {
		for (i = 0; i < 10; i++) {
			rear[i] = -1;
			front[i] = -1;
		}
		exp = pow((double)10, k - 1);
		/* 각 원소를 처리 */

		while (first != -1) {
			p = first;
			first = node[first].next;
			y = node[p].info;
			/* k 번째x` 숫자를 발췌 */
			j = (y / exp) % 10;
			/* y 를 큐[i]에 삽입 */
			q = rear[j];
			if (q == -1)
				front[j] = p;
			else
				node[q].next = p;
			rear[j] = p;
		} /* end while */
		

		/* 첫 원소를 찾는다 */
		for (j = 0; j < 10 && front[j] == -1; j++)	;
		first = front[j];
		/* 큐들을 연결한다 */
		while (j <= 9) {
			/* 다음 원소를 찾는다 */
			for (i = j + 1; i < 10 &&front[i] == -1; i++)		;
			if (i <= 9) {
				p = i;
				node[rear[j]].next = front[i];
			}
			j = i;
		} /* end while */
		node[rear[p]].next = -1;
		m = first;
		/*중간결과출력*/
		printf("%d자리 정렬 : ", k);
		while (m != -1) {
			printf("%d ", node[m].info);
			m = node[m].next;
		}
		printf("\n");

	} /* end for */

	/* 원래 파일에 복사 */
	for (i = 0; i < n; i++) {
		x[i] = node[first].info;
		first = node[first].next;
	}

}
int main(void) {
	int i;
	int x[10] = { 57,14,36,32,38,54,56,34,26,74 };
	radixsort(&x[0], 10);
	printf("최종 : ");
	for (i = 0; i < 10; i++) {
		printf("%d  ", x[i]);
	}
	printf("\n");
	return 0;
}
