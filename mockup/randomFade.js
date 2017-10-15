(function() {
    setAllLow();

    var pixels = new Array(144);
    for (var i = 0; i < 144; i++) pixels[i] = i;

    var current = 0;
    var direction = LOW;
    setInterval(function() {
        if (current == 0) {
            direction = direction == LOW ? HIGH : LOW;
            shuffle(pixels, 144);
        }
        var row = pixels[current] % 12;
        var col = (pixels[current] - row) / 12;
        setLight(row, col, direction);

        current = (current + 1) % 144;
    }, 100);
})();