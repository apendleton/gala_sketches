void loop() {
    bars(25);
    drops(50);

    bars(30);
    randomFade(30,2);

    bars(30);
    spokes(15, true);

    bars(30);
    snake(30);

    setAllLow();
    delay(30 * 1000);
    delay(30 * 1000);
}