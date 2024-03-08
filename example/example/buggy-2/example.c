int func1(int x) {
    int y = 100;
    y = x;
    if (x >= 100) {
        return -y;
    }
    return y;
}
