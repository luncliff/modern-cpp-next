#include <iostream>

int main() {
	// ��ü ���� ������ ����
	int sum = 0;

	// 1 ~ 10���� �ݺ��ϸ鼭 ����
	for (int i = 1; i <= 10;) {
		sum += i;	// ��������� �տ� i�� ����
		++i;		// i�� ������Ŵ
	}

	// ��� ���
	std::cout << "1 ~ 10������ �� = " << sum << std::endl;

	return 0;
}