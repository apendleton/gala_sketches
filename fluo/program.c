void loop() {
    drops(50);

    bars_sweep(30);
    randomFade(30,2);

    bars_sides(30);
    spokes(15, true);

    bars_diag(30);
    snake(30);

    bars_crosswalk(25);

    setAllLow();
    delay(30 * 1000);
    delay(30 * 1000);
}