(function() {
    setAllLow();

    var rows = new Array(12);
    for (var i = 0; i < 12; i++) rows[i] = i;
    shuffle(rows, 12);

    var current = 0;
    setInterval(function() {
        for (var row = 0; row < 12; row++) {
            for (col = 0; col < 5; col++) {
                var curCol = (rows[row] + col + current) % 12;
                var level = col / 4;
                setLevel(row, curCol, level);
            }
        }
        current = (current + 1) % 12;
    }, 100);
})();