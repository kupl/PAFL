int func1(int x) {
    int y = 100;
    y = x;
    if (x > 101) {
        return -y;
    }
    return y;
}
