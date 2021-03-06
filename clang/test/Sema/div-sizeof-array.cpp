// RUN: %clang_cc1 %s -verify -Wsizeof-array-div -fsyntax-only -triple=x86_64-linux-gnu
// RUN: %clang_cc1 %s -verify -fsyntax-only -triple=x86_64-linux-gnu

template <typename Ty, int N>
int f(Ty (&Array)[N]) {
  return sizeof(Array) / sizeof(Ty); // Should not warn
}

typedef int int32;

void test(void) {
  int arr[12]; // expected-note 2 {{array 'arr' declared here}}
  unsigned long long arr2[4];
  int *p = &arr[0];
  int a1 = sizeof(arr) / sizeof(*arr);
  int a2 = sizeof arr / sizeof p; // expected-warning {{expression does not compute the number of elements in this array; element type is 'int', not 'int *'}}
  // expected-note@-1 {{place parentheses around the 'sizeof p' expression to silence this warning}}
  int a4 = sizeof arr2 / sizeof p;
  int a5 = sizeof(arr) / sizeof(short); // expected-warning {{expression does not compute the number of elements in this array; element type is 'int', not 'short'}}
  // expected-note@-1 {{place parentheses around the 'sizeof(short)' expression to silence this warning}}
  int a6 = sizeof(arr) / sizeof(int32);
  int a7 = sizeof(arr) / sizeof(int);
  int a9 = sizeof(arr) / sizeof(unsigned int);
  const char arr3[2] = "A";
  int a10 = sizeof(arr3) / sizeof(char);
  int a11 = sizeof(arr2) / (sizeof(unsigned));
  int a12 = sizeof(arr) / (sizeof(short));

  int arr4[10][12];                         // expected-note 3 {{array 'arr4' declared here}}
  int b1 = sizeof(arr4) / sizeof(arr2[12]); // expected-warning {{expression does not compute the number of elements in this array; element type is 'int [12]', not 'unsigned long long'}}
  // expected-note@-1 {{place parentheses around the 'sizeof (arr2[12])' expression to silence this warning}}
  int b2 = sizeof(arr4) / sizeof(int *); // expected-warning {{expression does not compute the number of elements in this array; element type is 'int [12]', not 'int *'}}
  // expected-note@-1 {{place parentheses around the 'sizeof(int *)' expression to silence this warning}}
  int b3 = sizeof(arr4) / sizeof(short *); // expected-warning {{expression does not compute the number of elements in this array; element type is 'int [12]', not 'short *'}}
  // expected-note@-1 {{place parentheses around the 'sizeof(short *)' expression to silence this warning}}

  int arr5[][5] = { // expected-note 2 {{array 'arr5' declared here}}
      {1, 2, 3, 4, 5},
      {6, 7, 8, 9, 0},
  };
  int c1 = sizeof(arr5) / sizeof(*arr5);
  int c2 = sizeof(arr5) / sizeof(**arr5); // expected-warning {{expression does not compute the number of elements in this array; element type is 'int [5]', not 'int'}}
  // expected-note@-1 {{place parentheses around the 'sizeof (**arr5)' expression to silence this warning}}
  int c3 = sizeof(arr5) / sizeof(int); // expected-warning {{expression does not compute the number of elements in this array; element type is 'int [5]', not 'int'}}
  // expected-note@-1 {{place parentheses around the 'sizeof(int)' expression to silence this warning}}
}
