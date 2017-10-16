(function() {
    setAllLow();

    var current = 0;
    setInterval(function() {
        setAllRingsLow();
        for (var row = 0; row < 12; row++) {
            for (col = 0; col < 12; col++) {
                setRingL(row, col, current, [255,0,0]);
            }
        }
        current = (current + 1) % 12;
    }, 100);
})();