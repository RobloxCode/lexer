// single-line comment: should be skipped entirely, no token
/* multi-line
   comment: should also be skipped entirely, no token */

int main(void) {
    int count = 0;
    float average = 3.14;
    char *name = "hello world";

    int valid_int = 42;
    float valid_float = 3.14159;
    float suffixed = 10.5f;
    // float invalid_num = 1.2.3;

    count = count + 1;
    count = count - 1;
    count = count * 2;
    count = count / 2;

    if (count == 0) {
        count += 1;
    }

    if (count != 0 && average <= 3.14) {
        count -= 1;
    }

    if (count >= 0 || average >= 0) {
        count++;
    }

    int arr[3] = {1, 2, 3};

    int *first = arr;

    ()

        /=

        some_fn();

    return 0;
}
