int func1(int x) {
    int y = 100;
    y = x;
    if (x > 99) {
        return -y;
    }
    return y;
}
