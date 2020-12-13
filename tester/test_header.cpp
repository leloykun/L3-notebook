bool ANY_FAILED = false;

template <class T>
void assert_equal(T expected, T actual, bool kill = false) {
    if (!(expected == actual)) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "  Actual: " << actual << std::endl;
        if (kill) assert(false);
    }
}

template <class T>
void assert_not_equal(T not_expected, T actual, bool kill = false) {
    if (not_expected == actual) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Not expected: " << not_expected << std::endl;
        std::cout << "      Actual: " << actual << std::endl;
        if (kill) assert(false);
    }
}

void assert_true(bool actual, bool kill = false) {
    if (true != actual) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Expected: " << "true" << std::endl;
        std::cout << "  Actual: " << "false" << std::endl;
        if (kill) assert(false);
    }
}

void assert_false(bool actual, bool kill = false) {
    if (false != actual) {
        ANY_FAILED = true;
        std::cout << "Assertion failed:" << std::endl;
        std::cout << "Expected: " << "false" << std::endl;
        std::cout << "  Actual: " << "true" << std::endl;
        assert(false);
        if (kill) assert(false);
    }
}

void assert_almost_equal(double a, double b, double eps = 1e-9, bool kill = false) {
    assert_true(abs(a - b) < eps, kill);
}

double randdouble(double a, double b) {
    return static_cast<double>(rand()) / RAND_MAX * (b - a) + a;
}

int randint(int a, int b) {
    return static_cast<int>(randdouble(a, b) + 0.5);
}
