(function() {
    setAllLow();

    var current = 0;

    setInterval(function() {
        if (current < 60) {
            var level = (current + 1) / 60;
            for (var row = 0; row < 6; row++) {
                for (var i = 0; i < 12; i++) {
                    setLevel(row * 2, i, level * (8 - row)/8);
                }
            }
        } else if (current >= 600) {
            current = 0;
            setAllLow();
        }

        current += 1;
    }, 100);
})();