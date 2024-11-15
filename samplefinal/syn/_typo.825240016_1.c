/*

FUNGSI ITERATIF

int bilangan_iter (A[], i)
ipt: array A bertipe int[], i bertipe int
output: n bertipe float
for (i = 0; i < 5; i++) {
A[i]
}
n = A[0] + (i - 1) * 2;
return (n);

-----------

FUNGSI REKURSIF

int bilangan_rec (A[], i, x)
ipt: array A bertipe int[], i dan x bertipe int
output: bertipe float
if (x != A[i]) {
        return -1;
}
else {
        return A[0] + (bilangan_rec(A, i-1, x)) * 2;

*/




int
bilangan_iter(int A[], int i, int n)
{
	for (i = 0; i < 5; i++) {
		A[i];
	}
	n = A[0] + (i - 1) * 2;
	return n;
}

int
bilangan_rec(int A[], int i, int x)
{
	if (x != A[i]) {
		return -1;
	} else {
		return A[0] + (bilangan_rec(A, i - 1, x)) * 2;
	}
}
